// Arduino IDE 1.8.5
// Biblioteca Arduino AVR Boards 1.6.20

#define Versao "Nano_190630d"

#define ss_rx_pin 10
#define ss_tx_pin 11

void setup() {
  Serial.begin(115200); Serial.println();
  ss_setup();
}

void loop() {
  ss_loop();
}


