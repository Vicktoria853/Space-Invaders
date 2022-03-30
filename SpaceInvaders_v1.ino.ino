#include <FastLED.h>

#define LED_PIN 42
#define ENCODER_SWITCH 36
#define NUM_LEDS 64

#define outputA 40
#define outputB 38

// encoder
int counter = 0;
int aState;
int aLastState;
int bnt_was_pressed;
unsigned long hold;
unsigned long hold_timer = 1800;

//the ending of the game
bool the_end;
unsigned long prag;
unsigned long prag_timer;
unsigned long prag_end = 60000;
unsigned long temp;
unsigned long time_now;
unsigned long temp_time;

//++++++++++++++++++++++++++++++++++++++++++++
struct bullet {
  int x;
  int y;
  unsigned long fired_at;
  bool active;
};
bullet hero_lazer;

int hearts;
unsigned long part_time;
int parts;
int interval_part = 12000; // 12 seconds
int all_parts = 5;



//for all bullets
unsigned long bullet_speed = 500;



struct alien {
  int x;
  int y;
  bool hit;
};

unsigned long order_to_fire;
alien army[8];
bullet alien_lazer[3];
//int active_al_bullets;
unsigned long alien_speed;


// the board
CRGB leds[NUM_LEDS];
int matrix[8][8]; //

void setup() {
  parts = 0;
  hearts = 3;
  hero_lazer.x = 0;
  hero_lazer.y = 0;
  hero_lazer.active = false;
  for (int i = 0; i < 3; i++)
  {
    alien_lazer[i].x = 0;
    alien_lazer[i].y = 7;
    alien_lazer[i].active = false;
    alien_lazer[i].fired_at = millis();
  }
  //active_al_bullets = 0;
  order_to_fire = millis();

  bnt_was_pressed = 0;

  // <<<<  init of encoder and leds >>>>
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  pinMode(ENCODER_SWITCH, INPUT_PULLUP);


  // <<<<<<<<<< the init of the boards as matrix >>>>>>>>>>>
  for (int i = 0; i < 64; i += 8)
  {
    if ((i / 8) % 2 == 0)
    {
      for (int k = i + 7; k >= i; k--)
      {
        matrix[ (i / 8) ][7 - k % 8] = k;
      }
    }
    else {
      for (int k = i; k <= i + 7; k++)
      {
        matrix[ (i / 8)][k % 8] = k;
      }
    }
  }
  // <<<<<<<<<<<<<<<<<< >>>>>>>>>>>>>>>>>>

  for (int i = 0; i < 8; i++)
  {
    army[i].hit = false;
    army[i].x  = 0;
    army[i].y = i;
    //leds[matrix[0][i]] = colours[1];
  }

  aLastState = digitalRead(outputA);
  alien_speed = millis();
  the_end = false;
  prag == millis();


}


void rotary_encoder();
void rotary_switch();

void moving_bullet();
void moving_aliens();
void round_bullet();
void win();
void lose();
void reset();
void show_leds();

void loop() {
  rotary_switch();
  
  prag_timer = millis();
  
  if ((prag_timer > prag_end + prag ) && (the_end == false))
  {
    win();
  }
  else if (the_end == true)
  {
    lose();
    //rotary_switch();
    //while(1);
  }
  else {
    if (part_time + interval_part < prag_timer)
    {
      parts++;
      part_time += interval_part;
    }
    rotary_encoder();
    //rotary_switch();

    temp = millis();
    if (temp > order_to_fire + bullet_speed + 1000)
    {
      round_bullet();
    }
    //   for(int i = 0; i< parts; i++){
    //    leds[matrix[7][7 -i]] = CRGB(0, 255, 0);}
    moving_bullet();
    moving_aliens();
    show_leds();
    FastLED.show();
  }
}



