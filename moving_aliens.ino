void moving_aliens()
{
  temp = millis();// - 1000;
  
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
        if(army[i].y == hero_lazer.y && army[i].x >= hero_lazer.x)
        { 
          Serial.println(alien_speed);
            army[i].hit = true;
            hero_lazer.active = false;
            leds[matrix[hero_lazer.x][hero_lazer.y]] = CRGB(0, 0, 0);
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
   
 alien_speed = millis();
 // FastLED.show();
  
}
}

