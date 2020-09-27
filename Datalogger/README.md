# Datalogger

Data logger module based on ESP8266 Wemos D1 mini (ESP8266) IoT development board and Arduino.

Firmware for ESP8266 is available in OKiotReg_200321c folder, and firmware for Arduino module (Arduino Uno, Arduino Nano, Arduino Mega boards are compatible) can be found in Nano_200327a folder.
Both codes can be edited with Arduino IDE [more details](https://www.arduino.cc/en/main/software).

Communication between datalogger and Arduino modules can be done with 433 MHz radio frequency communication, or through serial communication.
For ease of reproducibility, the version available here is the one with serial communication betweeen ESP8266 Wemos D1 mini and Arduino module (UART serial communication, with 8N2 setup, i.e. 8 bits ASCII, no  parity, 2 stop bits), set with 9600 baud rate.

Datalogger module is compatible with RTC (Real Time Clock) module with battery for fault tolerant timestamp syncronization. The datalogger module uses ESP8266 filesystem (flash memory), with maximum storage of 1.5 MB, 50 files. Each day has a unique file, with each event registered with its UNIX timestamp.

[Brazilian smart home testbed](https://github.com/vthayashi/OKIoT/tree/master/BrazilTestbed) with 20 sensors (10 motion sensors and 10 light state sensors) had events of two months registered in this datalogger module.

As for hardware, pin 11 of Arduino must be connected to D6 pin of Wemos D1 mini, and Arduino pin 10 must be connected to Wemos D1 mini D7 pin.
Full schematic can be found in [OKIoT Datalogger v002.pdf file](https://github.com/vthayashi/OKIoT/blob/master/Datalogger/OKIoT%20Datalogger%20v002.pdf).
