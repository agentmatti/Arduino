# Entwicklungsumgebung installieren/einrichten
## Arduino IDE installieren

### Windows

Beim Microsoft Store das machen. 

![Arduino_IDE_installieren](./Bilder/Arduino_IDE.png)

### Linux / Ubuntu

Von Arduino.cc die 64 Bit Linux Variante Laden:

![Linux Download](./Bilder/Linux_Download.png)

Die Datei speichern. Nach dem Download den Downloadorder öffnen und das heruntergeladene Archiv auspacken:

![Linux extract](./Bilder/Linux_extract.png)

Nun kann die Entwicklungsumgebung gestartet werden:

![Linux Start](./Bilder/Linux_start.png)


## Bibliotheken installieren

Für den Prozessor und die LED brauchen wir spezielle Bibliotheken.
Bei Arduino IDE findest du unter Datei die Voreinstellungen. Dort kopierst du folgende URL rein:

`http://arduino.esp8266.com/stable/package_esp8266com_index.json`

![Voreinstellungen](./Bilder/URL.png) 

Unter Werkzeuge|Board findest du den Boardverwalter. In die Suchleiste gibst du nodemcu ein und installierst die Bibliothek mit der Version 2.4.0.

![Bibilotheksversion](./Bilder/Arduino_esp_bibliothek.png)

Nach der installation muss das Board ausgewählt werden. Unter Werkzeuge|Board Wählst du NodeMCU 1.0 aus.

![Auswahl](./Bilder/Arduino_esp_auswahl.png)

Ausserdem benötigen wir eine Bibliothek um das LED Band zu beunutzen. Unter Menu Werkezuge|Bibliotheken muss die folgende Bibliothek installiert werden:

![Adafruit Neopixel](./Bilder/Adafruit_Neopixel.png)
