#include <SoftwareSerial.h>  

//VARS
int ledPin = 13;
int buttonPin =12;
int releSirenaPin = 5;
int releGSMPin = 4;

int piezoPin = 11;
int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

int allarme= 0;

/*
create a Button object at pin 12
connect button between pin 12 and GND
*/
//Button button = Button(12,BUTTON_PULLUP);


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
  setup_interuttori();
  setup_piezo();
}

//SETUP PIEZO
void setup_piezo() {
  pinMode(piezoPin, OUTPUT);
}

//SETUP BUTTON
void setup_interuttori(){
  pinMode(buttonPin, INPUT);           // set pin to input
  digitalWrite(buttonPin, HIGH);       // turn on pullup resistors
}

//SETUP RELE
void setup_rele(){
  pinMode(releSirenaPin, OUTPUT);
  pinMode(releGSMPin, OUTPUT);
}

//SETUP PIR
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
  int buttonState = 0;
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is LOW:
  if (buttonState == LOW) {    
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  }
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
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

//da cancellare \/
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(piezoPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(piezoPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void loop_piezo() {
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }

    // pause between notes
    delay(tempo / 2); 
  }
}
