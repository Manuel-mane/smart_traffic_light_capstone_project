#include <TimerThree.h>




int redled1 = 3;
int yellowled1 = 4;
int greenled1 = 5;
int redled2 = 7;
int yellowled2 = 8;
int greenled2 = 9;
int emergency1 = 0;
int emergency2 = 0;
int LCD1 = 23;
int LCD2 = 25;
const int t3_load = 0;
const int t3_comp = 31250; //compared value
int myFlag = 0;   //setting a flag
int traffic1;

///////////////////////////
int sensor_input = 41;
int sensor_output = 50;
int parking_red = 44;
int parking_green = 46;
int sign = 0;
///////////////////////////

//Funtion prototype
void trafficlight1();
void trafficlight2();
void normalcondition1();
void normalcondition2();
void notraffic();
void process();
void emergency();
void emergency1_act();
void emergency2_act();
 

void setup() 
{
  // put your setup code here, to run once:
  
pinMode (3, OUTPUT);
pinMode (4, OUTPUT);
pinMode (5, OUTPUT);
pinMode (7, OUTPUT);
pinMode (8, OUTPUT);
pinMode (9, OUTPUT);
pinMode (A0, INPUT);
pinMode (A3, INPUT);
pinMode (34, INPUT);
pinMode (26, INPUT);

//////////////////////
pinMode (sensor_input, INPUT);
pinMode (50, OUTPUT);
pinMode (44, OUTPUT);
pinMode (46, OUTPUT);
digitalWrite(sensor_output, HIGH);
digitalWrite(parking_red, HIGH);
digitalWrite(parking_green, LOW);

//////////////////////

Serial.begin(9600);

//timer setup
noInterrupts(); //disable all interrupts
TCCR3A = 0; //Reset timer control register A

TCCR3B &= -(1 << WGM13);
TCCR3B |= (1 << WGM12);
TCCR3B |= (1 << WGM32);

//Setting prescaler to 256
TCCR3B |= (1<<CS12);
TCCR3B &= -(1<<CS11);
TCCR3B &= -(1<<CS10);

TCNT3 = t3_load;
OCR3A = t3_comp;

//Enable Timer3 compare interrupt
TIMSK3 = (1 << OCIE3B);
SREG = (SREG & 0b01111111)|0b10000000; //Habilitar interrupciones
interrupts();  //enable all interrupts

}

//Main function
void loop() 
   
{    Serial.println(analogRead(A0)); //print voltage of output pin (resolution 1-1024
Serial.println(analogRead(A3)); //print voltage of output pin (resolution 1-1024
//delay (1000); //wait a second
if (analogRead(A3) < 800 && analogRead(A0) > 800)
{
  //function for side 1 ON and side 2 OFF
 trafficlight1();
}
else if ((analogRead(A3) > 800 && analogRead(A0) < 800))
{
   trafficlight2();
}
 

  else if ((analogRead(A3) < 800 && analogRead(A0) < 800))
  {
    normalcondition();
  }
    
  else 
  {
  notraffic();
   
         }
  
} 
 
