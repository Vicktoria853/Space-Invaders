void round_bullet()
{

  order_to_fire = millis();
  for (int i = 0; i < 3; i++)
  {
    //leds[matrix[alien_lazer[i].x][alien_lazer[i].y]] = CRGB(0, 0, 0);
    if (alien_lazer[i].x + 1 == 6 ) //al_bullets[i].active == true )
    {
      if (alien_lazer[i].y == counter)
      {
        hearts--;
        //leds[matrix[7][hearts]] = CRGB(0, 0, 0); //colours[2];// CRGB(10, 100, 100);
        if (hearts == 0)
        {
          lose();
          return;
        }
        else
        {
          long al_fire = random(8);
          if (army[al_fire].x == 5)
            al_fire = random(8);
          alien_lazer[i].x = army[al_fire].x + 1;
          alien_lazer[i].y = army[al_fire].y;
          //alien_lazer[i].fired_at = millis();
          //leds[matrix[alien_lazer[i].x][alien_lazer[i].y]] = CRGB(220, 20, 60);

        }
      }
      else {
        long al_fire = random(8);
        if (army[al_fire].x == 5)
          al_fire = random(8);
        alien_lazer[i].x = army[al_fire].x + 1;
        alien_lazer[i].y = army[al_fire].y;
        //alien_lazer[i].fired_at = millis();
        //leds[matrix[alien_lazer[i].x][alien_lazer[i].y]] = CRGB(220, 20, 60);
      }


    }
    else
    {
      alien_lazer[i].x += 1;
      //leds[matrix[alien_lazer[i].x][alien_lazer[i].y]] = CRGB(220, 20, 60);

    }
    //leds[matrix[alien_lazer[i].x][alien_lazer[i].y]] = CRGB(220, 20, 60);



  }

}

