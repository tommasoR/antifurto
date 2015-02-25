#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/* Antifurto giardino versione 1.0 del Febbraio 2015 by Tom
   comprende:
   1 display 5110
   3 ingressi NC a calamita
   1 foto resistenza per luce notturna
   2 rele per azionamento sirena e luce di notturna di cortesia
   1 TMP 36 sensore di temperatura
*/

/*5110 collegare resistenze 10K i pin del 5110  non sono standard
http://forum.arduino.cc/index.php?topic=254284.0
BL 100ohm
*/
#define PIN_SCE   7 //Pin X on LCD
#define PIN_RESET 6 //Pin X on LCD
#define PIN_DC    5 //Pin X on LCD
#define PIN_SDIN  4 //Pin X on LCD
#define PIN_SCLK  3 //Pin X on LCD

//rele
#define PIN_RELE_SIRENA 11 //TODO mettere a 11
#define PIN_RELE_LUCE_NOTTURNA 12

//fotoresistenza
/*
----------------------------------------------------

           PhotoR     50K
 +5    o---/\/\/--.--/\/\/---o GND
                  |
 Pin 0 o-----------

----------------------------------------------------
*/
#define LIGHT_PIN  0 //define a pin for Photo resistor
int valphotoRes=1023; //variabile con valore luce 0 senza luce; max 1023 piena luce o sensore disabilitato


const word PAGINA1 = 15000;// 15 secondi per pagina 1 
const word PAGINA2 = 13000;// dopo 13 secondi pagina 2 i valori DEVONO essere differenti

//Variabili
unsigned long currentMillis = 0L;
word sogliaGiornoNotte = 100;//da verificare con metodo empirico
unsigned long pollingPhotoR = 30000;//5 minut1 300.000 TODO
word pollingMonitor = PAGINA1;
unsigned long durataSirena = 0;// ogni allarme definisce la durata in millisecondi
unsigned long startMillisSirena = 0L;
unsigned long previousMillisPhotoR = 0L;
unsigned long previousMillisMonitor = 0L;
unsigned long previousMillisSirena = 0L;
unsigned long previousMillisTemp = 0L;
unsigned long lastPowerON_LIGHT =0L;
unsigned long lastPowerOFF_LIGHT =0L;


/*Contatti magnetici normalmente chiusi
DEVONO essere consecutivi i pin altrimenti modificare il CICLO FOR*/
#define NC_CONT_1  8
#define NC_CONT_2  9
#define NC_CONT_3 10

/* array "zona" degli eventi di allarme
contiene il valore in millis degli eventi dei contatti NC                       
              d8 d9 d10 */
typedef struct 
{
  unsigned long eventMillis;
  boolean  consumato;
} zona ;

zona zonas[3];


/* Sensor test sketch
    for more information see http://www.ladyada.net/make/logshield/lighttemp.html
    */
//LM35 Pin Variables
#define tempPin 1 //the analog pin the LM35's Vout (sense) pin is connected to
    //the resolution is 10 mV / degree centigrade with a
    //500 mV offset to allow for negative temperatures
  float temperatureC = 0.0; // the analog reading from the sensor
  int LM35sensor = 0;
  float volts = 0.0;

//
//variabili per  monitor
  String t;
  char charBuf[10];
  char tempBuf[10];

//The DC pin tells the LCD if we are sending a command or data
#define LCD_C     LOW
#define LCD_D     HIGH


//You may find a different size screen, but this one is 84 by 48 pixels
#define LCD_X     84
#define LCD_Y     48

//This table contains the hex values that represent pixels
//for a font that is 5 pixels wide and 8 pixels high
static const byte ASCII[][5] =
{
 {0x00, 0x00, 0x00, 0x00, 0x00} // 20  
,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c ¥
,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j 
,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ←
,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f →
};

void LcdCharacter(char character)
{
  LcdWrite(LCD_D, 0x00);
  for (int index = 0; index < 5; index++)
  {
    LcdWrite(LCD_D, ASCII[character - 0x20][index]);
  }
  LcdWrite(LCD_D, 0x00);
}

void LcdClear(void)
{
  for (int index = 0; index < LCD_X * LCD_Y / 8; index++)
  {
    LcdWrite(LCD_D, 0x00);
  }
}

