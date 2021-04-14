#include <FastLED.h>

#define LED_PIN 2
#define ENCODER_SWITCH 10
#define NUM_LEDS 64

#define outputA 6
#define outputB 7


struct bullet{
  int x;
  int y;
  unsigned long fired_at;
  bool hero;
  bool active; 
};

bullet amuno;


int counter = 0;
int aState;
int aLastState;
//int bullets[3];
//int num_bullets;
//unsigned long firing_bullets[3];



int bnt_was_pressed;


CRGB leds[NUM_LEDS];
int matrix[8][8]; // 

void setup() {
              amuno.x = 0;
              amuno.y = 0;
              amuno.active = false;
              amuno.hero = true; // who shots it
              bnt_was_pressed = 0;
              FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
              pinMode(outputA, INPUT);
              pinMode(outputB, INPUT);
              pinMode(ENCODER_SWITCH, INPUT_PULLUP);
              //Serial.begin(9600);
              //>>>>>>>>>>
     /*       
              for(int i = 0; i < 64; i+=8)
              {
                if((i/8) % 2 == 0)
                {  
                  for(int k = i + 7; k >=i; k--)
                  {
                  matrix[ (i/8)%2 ][7-k%8] = k;
                  }
                }
                else{
                  for(int k = i; k <= i + 7; k++)
                  {
                     matrix[ (i/8)%2][k % 8] = k;
                  }
                  
                 
                  }
                  
              }*/

              for(int i = 7; i >=0; i--)
              {
                  matrix[0][7-i] = i;
              }
              //<<<<<<<<
              for(int i = 8; i <=15; i++)
              {
                  matrix[1][i % 8] = i;
              }
              //>>>>>>>
              for(int i = 23; i >=16; i--)
              {
                  matrix[2][23-i] = i;
              }
              //<<<<<<<<
              for(int i = 24; i <=31; i++)
              {
                  matrix[3][i % 8] = i;
              }
              //>>>>>>>>
              for(int i = 39; i >=32; i--)
              {
                  matrix[4][39-i] = i;
              }
              //<<<<<<<<
              for(int i = 40; i <=47; i++)
              {
                  matrix[5][i%8] = i;
              }
              //>>>>>>>>>
              for(int i = 55; i >=48; i--)
              {
                  matrix[6][55-i] = i;
              }
              //<<<<<<<<
              for(int i = 56; i <=63; i++)
              {
                  matrix[7][i%8] = i;
              }
              //>>>>>>>>>>>>
              
              
              aLastState = digitalRead(outputA);
              //num_bullets = 0;
             
}


void rotary_encoder()
{
    aState = digitalRead(outputA);
   leds[matrix[6][counter]] = CRGB(0, 0, 0);
  if( aState != aLastState)
    {
       if(digitalRead(outputB) != aState)
        counter--;
        else
            counter++;
    if(counter > 7)
      {
        counter =7;
        }
     if(counter < 0)
      {
        counter = 0;
        
        }
   Serial.print("Position: ");
   Serial.println(counter);
  leds[matrix[6][counter]] = CRGB(100, 0, 0);
   }
   aLastState = aState;
   
   if(digitalRead(ENCODER_SWITCH) == LOW )
   {
      if(bnt_was_pressed == 0 && amuno.active == false)
      {
         Serial.println("The button is pressed!");
         amuno.x = 6; // x
         amuno.y = counter; // y
         amuno.active = true;
         amuno.fired_at = millis();
         bnt_was_pressed = 1;
         
      }
   }
   else
   {
    bnt_was_pressed = 0;
    }
     
}


void moving_bullets()
{
  if(amuno.active == false)
    return;
  unsigned long temp_time = millis() - 1000;
  if(amuno.x < 0)
  {
    
    amuno.active = false;
  }
  
  else if(( temp_time> amuno.fired_at) && amuno.active == true)
  {
    leds[matrix[ amuno.x ][ amuno.y]] = CRGB(0, 0, 0);
    amuno.x -= 1;
    if(amuno.x < 0)
    {
        amuno.active = false;
        return;
      }
    leds[matrix[ amuno.x ][ amuno.y]] = CRGB(10, 100, 100);
    amuno.fired_at = millis();
    
   }
}


void loop() {

/*
for(int i = 0; i< 8; i++)
{
  for(int k = 0; k < 8; k++)  
  {
    leds[matrix[i][k]] = CRGB(200, 0, 0);
    delay(50);
    FastLED.show();
   
  }
  }
  */
  //leds = CRGB(100, 100, 100);
  rotary_encoder();
  leds[matrix[6][counter]] = CRGB(100, 0, 0);
  moving_bullets();
  if(amuno.active == true)
  {
    leds[matrix[amuno.x][amuno.y]] = CRGB(10, 100, 100);
    
   }
  FastLED.show();
  


}

