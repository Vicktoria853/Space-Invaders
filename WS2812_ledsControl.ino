#include <FastLED.h>

#define LED_PIN 2
#define ENCODER_SWITCH 10
#define NUM_LEDS 64

#define outputA 6
#define outputB 7

int counter = 55;
int aState;
int aLastState;
//int bullets[3];
//int num_bullets;
//unsigned long firing_bullets[3];


int bullet;
unsigned long firing_bullet;

CRGB leds[NUM_LEDS];

void setup() {

   FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  pinMode(ENCODER_SWITCH, INPUT);
  Serial.begin(9600);
  
  aLastState = digitalRead(outputA);
  //num_bullets = 0;
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


void moving_bullets(int *bull, unsigned long *firing)
{
  if(*bull < 0)
  {
    return;
    }
    unsigned long temp = millis();
   if(temp - 1000 > *firing )
   {
    switch(*bull / 8)
    {
      case 4:
        *bull -= 39 - *bull % 8;
        break;
      case 3:
        *bull -= 31 - *bull % 8;
        break;
      case 2:
        *bull -= 23 - *bull % 8;
        break;
      case 1:
        *bull -= 15 - *bull % 8;
        break;
      case 0:
        *bull -= 7 -* bull % 8;
        break;
      }

    
    /*if(bullet / 8 == 6)
    {
      bullet -= 39 - bullet % 8;
     }
     else if(bullet / 8 == 6)
    {
      bullet -= 39 - bullet % 8;
     }
    */
    if(*bull < 0)
    {
      return;
    }
       }
    leds[*bull] = CRGB(100, 0, 0);
    *firing = millis();

  /*
  if(num_bullets == 0)  
  {
   return;    
   }
  for(int i = 0; i < num_bullets; i++ )
    {
      if(firing_bullets[i] + 1000 >= millis())
      {
        bullets[i] -= 8;
        if(bullets[i] < 0)
        {
          int temp = bullets[num_bullets-1];
          bullets[num_bullets - 1] = bullets[i];
          bullets[i] = temp;
          num_bullets--;
          unsigned long sec_temp = firing_bullets[num_bullets - 1];
          firing_bullets[num_bullets - 1] = firing_bullets[i];
          firing_bullets[i] = sec_temp;            
        }
        else
          {
              firing_bullets[i] = millis();
              leds[bullets[i]] = CRGB(100, 0, 0);
           }
      
      }
      else{
        
        leds[bullets[i]] = CRGB(100, 0, 0);
        }
    }
    //FastLED.show();
    */
}


void loop() {

  
  rotary_encoder();
  for(int i = 0; i< NUM_LEDS; i++)
   {
    leds[i] = CRGB(0, 0, 0);   
    }
  leds[counter] = CRGB(100,100, 100);
  
  if(digitalRead(ENCODER_SWITCH) == HIGH)
  {
          bullet = 47 - counter % 8;
          firing_bullet = millis();
   }
  moving_bullets(&bullet, &firing_bullet);
  FastLED.show();


}

