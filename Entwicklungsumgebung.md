# Entwicklungsumgebung installieren/einrichten
## Arduino IDE installieren
Beim Microsoft Store das machen. 
![Arduino_IDE_installieren](./Bilder/Arduino_IDE.png)
## Bibliotheken installieren
Für den Prozessor brauchen wir eine spezielle Bibliothek.
Bei Arduino IDE findest du unter Datei die Voreinstellungen. Dort kopierst du folgende URL rein:
`http://arduino.esp8266.com/stable/package_esp8266com_index.json`
![Voreinstellungen](./Bilder/URL.png) 

Unter Werkzeuge|Board findest du den Boardverwalter. In die Suchleiste gibst du nodemcu ein und installierst die Bibliothek mit der Version 2.4.0.
![Bibilotheksversion](./Bilder/Arduino_esp_bibliothek.png)

Nach der installation muss das Board ausgewählt werden. Unter Werkzeuge|Board Wählst du NodeMCU 1.0 aus.
![Auswahl](./Bilder/Arduino_esp_auswahl.png)
## Code
Um die Lampenkette propgrammieren zu können sind falgende Anweisungen nötig:
`#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif`
Jetzt muss definiert werden über welchen Pin am ESP12b das WS2812B verbunden. 
`#define PIN    6`
Dann noch … wie viele LEDs stehen uns zur Verfügung? 
`#define NUMPIXELS 16`
Setup der Adafruit_NeoPixel-Lib vor der Benutzung … 
`Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);`
Setup der Adafruit_NeoPixel-Lib in der Setup-Methode() … 
`void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  Serial.begin(115200);
  pixels.begin();
  }`
Jetzt kann‘s los gehen ...   
`void loop() {
  pixels.clear();
  DEBUG_MSG("loop ...\n");
`
Und hier steht jetzt Dein Code …  
