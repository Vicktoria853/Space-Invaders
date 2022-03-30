void rotary_switch() {

  if (digitalRead(ENCODER_SWITCH) == LOW )
  {
    time_now = millis();
    
    if (hold + hold_timer < time_now)
      {
        reset();
        return;
      }

    if (bnt_was_pressed == 0 && hero_lazer.active == false)
    {
      hero_lazer.x = 5 ; // x
      hero_lazer.y = counter; // y
      hero_lazer.active = true;
      hero_lazer.fired_at = millis();
      bnt_was_pressed = 1;
      

    }
  }
  else
  {
    bnt_was_pressed = 0;
    hold = millis();
  }

}

