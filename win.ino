void win()
{
  for (int i = 0; i < 8; i++)
  {
    for (int k = 0; k < 8; k++)
    {
      leds[matrix[i][k]] = CRGB(0, 0, 0);
    }
  }
  int four = 3;
  for (int i = 0; i < 4; i++)
  {
    leds[matrix[i][four]] = CRGB(0, 0, 255);
    leds[matrix[i][7 - four]] = CRGB(0, 0, 255);
    four--;

  }
  four = 0;
  for (int i = 4; i < 8; i++)
  {

    leds[matrix[i][four]] = CRGB(0, 0, 255);
    leds[matrix[i][7 - four]] = CRGB(0, 0, 255);
    four++;

  }
  FastLED.show();



}
