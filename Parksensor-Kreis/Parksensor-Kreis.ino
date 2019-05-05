// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// nodeMCU pin assignemnt
// board name -> GPIO
// digital pins only
const uint8_t ESP_D0_PIN = 16;  // User-wake
const uint8_t ESP_D1_PIN = 5;
const uint8_t ESP_D2_PIN = 4;
const uint8_t ESP_D3_PIN = 0;   
const uint8_t ESP_D4_PIN = 2;   // TXD1 // also LED
const uint8_t ESP_D5_PIN = 14;  // HSPICLK
const uint8_t ESP_D6_PIN = 12;  // HSPIQ
const uint8_t ESP_D7_PIN = 13;  // RXD2 - HSPID
const uint8_t ESP_D8_PIN = 15;  // TXD2 - HSPID
const uint8_t ESP_D9_PIN = 3;   // RXD0
const uint8_t ESP_D10_PIN = 1;   // TXD0
const uint8_t ESP_D11_PIN = 9;   // SPIHD
const uint8_t ESP_D12_PIN = 10;  // SPIWP


// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
// either use arduino pin numbers, or use ESP_Dx Pins for esp8266
#define PIN_STRIP      6
// ESP sample
// #define PIN ESP_D6_PIN

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
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN_STRIP, NEO_GRB + NEO_KHZ800);


// variabled for the sonic sensor
int delayval = 2; // delay microseconds for sonic sensor

#define EchoPin_Sonic 7 // Echo Pin
#define TrigPin_Sonic 8 // Trigger Pin

// just to know.
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
  pinMode(TrigPin_Sonic, OUTPUT);
  pinMode(EchoPin_Sonic, INPUT);
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  digitalWrite(TrigPin_Sonic, LOW);
  delayMicroseconds(delayval);
  
  digitalWrite(TrigPin_Sonic, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(TrigPin_Sonic, LOW);
  duration = pulseIn(EchoPin_Sonic, HIGH);
  
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
