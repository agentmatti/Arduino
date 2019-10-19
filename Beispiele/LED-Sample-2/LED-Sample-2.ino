// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the ESP is connected to the NeoPixels?
//wenn esp dann D8 wenn arduino 6
#define PIN        6
//#define PIN         3 // this would be RST
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 144 // Popular NeoPixel ring size

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
  uint8_t LEDgreen = NUMPIXELS / 20;
  uint8_t pause = .1 * 1000 / NUMPIXELS;
  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.

  for(int led=0; led<NUMPIXELS; led++) {
        pixels.setPixelColor(led, pixels.Color(0, 0, 10));
  }
  pixels.show();
   
  for(int led=0; led<NUMPIXELS; led++) {
//        das ist die einfache Variante
//        pixels.setPixelColor(led+0, pixels.Color(0, 255, 0));
//        pixels.setPixelColor(led+1, pixels.Color(0, 255, 0));
//        pixels.setPixelColor(led+2, pixels.Color(0, 255, 0));
//        pixels.setPixelColor(led+3, pixels.Color(0, 255, 0));
//        pixels.setPixelColor(led+4, pixels.Color(0, 255, 0));
    // besser gehts mit einer Schleife
    for(int c=0; c<LEDgreen; c++) {
      pixels.setPixelColor(led+c, pixels.Color(0, 100, 0));
    }
    pixels.show();
    delay(pause);
    pixels.setPixelColor(led, pixels.Color(10, 0, 0));
  }
  for(int led = NUMPIXELS; led > 0; led--) {
     for(int c=0; c<LEDgreen; c++) {
      pixels.setPixelColor(led - c, pixels.Color(0, 100, 0));
    }
    pixels.show();
    delay(pause);
    pixels.setPixelColor(led, pixels.Color(0, 0, 10));
  }
  
} /** Ende of programm  **/
