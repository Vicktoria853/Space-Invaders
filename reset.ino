void reset() {
  for (int i = 0; i < 8; i++)
  {
    for (int k = 0; k < 8; k++)
    {
      leds[matrix[i][k]] = CRGB(0, 0, 0);
    }
  }
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

  prag = millis();

}
