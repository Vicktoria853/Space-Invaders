
void show_leds(){
    for(int i = 0; i < 8; i++)
  {
    for(int k = 0; k< 8; k++)
    {
      leds[matrix[i][k]] = CRGB(0,0, 0);
    } 
  }
  
  leds[matrix[6][counter]] = CRGB(0, 255, 100);
  if(hero_lazer.active == true)
  {
    leds[matrix[hero_lazer.x][hero_lazer.y]] = CRGB(0, 100, 100);
  }
  for(int i = 0; i < hearts; i++)
  {
    leds[matrix[7][i]] = CRGB(255, 255, 0); 
  }
   for(int i = 0; i< 8; i++)
   {
    if(army[i].hit == false)
    {
      leds[matrix[army[i].x][army[i].y]] = CRGB(255, 0, 0);
    }
    
    }
     for(int i = 0; i< parts; i++){
    leds[matrix[7][7 -i]] = CRGB(0, 255, 0);}
    leds[matrix[6][counter]] = CRGB(0, 255, 100); 
     leds[matrix[ hero_lazer.x ][ hero_lazer.y]] = CRGB(0, 255, 255);
     for(int i = 0; i< 3; i++)
     {
      leds[matrix[alien_lazer[i].x][alien_lazer[i].y]] = CRGB(220, 20, 60);
      }
    if(hero_lazer.active == true)
  {
    leds[matrix[hero_lazer.x][hero_lazer.y]] = CRGB(0, 100, 100);
  }
  
  
  }


