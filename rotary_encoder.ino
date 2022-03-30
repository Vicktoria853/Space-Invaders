
void rotary_encoder()
{
    aState = digitalRead(outputA);
   //leds[matrix[6][counter]] = CRGB(0, 0, 0);
  if( aState != aLastState)
    {
       if(digitalRead(outputB) != aState)
        counter--;
        else
            counter++;
    if(counter > 7)
      {
        counter =7;
        }
     if(counter < 0)
      {
        counter = 0;
        
        }
  //leds[matrix[6][counter]] = CRGB(0, 255, 100); //colours[0];//CRGB(100, 0, 0);
   }
   aLastState = aState;
   
   
   
     
}

