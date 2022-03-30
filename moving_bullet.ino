
void moving_bullet()
{
  
  if(hero_lazer.active == false)
  {
    return;
  }
  if(army[hero_lazer.y].x >= hero_lazer.x)
  {
      hero_lazer.active = false; 
      army[hero_lazer.y].hit = true; 
      //leds[matrix[ hero_lazer.x ][ hero_lazer.y]] = CRGB(0, 0, 0);
      return;
  }
  temp_time = millis();
  if(hero_lazer.x < 0)
  {
    
    hero_lazer.active = false;
  }
  
  else if(( temp_time> hero_lazer.fired_at + bullet_speed) && hero_lazer.active == true)
  {
    //leds[matrix[ hero_lazer.x ][ hero_lazer.y]] = CRGB(0, 0, 0);
    hero_lazer.x -= 1;
    if(hero_lazer.x < 0)
    {
        hero_lazer.active = false;
        return;
      }
    //leds[matrix[ hero_lazer.x ][ hero_lazer.y]] = CRGB(0, 255, 255);
    hero_lazer.fired_at = millis();
    
   }
}