void LcdInitialise(void)
{
  pinMode(PIN_SCE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_SDIN, OUTPUT);
  pinMode(PIN_SCLK, OUTPUT);
  digitalWrite(PIN_RESET, LOW);
  digitalWrite(PIN_RESET, HIGH);
  LcdWrite(LCD_C, 0x21 );  // LCD Extended Commands.
  LcdWrite(LCD_C, 0xB1 );  // Set LCD Vop (Contrast). 
  LcdWrite(LCD_C, 0x04 );  // Set Temp coefficent. //0x04
  LcdWrite(LCD_C, 0x14 );  // LCD bias mode 1:48. //0x13
  LcdWrite(LCD_C, 0x20 );  // LCD Basic Commands
  LcdWrite(LCD_C, 0x0C );  // LCD in normal mode.
}

void LcdString(char *characters)
{
  while (*characters)
  {
    LcdCharacter(*characters++);
  }
}

void LcdWrite(byte dc, byte data)
{
  digitalWrite(PIN_DC, dc);
  digitalWrite(PIN_SCE, LOW);
  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
  digitalWrite(PIN_SCE, HIGH);
}

void resetVariabili(void){
   for (int i = 0; i < 3; i++) {
           zonas[i].eventMillis=0L;
           zonas[i].consumato=false;
        }
}

/* Questa funzione restituisce una stringa che riporta l'ora minuti e secondi dall'evento*/
char*  getTimebyMillis(unsigned long m){
  char evento[100];
  unsigned long seconds = 0; 
  unsigned long minutes = 0; 
  unsigned long hours = 0; 
  /* se valore in millis è negativo lo riporto a positivo*/
  if (m<0)
    m*=-1;
  seconds += m / 1000; 
  m = m % 1000; 
  minutes += seconds / 60; 
  seconds = seconds % 60; 
  hours += minutes / 60; 
  minutes = minutes % 60; 
  hours = hours % 24; 
  
  sprintf(evento,"%.2luH%.2luM%.2luS",hours,minutes,seconds);
  return evento;
}

void setup(void)
{
Serial.begin(9600);  //Begin serial communcation
  LcdInitialise();
  LcdClear();
  LcdString("Ciao Mondo!");
  
  // setto i contatti NC 
  pinMode(NC_CONT_1, INPUT);           // set pin to input
  digitalWrite(NC_CONT_1, HIGH);       // turn on pullup resistors
  pinMode(NC_CONT_2, INPUT);           // set pin to input
  digitalWrite(NC_CONT_2, HIGH);       // turn on pullup resistors
  pinMode(NC_CONT_3, INPUT);           // set pin to input
  digitalWrite(NC_CONT_3, HIGH);       // turn on pullup resistors
  
  // initialize the digital pin's as an output.
  pinMode(PIN_RELE_SIRENA, OUTPUT);            // Relay 1 
  digitalWrite(PIN_RELE_SIRENA, LOW);
  pinMode(PIN_RELE_LUCE_NOTTURNA, OUTPUT);     // Relay 2
  digitalWrite(PIN_RELE_LUCE_NOTTURNA, LOW);
  
  //
  resetVariabili();
}

void loop(void)
{
  currentMillis = millis();
  photoRes();
  contattiNC();
  readTemp();
  monitor();
  sirena();
}

void contattiNC(void){
  for (int i=0; i < 3; i++){
    if (digitalRead(i+NC_CONT_1) && !(zonas[i].consumato)){    
      delay(150);//anti rimbalzo per i pulsanti a membrana bastano 15  millis x quelli a lamella meglio 150
      if(digitalRead(i+NC_CONT_1)){
        zonas[i].consumato = true; 
        zonas[i].eventMillis = currentMillis;
        startMillisSirena = currentMillis; 
        durataSirena = 300000;//imposta durata sirena a 5 minuti  300000millis
      }
    }
  }  
}

void sirena(void){
  if((durataSirena != 0) && (currentMillis - startMillisSirena < durataSirena)) {
    //accendi sirena e tieni accesa
    digitalWrite(PIN_RELE_SIRENA, HIGH);
  } else if(durataSirena > 0){
    //spegni sirena
    digitalWrite(PIN_RELE_SIRENA, LOW);
    durataSirena=0L;// metto a zero così non setto più la porta della sirena
  }
}

