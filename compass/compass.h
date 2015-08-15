#include <Arduino.h>

//#define uint8_t byte

// int constants for lights
#define COMPASS_LED_BEHIND_LEFT 0
#define COMPASS_LED_LEFT 1
#define COMPASS_LED_AHEAD_LEFT 2
#define COMPASS_LED_AHEAD 3
#define COMPASS_LED_AHEAD_RIGHT 4
#define COMPASS_LED_RIGHT 5
#define COMPASS_LED_BEHIND_RIGHT 6
#define COMPASS_LED_MARKER 7

void declare_compass(void);

void setup_compass(void);

void setDirectionByte(byte &leds, float heading);

// Eventually, I want to use this to avoid edge-jitter when 
// someone is near a border between two LEDs
class compassLeds{
  public:

  private:
    float _last_deg;

};