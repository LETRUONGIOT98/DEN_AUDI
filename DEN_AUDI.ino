
#include "Arduino.h"
#include <FastLED.h>

#define LED_PIN 3 //Led Pin
#define BrakeSignal 4 //Phanh
#define LeftSignal 5 //XI NHAN TRÁI
#define RightSignal 6 //XI NHAN PHẢI
#define ReverseSignal 7 //KHẨN CẤP

#define NUM_LEDS 9 //Số led
#define BlinkerLEDs 3 //STOP

int BlinkerSpeed = 35; //Tốc độ đèn chạy xi nhan
int BlinkerOffDelay = 250; //Thời gian tắt Xi Nhan

int StartupSpeed = 25;

CRGB leds[NUM_LEDS];


void setup() 
{
FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
pinMode(BrakeSignal, INPUT);
pinMode(LeftSignal, INPUT);
pinMode(RightSignal, INPUT);
pinMode(ReverseSignal, INPUT);


  for (int i = 0; i < (NUM_LEDS/2); i++)
  {
    leds[i] = CRGB(30, 0, 0);
    leds[i-1] = CRGB(0, 0, 0);
    leds[(NUM_LEDS-1)-i] = CRGB(30, 0, 0);
    leds[(NUM_LEDS)-i] = CRGB(0, 0, 0);
    FastLED.show();
    delay (StartupSpeed);    
  }
  
  for (int j = ((NUM_LEDS/2)-1); j >= 0; j--)
  {
    leds[j] = CRGB(30, 0, 0);
    leds[(NUM_LEDS/2-1)+((NUM_LEDS/2)-j)] = CRGB(30, 0, 0);
    FastLED.show();
    delay (StartupSpeed);    
  }

  for (int j = ((NUM_LEDS/2)-1); j >= 0; j--)
  {
    leds[j] = CRGB(255, 0, 0);
    leds[(NUM_LEDS/2-1)+((NUM_LEDS/2)-j)] = CRGB(255, 0, 0);
    FastLED.show();
    delay (StartupSpeed);    
  }

  for (int j = 255; j >= 60; j--)
  {  
    for (int i = 0; i < NUM_LEDS; i++)
    {
    leds[i] = CRGB(j, 0, 0);
    }
    FastLED.show();  
    delay (5);
  }
}


void loop() 
{
if((digitalRead(ReverseSignal)==1)&&(digitalRead(BrakeSignal)==0)) //Reverse Light
{   
Reverse();
}

if((digitalRead(ReverseSignal)==1)&&(digitalRead(BrakeSignal)==1)) //Brake Light
{   
BrakeFull();
}

if(digitalRead(ReverseSignal)==0)
{
if((digitalRead(LeftSignal)==0)&&(digitalRead(RightSignal)==0)&&(digitalRead(BrakeSignal)==0)) //Park Light
{   
ParkFull();
}

if((digitalRead(BrakeSignal)==1)&&(digitalRead(LeftSignal)==0)&&(digitalRead(RightSignal)==0)) //Brake Light
{
BrakeFull();
}
    
if((digitalRead(LeftSignal)==1)&&(digitalRead(RightSignal)==0)&&(digitalRead(BrakeSignal)==0)) //Left Blinker
{
LeftDim();
RightLit(); 
LeftBlinker();
LeftDim();
delay (BlinkerOffDelay);
}

if((digitalRead(RightSignal)==1)&&(digitalRead(LeftSignal)==0)&&(digitalRead(BrakeSignal)==0)) //Right Blinker
{
RightDim();
LeftLit();
RightBlinker();
RightDim();
delay (BlinkerOffDelay);
}

if((digitalRead(LeftSignal)==1)&&(digitalRead(RightSignal)==0)&&(digitalRead(BrakeSignal)==1)) //Left Blinker & Brake
{
LeftDim();
RightFull(); 
LeftBlinker();
LeftDim();
delay (BlinkerOffDelay);
}

if((digitalRead(RightSignal)==1)&&(digitalRead(LeftSignal)==0)&&(digitalRead(BrakeSignal)==1)) //Right Blinker & Brake
{
RightDim();
LeftFull();
RightBlinker();
RightDim();
delay (BlinkerOffDelay);
}

if((digitalRead(LeftSignal)==1)&&(digitalRead(RightSignal)==1)&&(digitalRead(BrakeSignal)==0)) //Dual Blinker / Hazard
{
LeftDim();
RightDim();
ParkMiddle();
DualBlinker();
LeftDim();
RightDim();
delay (BlinkerOffDelay);
}

if((digitalRead(LeftSignal)==1)&&(digitalRead(RightSignal)==1)&&(digitalRead(BrakeSignal)==1)) //Dual Blinker / Hazard + Brake
{
LeftDim();
RightDim();
BrakeMiddle();
DualBlinker();
LeftDim();
RightDim();
delay (BlinkerOffDelay);
}
}
}




























void Reverse()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(255, 255, 255);
  }
    FastLED.show();  
}

void BrakeFull()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(255, 0, 0);
  }
    FastLED.show();  
}

void BrakeMiddle()
{
  for (int i = BlinkerLEDs; i < (NUM_LEDS - BlinkerLEDs); i++)
  {
    leds[i] = CRGB(255, 0, 0);
  }
    FastLED.show();  
}

void ParkFull()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(60, 0, 0);
  }
    FastLED.show();
}

void ParkMiddle()
{
  for (int i = BlinkerLEDs; i < (NUM_LEDS - BlinkerLEDs); i++)
  {
    leds[i] = CRGB(60, 0, 0);
  }
    FastLED.show();  
}

void LeftBlinker()
{
  for (int i = (BlinkerLEDs-1); i >= 0; i--)
  {
    leds[i] = CRGB(255, 165, 0);
    FastLED.show();
    delay (BlinkerSpeed);    
  }
}

void LeftDim()
{
  for (int i = 0; i < BlinkerLEDs; i++)
  {
    leds[i] = CRGB(0, 0, 0);
  }
    FastLED.show();
}

void LeftLit()
{
  for (int i = 0; i < (NUM_LEDS - BlinkerLEDs); i++)
  {
    leds[i] = CRGB(75, 0, 0);
  }
    FastLED.show();
}

void LeftFull()
{
  for (int i = 0; i < (NUM_LEDS - BlinkerLEDs); i++)
  {
    leds[i] = CRGB(255, 0, 0);
  }
    FastLED.show();
}

void RightBlinker()
{
  for (int i = (NUM_LEDS - BlinkerLEDs); i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(255, 165, 0);
    FastLED.show();
    delay (BlinkerSpeed);
  }
}

void RightDim()
{
   for (int i = (NUM_LEDS - BlinkerLEDs); i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(0, 0, 0);
  }
    FastLED.show();
}

void RightLit()
{
  for (int i = BlinkerLEDs; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(75, 0, 0);
  }
    FastLED.show();
}

void RightFull()
{
  for (int i = BlinkerLEDs; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(255, 0, 0);
  }
    FastLED.show();
}

void DualBlinker()
{
  for (int i = (BlinkerLEDs-1); i >= 0; i--)
  {
    leds[i] = CRGB(255, 165, 0);
    leds[NUM_LEDS-1-i] = CRGB(255, 165, 0);
    FastLED.show();
    delay (BlinkerSpeed);
  }
}
