#include <FastLED.h>

#define LED_PIN 2
#define NUM_LEDS 64

#define outputA 6
#define outputB 7

int counter = 55;
int aState;
int aLastState;

CRGB leds[NUM_LEDS];

void setup() {

    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  Serial.begin(9600);
  
  aLastState = digitalRead(outputA);
  
}
void rotary_encoder()
{
    aState = digitalRead(outputA);
  if( aState != aLastState)
    {
       if(digitalRead(outputB) != aState)
        counter++;
        else
            counter--;
    if(counter > 55)
      {
        counter = 55;
        }
     if(counter < 48)
      {
        counter = 48;
        
        }
   Serial.print("Position: ");
   Serial.println(counter);

   }
   aLastState = aState;
  
  
}

void loop() {

  
  rotary_encoder();
  for(int i = 0; i< NUM_LEDS; i++)
   {
    leds[i] = CRGB(0, 0, 0);   
    }
  leds[counter] = CRGB(100,100, 100);
  FastLED.show();
/*  for(int i = 0; i< NUM_LEDS; i++)
   {
    leds[i] = CRGB(0, 0, 0);
    FastLED.show();
    
    }

 /* for(int i = 0; i < NUM_LEDS; i+=8)
   {
    leds[i] = CRGB(0, 0, 255);
    FastLED.show();
     delay(1000);
    
    }
/*
    for(int i = 0; i < NUM_LEDS; i+=8)
   {
    leds[i] = CRGB(255, 0, 0);
    FastLED.show();
     delay(40);
    
    }*/


}

