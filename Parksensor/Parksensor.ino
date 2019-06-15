// (c) coderdojo berlin 
// sample for a distanec sensor with LED strip
// led strip (ws2812) and sonic sensor

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// nodeMCU (ESP) pin assignemnt
// board name -> GPIO
// digital pins only

// Which pin on the Arduino is connected to the NeoPixels?
// either use arduino pin numbers, or use ESP_Dx Pins for nodeMCU
#define PIN_STRIP      D8

// How many NeoPixels are attached?
#define NUMPIXELS      16

// define some colors for the strip
// colors will be defined in setup() method
uint32_t col_off = 0;
uint32_t col_green = 0;
uint32_t col_yellow = 0;
uint32_t col_red = 0;


// max distance in cm (centimeters) for the sensor 
long MAX_DISTANCE  = 32;

// percent of distance in green (ok)
# define SAVE_RANGE   40 // means: 40% of max distance is ok

// percent of pixels in yellow (warning)
# define WARNING_RANGE  80 // 30% of MAX_DISTANCE is warning

// percent of pixels in red (critical)
# define CRITICAL_RANGE 90 // rest is critical

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN_STRIP, NEO_GRB + NEO_KHZ800);

// variabled for the sonic sensor
int delayval = 2; // delay microseconds for sonic sensor
// PINs for the sonix sensor. Use pin numbes from arduino, or in case
// of NodeMCU ESP board, the ESP_Dx pin numbers.
#define EchoPin_Sonic D7 // Echo Pin
#define TrigPin_Sonic D6 // Trigger Pin


// initialization of the strip and the distance sensor
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  // This initializes the NeoPixel library.
  strip.begin(); 

  // initialize debug console
  Serial.begin (9600);

  // initialize PINs for sonic sensor
  pinMode(TrigPin_Sonic, OUTPUT);
  pinMode(EchoPin_Sonic, INPUT);

  // set some colors for the strip
  col_off = strip.Color(0, 0, 0);
  col_green = strip.Color(0, 50, 0);
  col_yellow = strip.Color(150, 50, 0);
  col_red = strip.Color(255, 0, 0);
}

// this function returns the current distance in cm
long getDistance() {
  // get the current distance from sonic sensor
  digitalWrite(TrigPin_Sonic, LOW);
  delayMicroseconds(delayval);
  digitalWrite(TrigPin_Sonic, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin_Sonic, LOW);
  long duration = pulseIn(EchoPin_Sonic, HIGH);
  // the distance is the time of the signal / signal speed
  // this way its in cm
  return duration/58.2;
}

// main loop, will be executed allways
void loop() {
  // get the current distance from sonic sensor
  long distance = getDistance();

  // based on distance, calculate the max nr of LED to use
  unsigned long dist_perc = (long(distance * 100) / MAX_DISTANCE);
  // this is the highest LED number which should be switched on based on the distance
  unsigned long max_led = NUMPIXELS - ((NUMPIXELS * dist_perc) / 100); 

  // some debug messages on the serial console
  Serial.println("-------");
  Serial.println(distance);
  Serial.println(MAX_DISTANCE);
  Serial.println(max_led);
  Serial.println(dist_perc);  

  // set each LED of the strip
  for(int led = 0; led < NUMPIXELS; led++){
    // per default, LED is off
    uint32_t cur_color = col_off;
    // iterate over all LEDs
    // start from 0. Check based on current distance and LED pin the color
    // the first LED is green, the last one is MAX_DISTANCE
    if( led <= ((SAVE_RANGE) * NUMPIXELS / 100 )) {
      // we are in the area where of the save range
      // check distance is also here
      if( distance <= MAX_DISTANCE) {
        cur_color = col_green;
      }
    } else if( led <= ((WARNING_RANGE) * NUMPIXELS / 100 )) {
      // we are in the area where of the warning range
      // check distance is also here
      if( distance <= MAX_DISTANCE) {
        cur_color = col_yellow;
      }
    } else  {
      // we are in the area where the critical range is
      // check distance is also here
      if( distance <= MAX_DISTANCE) {
        cur_color = col_red;
      }
    }
    if( led >= max_led ) {
      // all other LED that distance set to 0
      cur_color = col_off;
    }
    // now set the color of the pixel
    strip.setPixelColor(led, cur_color);
  }
  // This sends the updated pixel color to the hardware.
  strip.show(); 
  // if you want, wat a little between the next loop
  delay(0);
}