void monitor(void){
  if(currentMillis - previousMillisMonitor > pollingMonitor) {
    // save the last time control
    previousMillisMonitor= currentMillis;
    
    LcdInitialise();
    LcdClear();
    
    LcdString("A :");
    LcdString(getTimebyMillis(currentMillis));
    
    
    if(pollingMonitor==PAGINA1){
      //pagina 1
      pollingMonitor=PAGINA2;//prossimo giro fai vedere seconda pagina
      
      //ultima accensione Luce
      if(lastPowerON_LIGHT>0){
        LcdString("L1:");
        LcdString(getTimebyMillis(currentMillis-lastPowerON_LIGHT));
      } 
      
      //ultimo spegnimento luce
      if(lastPowerOFF_LIGHT>0){
        LcdString("L0:");
        LcdString(getTimebyMillis(currentMillis-lastPowerOFF_LIGHT));
      }
      
      //valore letto dalla photoresist
      LcdString("Luce_= ");
Serial.println(analogRead(LIGHT_PIN));  
      t=(String(analogRead(LIGHT_PIN), DEC));
Serial.println("t.length()");
Serial.println(t.length());
      t.toCharArray(charBuf,10);
      LcdString(charBuf);
Serial.println(charBuf);

     //valore letto per la temperatura
     dtostrf(temperatureC , 2, 2, tempBuf);
Serial.print("valore che dovrei mandare su lcd tempBuf=");Serial.println(tempBuf);
    } else {
      //pagina 2
      pollingMonitor=PAGINA1;//prossimo giro fai vedere prima pagina
      
      for (int i = 0; i < 3; i++) {
           if(zonas[i].eventMillis > 0){
             LcdString("Z");
             itoa(i,charBuf,10);
             LcdString(charBuf);
             LcdString(":");
             LcdString(getTimebyMillis(currentMillis-zonas[i].eventMillis));
           }
      }
      
      //ultima volta che ha suonato la sirena
      if(startMillisSirena>0){
        LcdString("S1:");
        LcdString(getTimebyMillis(currentMillis-startMillisSirena));
      }
    }
  }
}

void photoRes(void){
  if(currentMillis - previousMillisPhotoR > pollingPhotoR) {
Serial.println("photoRes");
    // save the last time control
    previousMillisPhotoR = currentMillis;  
    valphotoRes=analogRead(LIGHT_PIN);// 0 senza luce; max 1023 piena luce o sensore disabilitato
Serial.println(valphotoRes); //Write the value of the photoresistor to the serial monitor.
    if(valphotoRes<sogliaGiornoNotte && lastPowerOFF_LIGHT >= lastPowerON_LIGHT ){
      // Accendo luce nottura soglia superata 
      digitalWrite(PIN_RELE_LUCE_NOTTURNA, HIGH);
Serial.println("accendo");
      lastPowerON_LIGHT=previousMillisPhotoR;
    } else if(valphotoRes>sogliaGiornoNotte && lastPowerON_LIGHT > lastPowerOFF_LIGHT){
      //spengo luce notturna
      digitalWrite(PIN_RELE_LUCE_NOTTURNA, LOW);      
Serial.println("spengo");
      lastPowerOFF_LIGHT=previousMillisPhotoR;
    }
  }
}

void readTemp() {
  if(currentMillis - previousMillisTemp > 20000) {
    // save the last time control
    previousMillisTemp = currentMillis;
    //getting the voltage reading from the temperature sensor
    LM35sensor = analogRead(tempPin);
    //lettura valore del sensore LM35 messo sull'ingresso
    //analogico A1
    volts = ( LM35sensor/1024.0)*5.0; //formula per ottenere la tensione di uscita dell'LM35 in volts
    temperatureC =volts*100.0;// valore espresso in gradi Celsius (l'out del sensore è 10mv per grado) 
    // print out the voltage
Serial.print(volts); Serial.println(" volts");
    // now print out the temperature
Serial.print(temperatureC); Serial.println(" degrees C");
  }
}

