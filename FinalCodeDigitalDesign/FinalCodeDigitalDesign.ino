#include <OneWire.h>
#include <DallasTemperature.h>
#define IR1 A0
#define IR2 A1    
#define TemperatureSensor 3 //YELLOW - GREEN
int ElectricFan = 4; // GREEN -  WHITE
int Led = 5; 
int Led2 = 6;
int Led3 = 7;
OneWire oneWire(TemperatureSensor);
DallasTemperature sensors(&oneWire);
float currentTemp; 
int maxTemp =420;
unsigned int count = 0;
unsigned int flh1,flh2;
unsigned long valY, valX;
void tempSensor(){
  sensors.requestTemperatures();    x
  currentTemp = sensors.getTempCByIndex(0);
  //Serial.println(currentTemp);
}
void IRSensor(){
  valY = analogRead(IR1);  //BROWN - RED
  valX = analogRead(IR2);  //GRAY - ORANGE
 // Serial.println(valX);
  //Serial.println(valY);
  if(flh1==0)
  {
    if(valY<500)   
    {
      flh1=1;
      flh2=0; 
      
    }
    else if(valX<500)
    {
      flh1=1;
      flh2=1;
    }

    if(valX< 500&& valY< 500){
      if(flh1==1 && flh2==0){
        flh1=1;
        flh2=0;
      }else if(flh1==1 && flh2==1){
        flh1=1;
        flh2=1;
      }
    }
  }                                                            
  
  if(flh1==1)
  {
    if(flh2==1)
    {
      if(valY<500)   
      {
        flh1=0;
        if(count<999)
        {     
            count++;
            Serial.println(count);
        }
        //led_on_off();
  
        while(valY<500) 
        {
          valY = analogRead(IR1);  
        }

       }
    }
    
    if(flh2==0)
    {
      if(valX<500) 
      {
        flh1=0;
        if(count>0)
        {
          count--;
          Serial.println(count);
        }
        
      while(valX<500)
      {
        valX = analogRead(IR2);   
      }
        
      }                 
    }
  } 

}

void setup() {
  // put your setup code here, to run once:
  pinMode(IR1,INPUT_PULLUP);
  pinMode(IR2,INPUT_PULLUP);
  pinMode(ElectricFan, OUTPUT);
  pinMode(Led, OUTPUT);
  pinMode(Led2,OUTPUT);
  sensors.begin();
  Serial.begin(9600);
}

void loop() {
 tempSensor();
 IRSensor();
  if(currentTemp > maxTemp){
    digitalWrite(ElectricFan, HIGH);
  //  Serial.println("ON");
    if(count >= 0){
      digitalWrite(Led,HIGH);
      digitalWrite(Led2,HIGH);
      digitalWrite(Led3,HIGH);
      digitalWrite(ElectricFan, HIGH);
    }else if(count ==0){
      digitalWrite(Led,LOW);
      digitalWrite(Led2, LOW);
      digitalWrite(Led3,LOW);
      digitalWrite(ElectricFan,LOW);
    }
  }
  
  if(currentTemp <= maxTemp ){
    digitalWrite(ElectricFan,LOW);
   // Serial.println("OFF");
    if(count > 0 ){
      digitalWrite(Led,HIGH);
      digitalWrite(Led2,HIGH);
      digitalWrite(Led3,HIGH);
      digitalWrite(ElectricFan, HIGH);
    }else if(count ==0){
      digitalWrite(Led,LOW);
      digitalWrite(Led2, LOW);
      digitalWrite(Led3,LOW);
      digitalWrite(ElectricFan,LOW);
    }
  }
  } 

/* WIRINGS:
LED
//RED - BLUE WIRE IS THE CONNECTION TO RESISTOR, WHITEGREEN IS TO NEGATIVE
//BLUE1 - BLUE IS IN RESISTOR< ORANGE IS TO NEGATIVE
//BLUE2 - WHITE ORANGE IS TO RESISTOR BROWN IS TO NEGATIVE
//BLUE3 - WHITE GREEN IS TO RESSITOR, WHITE BLUE IS TO NEGATIVE
//ORANGE GREEN IS TO RESSITOR, WHITE BROWN IS TO NEGATIVE
//BLUE4 - WHITEBROWN TO RESISTOR GREEN TO NEGATIVE

IRSENSOR 
IR2 YElllow output
Brown G ND
Green VCC
YELLO from boarrd to A1
IR! Orange Output
Violet GND
Gre3en VCC
YELLOWBLACK FROM bboard toA0

TEMMP SENSOR
GREEN TO BBARD 
RED TO SLOT3

ELECTRICFAN 
GREENBLUE TO SLOT 4


*/
