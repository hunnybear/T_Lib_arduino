#include <compass.h>

void setDirectionByte(byte &leds, float heading )
{
  // Normalize the heading to 0 to +2*pi radians
  heading = fmod((double)heading,2*M_PI);

  if (heading < 0.0) {
    heading = 2*M_PI + heading;
  }

  if (heading < radians(22.5))
  {
    bitSet(leds, COMPASS_LED_AHEAD);
  }
  else if (heading < radians(67.5))
  {
    bitSet(leds, COMPASS_LED_AHEAD_RIGHT);
  }
  else if (heading < radians(112.5))
  {
    bitSet(leds, COMPASS_LED_RIGHT);
  }
  else if (heading < radians(157.5))
  {
    bitSet( leds, COMPASS_LED_BEHIND_RIGHT);
  }
  else if (heading < radians(207.5))
  {
    //setting both 'behind' leds to on
    bitSet(leds, COMPASS_LED_BEHIND_RIGHT);
    bitSet(leds, COMPASS_LED_BEHIND_LEFT);
  }
  else if (heading < radians(247.5))
  {
    bitSet(leds, COMPASS_LED_BEHIND_LEFT);
  }
  else if (heading < radians(292.5))
  {
    bitSet(leds, COMPASS_LED_LEFT);
  }
  else if (heading < radians(337.5))
  {
    bitSet(leds, COMPASS_LED_AHEAD_LEFT);
  }
  else
  {
    bitSet(leds, COMPASS_LED_AHEAD);
  }

}