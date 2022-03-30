
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