//Timer loop
ISR(TIMER3_COMPB_vect)
{

//Serial.print("jjjjj\n");
 emergency1 = digitalRead(26);
 emergency2 = digitalRead(34);

SREG = (SREG & 0b01111111);// disable interrupts

if (emergency1 == HIGH || emergency2 == HIGH)
{
 
 
  Serial.print("emergency starts\n");
  myFlag = 1;

}

else {};

sign = digitalRead(sensor_input);
if(sign == HIGH)
{
  Serial.print("Parking\n");
  digitalWrite(parking_red, LOW);
  digitalWrite(parking_green, HIGH);
  }
//interrupts();
}
 
 //Functions


    void trafficlight1()
    {
       digitalWrite (redled2, 1); //Initial condition
digitalWrite (redled1, 0);     //Light traffic 1
digitalWrite (greenled1, 1);

    do
    {
      Serial.println(analogRead(A0)); 
Serial.println(analogRead(A3));
      digitalWrite (greenled1, 1);
    }while (analogRead(A3) < 800 && analogRead(A0) > 800 && myFlag == 0);
    if(myFlag == 1) emergency();
    digitalWrite (greenled1, 1);
   digitalWrite (redled2, 1);
    delay (6000);
    if(myFlag == 1) emergency();
    digitalWrite (redled2, 1);
digitalWrite (greenled1, 0);
delay (500);
digitalWrite (greenled1, 1);
delay (500);
digitalWrite (greenled1, 0);
delay (500);
digitalWrite (greenled1, 1);
delay (500);
digitalWrite (greenled1, 0);
delay (500);
if(myFlag == 1) emergency();
digitalWrite (redled2, 1);
digitalWrite (yellowled1, 1);
delay (3000);
if(myFlag == 1) emergency();
digitalWrite (redled2, 1);
digitalWrite (yellowled1, 0);
delay (200);
digitalWrite (redled1, 1);
delay (1000);
if(myFlag == 1) emergency();
digitalWrite (redled2, 1);
digitalWrite (redled1, 1);
traffic1 = 1;
   }

   
      void trafficlight2()
      { 
        digitalWrite (redled1, 1);
    digitalWrite (redled2, 0);   //Normal condition of traffic light 2
    do
    {
      Serial.println(analogRead(A0)); 
Serial.println(analogRead(A3));
   digitalWrite (greenled2, 1);
    }while (analogRead(A3) > 800 && analogRead(A0) < 800 && myFlag == 0);
    if(myFlag == 1) emergency();
    digitalWrite (redled1, 1);
    digitalWrite (greenled2, 1);
    delay (6000);
    if(myFlag == 1) emergency();
    digitalWrite (redled1, 1);
digitalWrite (greenled2, 0);
delay (500);
digitalWrite (greenled2, 1);
delay (500);
digitalWrite (greenled2, 0);
delay (500);
digitalWrite (greenled2, 1);
delay (500);
digitalWrite (greenled2, 0);
delay (500);
if(myFlag == 1) emergency();
digitalWrite (yellowled2, 1);
delay (3000);
if(myFlag == 1) emergency();
digitalWrite (redled1, 1);
digitalWrite (yellowled2, 0);
delay (200);
digitalWrite (redled2, 1);
delay (1000);
if(myFlag == 1) emergency();
digitalWrite (redled1, 1);
digitalWrite (redled2, 1);
traffic1 = 0;    
  }

  
      void normalcondition1()
      {
      digitalWrite (redled2, 1); //Initial condition
digitalWrite (redled1, 0);     //Light traffic 1
digitalWrite (greenled1, 1);
if(myFlag == 1) emergency();
digitalWrite (redled2, 1);
digitalWrite (greenled1, 1);
delay (6000);
if(myFlag == 1) emergency();
digitalWrite (redled2, 1);
digitalWrite (greenled1, 0);
delay (500);
digitalWrite (greenled1, 1);
delay (500);
digitalWrite (greenled1, 0);
delay (500);
digitalWrite (greenled1, 1);
delay (500);
digitalWrite (greenled1, 0);
delay (500);
if(myFlag == 1) emergency();
digitalWrite (redled2, 1);
digitalWrite (yellowled1, 1);
delay (3000);
digitalWrite (yellowled1, 0);
delay (200);
if(myFlag == 1) emergency();
digitalWrite (redled2, 1);
digitalWrite (redled1, 1);
delay (1000);
if(myFlag == 1) emergency();
digitalWrite (redled2, 1);
digitalWrite (redled1, 1);
      }

void normalcondition2()
{
digitalWrite (redled1, 1);
  digitalWrite (redled2, 0);   //Normal condition of traffic light 2
digitalWrite (greenled2, 1);
if(myFlag == 1) emergency();
digitalWrite (redled1, 1);
digitalWrite (greenled2, 1);
delay (6000);
if(myFlag == 1) emergency();
digitalWrite (redled1, 1);
digitalWrite (greenled2, 0);
delay (500);
digitalWrite (greenled2, 1);
delay (500);
digitalWrite (greenled2, 0);
delay (500);
digitalWrite (greenled2, 1);
delay (500);
digitalWrite (greenled2, 0);
delay (500);
if(myFlag == 1) emergency();
digitalWrite (redled1, 1);
digitalWrite (yellowled2, 1);
delay (3000);
digitalWrite (yellowled2, 0);
if(myFlag == 1) emergency();
digitalWrite (redled1, 1);
delay (200);
digitalWrite (redled2, 1);
delay (1000);
if(myFlag == 1) emergency();
digitalWrite (redled1, 1);
digitalWrite (redled2, 1);
    }
