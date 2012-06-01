#include <SoftwareSerial.h>  
char gsm_char=0;      //Stores character from the gsmSerial
 
SoftwareSerial gsmSerial(2,3);  //Creates a software serial port. (rx,tx)
 
void setup()
{
  //Initialize serial ports for communication.
  Serial.begin(9600);
  gsmSerial.begin(9600);
  Serial.println("Starting TC35 and debug Communication...");
}

void loop() { 
  loop_gsm();
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
