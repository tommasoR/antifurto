#include <SoftwareSerial.h>  
#include <Button.h>

//VARS
int ledPin = 13;
int releSirenaPin = 5;
int releGSMPin =4;
int allarme= 0;

/*
create a Button object at pin 12
connect button between pin 12 and GND
*/
Button button = Button(12,BUTTON_PULLUP);

//PIRsense
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30; 

//the time when the sensor outputs a low impulse
long unsigned int lowIn;  

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 5000;

boolean lockLow = true;
boolean takeLowTime;  

int pirPin_1 = 8;//the digital pin connected to the PIR sensor's output
int pirPin_2 = 9;// 


//GSM
char gsm_char=0;      //Stores character from the gsmSerial
SoftwareSerial gsmSerial(2,3);  //Creates a software serial port. (rx,tx)
 
void setup()
{
  //Initialize serial ports for communication.
  Serial.begin(9600);
  gsmSerial.begin(9600);
  Serial.println("Starting TC35 and debug Communication...");
  setup_pir();
  setup_rele();
}
//SETUP RELE
void setup_rele(){
  pinMode(releSirenaPin, OUTPUT);
  pinMode(releGSMPin, OUTPUT);
}

//SETUPPIR
void setup_pir(){
  pinMode(pirPin_1, INPUT);
  pinMode(pirPin_2, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin_1, LOW);
  digitalWrite(pirPin_2, LOW);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
  }

void loop() { 
  loop_gsm();
  loop_interuttore();
  loop_pir();
}

//LOOP
void loop_pir(){

     if((digitalRead(pirPin_1) == HIGH)||(digitalRead(pirPin_2) == HIGH)){
       digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
       if(lockLow){  
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;            
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec"); 
         delay(50);
         }         
         takeLowTime = true;
       }

     if((digitalRead(pirPin_1) == LOW)||(digitalRead(pirPin_2) == LOW)){       
       digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state

       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause, 
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
           lockLow = true;                        
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           }
       }
  }

void loop_interuttore(){
if(button.isPressed()){
	digitalWrite(ledPin,HIGH);
        attiva_sirena();
  }else{
	digitalWrite(ledPin,LOW);
  }
}

void loop_gsm() {
  //If a character comes in from the cellular module...
  if(gsmSerial.available() > 0){
    gsm_char=gsmSerial.read();    //Store the char in gsm_char.
    Serial.print(gsm_char);  //Print it to debug serial
  }
  //Read serial input
  if(Serial.available() > 0){
    gsm_char=Serial.read();  //Store char in gsm_char (Not really from the gsm, just saving some memory)
    //Evaluate input.
    if(gsm_char=='t'){
      gsmSerial.print("AT\r");  //Send test command
    } else if(gsm_char=='p'){
      gsmSerial.print("AT+CPIN=PINNUMBER\r");  //Enter pin, hardcoded
    } else if(gsm_char=='g'){
      gsmSerial.print("AT+CMGF=1\r"); //Set text mode.
    } else if(gsm_char=='s'){
      //Send sms!
      gsmSerial.print("AT+CMGS=PHONENUMBER\r"); //AT command to send SMS
      delay(100);
      gsmSerial.print("Hello Henrik"); //Print the message
      delay(10);
      gsmSerial.print("\x1A"); //Send it ascii SUB
    }
  }
}

void attiva_sirena(){
  digitalWrite(releSirenaPin, HIGH);   // sets the rele on
  delay(10000);                        // waits for 10 seconds
  digitalWrite(releSirenaPin, LOW);
}