void normalcondition()
{
  if (traffic1 == 0)
  {
    normalcondition1();
    normalcondition2();
  }
  else
  {
    normalcondition2();
    normalcondition1();
  }
}
    
    void notraffic()
    {
     
      Serial.print("notraffic\n");
      digitalWrite (redled2, 0);
    digitalWrite (redled1, 0);
    if(myFlag == 1) emergency();
    digitalWrite (yellowled1, 1);
    digitalWrite (yellowled2, 1);
delay (1000);
digitalWrite (yellowled2, 0);
digitalWrite (yellowled1, 0);
if(myFlag == 1) emergency();
delay (2000);
if(myFlag == 1) emergency();
Serial.print("notraffic end\n");
 
    }
    
void emergency1_act()
{
  Serial.print("emergency 1 starts\n");
  digitalWrite(redled2, 1);
  digitalWrite(greenled1, 1);
  delay(8000);
  digitalWrite(greenled1, 0);
  delay(500);
  digitalWrite(greenled1, 1);
  delay(500);
  digitalWrite(greenled1, 0);
  delay(500);
  digitalWrite(greenled1, 1);
  delay(500);
  digitalWrite(greenled1, 0);
  delay(500);
  digitalWrite(yellowled1, 1);
  delay(1000);
  digitalWrite(yellowled1, 0);
    delay(1000);
    digitalWrite(redled2, 0);
    delay(1000);
   Serial.print("emergency 1 ends\n");
  }

  void emergency2_act()
  {
   Serial.print("emergency 2 starts\n");
   digitalWrite(redled1, 1);
  digitalWrite(greenled2, 1);
  delay(8000);
  digitalWrite(greenled2, 0);
  delay(500);
  digitalWrite(greenled2, 1);
  delay(500);
  digitalWrite(greenled2, 0);
  delay(500);
  digitalWrite(greenled2, 1);
  delay(500);
  digitalWrite(greenled2, 0);
  delay(500);
  digitalWrite(yellowled2, 1);
  delay(1000);
  digitalWrite(yellowled2, 0);
  delay(1000);
  digitalWrite(redled1, 0);
  delay(1000);
   Serial.print("emergency 2 ends\n"); 
    }

    void begin_emergency()
    {
      digitalWrite (greenled1, 0);
 digitalWrite (greenled2, 0);
 digitalWrite (redled1, 0);
 digitalWrite (redled2, 0);
 digitalWrite (yellowled1, 1);
 digitalWrite (yellowled2, 1);
 delay (800);
 digitalWrite (yellowled1, 0);
digitalWrite (yellowled2, 0);
 delay (800);
digitalWrite (yellowled1, 1);
 digitalWrite (yellowled2, 1);
 delay (800);
 digitalWrite (yellowled1, 0);
digitalWrite (yellowled2, 0);
 delay (800);
 digitalWrite (yellowled1, 1);
 digitalWrite (yellowled2, 1);
 delay (800);
 digitalWrite (yellowled1, 0);
digitalWrite (yellowled2, 0);
 delay (1000);

    }
void emergency()
{
  myFlag = 0;
  
 
 if (emergency1 == HIGH && emergency2 == LOW)
 {
 begin_emergency();
 emergency1_act(); 
  }
 else if(emergency1 == LOW && emergency2 == HIGH)
 {
  begin_emergency();
  emergency2_act();
 }
 else if(emergency1 == HIGH && emergency2 == HIGH)
 {
  begin_emergency();
  emergency1_act();
  emergency2_act();
 }
 myFlag = 0;
 
}
