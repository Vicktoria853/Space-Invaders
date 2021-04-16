#include <FastLED.h>

#define LED_PIN 2
#define ENCODER_SWITCH 10
#define NUM_LEDS 64

#define outputA 6
#define outputB 7

// encoder
int counter = 0;
int aState;
int aLastState;
int bnt_was_pressed;

//the ending of the game
bool the_end;

//
struct bullet{
  int x;
  int y;
  unsigned long fired_at;
  bool active; 
};
bullet amuno;

int hearts;
unsigned long finished = 0;



//for all bullets
unsigned long bullet_speed = 500;



struct alien{
  int x;
  int y;
  bool hit;
  };

unsigned long order_to_fire;
alien army[8];
bullet al_amuno[3];
int active_al_bullets;
unsigned long alien_speed;


// the board
CRGB leds[NUM_LEDS];
int matrix[8][8]; // 

void setup() {
              hearts = 3;
              amuno.x = 0;
              amuno.y = 0;
              amuno.active = false;
              for(int i = 0; i < 3; i++)
              {
                al_amuno[i].x = 0;
                al_amuno[i].y = 7;
                al_amuno[i].active = false;    
                al_amuno[i].fired_at = millis();
              }
              active_al_bullets = 0;
              order_to_fire = millis();
              
              bnt_was_pressed = 0;
              FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
              pinMode(outputA, INPUT);
              pinMode(outputB, INPUT);
              pinMode(ENCODER_SWITCH, INPUT_PULLUP);

           //the init of the boards as matrix
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
void moving_bullet();
void moving_aliens();
void round_bullet();
void win();
void lose();

void loop() {
  unsigned long prag = millis(); 
  if(prag> 60000)
  {
    win();
    while(1);
  }
  if(finished + 12000 < prag)
  {
    leds[matrix[7][7 - finished/12000]] = CRGB(0, 255, 0);//colours[0];//CRGB(100, 0, 0);
    finished+=12000;
  }
  if(the_end == true)
  {
    lose();
    while(1);
    }
  else{

  
  rotary_encoder();
  leds[matrix[6][counter]] = CRGB(0, 255, 100);//colours[0];//CRGB(100, 0, 0);
  moving_bullet();
  if(amuno.active == true)
  {
    leds[matrix[amuno.x][amuno.y]] = CRGB(0, 100, 100); //colours[2];// CRGB(10, 100, 100);
  }
  
  for(int i = 0; i < hearts; i++)
  {
    leds[matrix[7][i]] = CRGB(255, 255, 0); //colours[2];// CRGB(10, 100, 100); 
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
  unsigned long temp = millis();
  if(temp > order_to_fire + bullet_speed + 500)
  {
    round_bullet();
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
  leds[matrix[6][counter]] = CRGB(0, 255, 100); //colours[0];//CRGB(100, 0, 0);
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

void round_bullet()
{
  //if(millis() < alien_speed + order_to_fire)
   //    return;
  order_to_fire = millis();
    for(int i = 0; i< 3; i++)
    {/*
      unsigned long temp = millis();
      if(al_amuno[i].fired_at + bullet_speed > temp)
      {*/
        
        leds[matrix[al_amuno[i].x][al_amuno[i].y]] = CRGB(0, 0, 0);
        if(al_amuno[i].x + 1 == 6 )//al_bullets[i].active == true )
        {
          if(al_amuno[i].y == counter)
          {
              hearts--;
              leds[matrix[7][hearts]] = CRGB(0, 0, 0); //colours[2];// CRGB(10, 100, 100); 
              if(hearts == 0)
              {
                lose(); 
                return;
              }
              else 
              {
                  long al_fire = random(8);
                  if(army[al_fire].x == 5)
                    al_fire = random(8);
                  al_amuno[i].x = army[al_fire].x +1;
                  al_amuno[i].y = army[al_fire].y;
                  //al_amuno[i].fired_at = millis();
                  //leds[matrix[al_amuno[i].x][al_amuno[i].y]] = CRGB(220, 20, 60);
                
              }         
          }
          else{
            long al_fire = random(8);
            if(army[al_fire].x == 5)
              al_fire = random(8);
            al_amuno[i].x = army[al_fire].x +1;
            al_amuno[i].y = army[al_fire].y;
            //al_amuno[i].fired_at = millis();
            //leds[matrix[al_amuno[i].x][al_amuno[i].y]] = CRGB(220, 20, 60);
            }
          
          
        }
        else
        {
          al_amuno[i].x += 1;
          //leds[matrix[al_amuno[i].x][al_amuno[i].y]] = CRGB(220, 20, 60);
          
         }
         leds[matrix[al_amuno[i].x][al_amuno[i].y]] = CRGB(220, 20, 60);
      
      
      
    }  
  
}

void moving_bullet()
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
  unsigned long temp_time = millis() - bullet_speed;
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
  unsigned long temp = millis();// - 1000;
  
  if(alien_speed + 5000 > temp)
  { 
          //round_bullet();
          return;  
 }
  
  //int left = 0;
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
            //left+=1;
            
            
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
        army[i].x = 0;
        army[i].hit = false;
    
    }
   
     /*{
      left += 1;
      
    }*/
 
  }
  
  /*if(left == 8)
  {
    for(int i = 0; i< 8; i++)
    {
        army[i].x = 0;
        army[i].y = i;
        army[i].hit = false;
    }
  }*/
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

  
