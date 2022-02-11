## Introduction

With this little setup your old SIEDLE HTA 711-0 doorbell gets ready for IoT! The goal is to send a mqtt message if someone rings the doorbell.

Here you can see the finished setup

<img src="https://github.com/bee-eater/SIEDLE-Smart-ESP8266/blob/master/Media/IMG_5099.JPG" alt="Setup" height="200"/>

And here the installation

<img src="https://github.com/bee-eater/SIEDLE-Smart-ESP8266/blob/master/Media/IMG_5096.JPG" alt="Install" height="200"/>

## Circuit infos

The SIEDLE provides a 12 VAC between 7 and c when someone rings the doorbell. That signal is converted to a usable 1.05 VDC signal which operates the photocoupler. The whole circuit is powered by a 5 VDC USB power adapter, which is converted to 3.3 VDC by the LD1117V33. Here is a screenshot from a LTSpice simulation:

<img src="https://github.com/bee-eater/SIEDLE-Smart-ESP8266/blob/master/Media/LTSpice.png" alt="Install" width="100%"/>

And the circuit:

<img src="https://github.com/bee-eater/SIEDLE-Smart-ESP8266/blob/master/Media/KiCAD.png" alt="Install" width="100%"/>

**Parts ESP / power supply:**

-   ESP-01
-   LD1117V33
-   C: 100µF
-   C: 100nF

**Parts voltage conversion**

-   PC817
-   1N4007 (hatte keine 1N4148 da, geht aber genauso!)
-   R: 2k2
-   C: 10µF

## Program infos

The ESP-12F can be programmed via Arduino. Enter the correct infos for your WiFi and mqtt broker in the SiedleESP.ino file and flash it to the ESP.

The message can be retrieved in any home automation system (NodeRED, Home Assistant, OpenHAB) and from there a message can be pushed to your phone by e.g. Pushover.

## Additional thoughts

-   The whole thing could be made battery powered by using an AtTiny85 like demonstrated here [ATTINY85wecktESP8266](https://github.com/ingeninge/ATTINY85wecktESP8266)
-   The circuit could be designed on a PCB
