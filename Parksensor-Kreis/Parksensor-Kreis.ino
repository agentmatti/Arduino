// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached?
#define NUMPIXELS      16

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
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


// variabled for the sonic sensor
int delayval = 2; // delay for half a second
#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define LEDPin 13 // Onboard LED
int maxRange = 200;
int minRange = 0;
long duration,distance;

// initialization of the strip and the distance sensor
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  strip.begin(); // This initializes the NeoPixel library.
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration/58.2;

  char log[1000];
  
  // define some colors
  uint32_t col_off = strip.Color(0, 0, 0);
  uint32_t col_green = strip.Color(0, 50, 0);
  uint32_t col_yellow = strip.Color(150, 50, 0);
  uint32_t col_red = strip.Color(255, 0, 0);

  // based on distance, calculate the max nr of LED to use
  unsigned long dist_perc = (long(distance * 100) / MAX_DISTANCE);
  unsigned long max_led = NUMPIXELS - ((NUMPIXELS * dist_perc) / 100); 
  
  Serial.println("-------");
  Serial.println(distance);
  Serial.println(MAX_DISTANCE);
  Serial.println(max_led);
  Serial.println(dist_perc);
  
  
  for(int led = 0; led < NUMPIXELS; led++){
    // per default, LED is off
    uint32_t cur_color = col_off;
    // iterate over all LEDs
    // start from 0. Check based on current distance and LED pin the color
    // the first LED is green, the last one is MAX_DISTANCE
    if( led <= ((SAVE_RANGE) * NUMPIXELS / 100 )) {
      // we are in the are where the save range is
      // check distance is also here
      if( distance <= MAX_DISTANCE) {
        cur_color = col_green;
      }
    } else if( led <= ((WARNING_RANGE) * NUMPIXELS / 100 )) {
      // we are in the are where the swarningave range is
      // check distance is also here
      if( distance <= MAX_DISTANCE) {
        cur_color = col_yellow;
      }
    } else  {
      // we are in the are where the critical range is
      // check distance is also here
      if( distance <= MAX_DISTANCE) {
        cur_color = col_red;
      }
    }
    if( led >= max_led ) {
      // all other LED that distance set to 0
      cur_color = col_off;
    }
    strip.setPixelColor(led, cur_color);
  }
  strip.show(); // This sends the updated pixel color to the hardware.
  delay(0);
}
