#include <FastLED.h>

#define LED_PIN 2
#define ENCODER_SWITCH 10
#define NUM_LEDS 64

#define outputA 6
#define outputB 7

bool the_end;

struct bullet{
  int x;
  int y;
  unsigned long fired_at;
  bool hero;
  bool active; 
};
bullet amuno;
int bullet_speed = 500;

struct alien{
  int x;
  int y;
  bool hit;
  };

alien army[8];
unsigned long alien_speed;

int counter = 0;
int aState;
int aLastState;
//hero, aliens, bullets X2 hearts
CRGB colours[5];



int bnt_was_pressed;


CRGB leds[NUM_LEDS];
int matrix[8][8]; // 

void setup() {
             colours[0] = (0, 100, 100); // hero
             colours[1] = (255, 0, 0); // alien
             colours[2] = (10, 100, 100); // hero's bullet
             colours[3] = (100, 100, 0); // aliens' bullet
             colours[4] = (10, 100, 0); // hearts == live
              amuno.x = 0;
              amuno.y = 0;
              amuno.active = false;
              amuno.hero = true; // who shots it
              amuno.x = 5;
              amuno.y = 0;
              bnt_was_pressed = 0;
              FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
              pinMode(outputA, INPUT);
              pinMode(outputB, INPUT);
              pinMode(ENCODER_SWITCH, INPUT_PULLUP);
              Serial.begin(9600);
              //>>>>>>>>>>
           
              for(int i = 0; i < 64; i+=8)
              {
                if((i/8) % 2 == 0)
                {  
                  for(int k = i + 7; k >=i; k--)
                  {
                  matrix[ (i/8) ][7-k%8] = k;
                  }
                }
                else{
                  for(int k = i; k <= i + 7; k++)
                  {
                     matrix[ (i/8)][k % 8] = k;
                  }
                }
              }
              for(int i = 0; i< 8; i++)
              {
                    army[i].hit = false;
                    army[i].x  = 0;
                    army[i].y = i;
                    //leds[matrix[0][i]] = colours[1];
              }
              
              aLastState = digitalRead(outputA);
              alien_speed = millis();
              the_end = false;
             
}


void rotary_encoder();
void moving_bullets();
void moving_aliens();
void win();
void lose();

void loop() {
  if(the_end == true)
  {
    while(1);
    }
  else{

  
  rotary_encoder();
  leds[matrix[6][counter]] = colours[0];//CRGB(100, 0, 0);
  moving_bullets();
  if(amuno.active == true)
  {
    leds[matrix[amuno.x][amuno.y]] = colours[2];// CRGB(10, 100, 100);
  }
  
  
   for(int i = 0; i< 8; i++)
   {
    //Serial.println("Hi");
    if(army[i].hit == false)
    {
      leds[matrix[army[i].x][army[i].y]] = CRGB(255, 0, 0);
      //Serial.println(army[i].x);
      //Serial.println(army[i].y);
    }
    
    }
   moving_aliens();
  FastLED.show();
  }


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
  leds[matrix[6][counter]] = colours[0];//CRGB(100, 0, 0);
   }
   aLastState = aState;
   
   if(digitalRead(ENCODER_SWITCH) == LOW )
   {
      if(bnt_was_pressed == 0 && amuno.active == false)
      {
         Serial.println("The button is pressed!");
         amuno.x = 5 ; // x
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
  {
    return;
  }
  if(army[amuno.y].x >= amuno.x)
  {
      amuno.active = false; 
      army[amuno.y].hit = true; 
      leds[matrix[ amuno.x ][ amuno.y]] = CRGB(0, 0, 0);
      return;
  }
  unsigned long temp_time = millis() - 500;
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
    leds[matrix[ amuno.x ][ amuno.y]] = CRGB(0, 255, 255);
    amuno.fired_at = millis();
    
   }
}

void moving_aliens()
{
  
  //Serial.println("The beginning");
  unsigned long temp = millis();// - 1000;
  
  if(alien_speed + 5000 > temp)
  {
    
          return;
        
 }
  
  int left = 0;
  for(int i = 0; i< 8; i++)
  {
    
    if(army[i].hit == false)
    {
        leds[matrix[army[i].x][army[i].y]] = CRGB(0, 0, 0);
        army[i].x +=1;
        if(army[i].y == amuno.y && army[i].x >= amuno.x)
        { 
          Serial.println(alien_speed);
            army[i].hit = true;
            amuno.active = false;
            leds[matrix[amuno.x][amuno.y]] = CRGB(0, 0, 0);
            left+=1;
            
            
        }
        else
          leds[matrix[army[i].x][army[i].y]] = CRGB(255, 0, 0);
       

        if(army[i].x == 6)
        {
          lose();
        }

    } 
    
    else
    {
      left += 1;
      
    }
 
  }
  
  if(left == 8)
  {
    for(int i = 0; i< 8; i++)
    {
        army[i].x = 0;
        army[i].y = i;
        army[i].hit = false;
    }
  }
 alien_speed = millis();
 // FastLED.show();
  
}

void win()
{
  for(int i = 0; i < 8; i++)
  {
    for(int k = 0; k< 8; k++)
    {
      leds[matrix[i][k]] = CRGB(0,0, 0);
    } 
  }
  int four = 3;
  for(int i = 0; i < 4; i++)
  {
      leds[matrix[i][four]] = CRGB(0,0, 255);
      leds[matrix[i][7 - four]] = CRGB(0,0, 255);
      four--;
    
  }
  four = 0;
    for(int i = 4; i < 8; i++)
  {
      
      leds[matrix[i][four]] = CRGB(0,0, 255);
      leds[matrix[i][7 - four]] = CRGB(0,0, 255);
      four++;
      
  }
  FastLED.show();
  the_end = true;
  
  
}



void lose()
{
  
  for(int i = 0; i < 8; i++)
  {
    for(int k = 0; k< 8; k++)
    {
      leds[matrix[i][k]] = CRGB(0,0, 0);
    } 
  }
  int four = 0;
  for(int i = 0; i < 4; i++)
  {
      leds[matrix[i][four]] = CRGB(255,0, 0);
      leds[matrix[i][7 - four]] = CRGB(255,0, 0);
      four++;
    
  }
    for(int i = 4; i < 8; i++)
  {
      four--;
      leds[matrix[i][four]] = CRGB(255,0, 0);
      leds[matrix[i][7 - four]] = CRGB(255,0, 0);
      
    
  }
  FastLED.show();
  the_end = true;
    
}

  
