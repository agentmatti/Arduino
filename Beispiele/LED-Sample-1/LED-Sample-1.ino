// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the ESP is connected to the NeoPixels?
#define PIN        D8
//#define PIN         3 // this would be RST

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 20 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  Serial.begin(115200);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  Serial.println("loop ...\n");

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.

  // erstmal all LED leicht rot schalten
  for(int led = 0; led < NUMPIXELS; led++) {
        pixels.setPixelColor(led, pixels.Color(10, 0, 0));
  }
  // und aufs Band senden
  pixels.show();

  // nun alle LED einmal hellrot schalten, kurz warten und wieder dunkelrot.
  for(int led = 0; led < NUMPIXELS; led ++) {
      pixels.setPixelColor(led, pixels.Color(255, 0, 0));
      pixels.show();
      delay(50);
      pixels.setPixelColor(led, pixels.Color(10, 0, 0));
  }
//    das wäre dafür dass alle LED 
//    for(int led = NUMPIXELS; led > 0; led--) {
//        pixels.setPixelColor(led, pixels.Color(255, 0, 0));
//        pixels.show();
//        delay(50);
//        pixels.setPixelColor(led, pixels.Color(50, 0, 0));
//    }
  
} /** Ende of programm  **/
