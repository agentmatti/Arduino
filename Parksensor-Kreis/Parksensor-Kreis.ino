// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16

// was ist der maximale Abstand
#define MAX_DISTANCE   32

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 2; // delay for half a second
#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define LEDPin 13 // Onboard LED
int maxRange = 200;
int minRange = 0;
long duration,distance;
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
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
  
  Serial.println(distance);
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for(int led =0; led < NUMPIXELS; led++){
     int color = 0;
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    if (led < distance){
      if( distance <= MAX_DISTANCE ) {
        // wir sind inerhalb des krittischen Bereiches
        if ( distance > 16 ) {
          pixels.setPixelColor(led, pixels.Color( 0, 50, 0));
        } else if ( distance > 4 ) {
          pixels.setPixelColor(led, pixels.Color( 50, 50, 0));        
        } else {
          pixels.setPixelColor(led, pixels.Color( 50, 0, 0));        
        }
      }
       else {
        pixels.setPixelColor(led, pixels.Color(0,0,0)); // Moderately bright green color.
      }
    }
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(0);
}
