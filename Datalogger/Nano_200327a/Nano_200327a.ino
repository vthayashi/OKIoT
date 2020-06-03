#define Versao "Nano_200327a"
#define ss_tx_pin 11 // D1mini D7
#define ss_rx_pin 10 // D1mini D6
#define ss_speed 9600 // SoftwareSerial

#include <SoftwareSerial.h>
SoftwareSerial mySerial(ss_rx_pin, ss_tx_pin);

void setup() {
  // put your setup code here, to run once:
  mySerial.begin(ss_speed); delay(10);
  mySerial.print("a7");

  Serial.begin(115200); delay(10);
  Serial.println("Iniciando");
  Serial.print("log "); Serial.println(Versao);
}

void loop() {
}
