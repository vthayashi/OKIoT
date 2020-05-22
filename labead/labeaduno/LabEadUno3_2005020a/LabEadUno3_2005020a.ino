#define Versao "LabEadUno3_2005020a"

uint8_t re_map[] = {7, 4};
uint8_t aw_map[] = {5, 6, 3};
int16_t prev_aw[] = { -1, -1, -1, -1, -1, -1, -1, -1};
uint8_t dr_map[] = {8, 11, 12, 13};

void setup() {
  analogReference(DEFAULT); // 5V
  Serial.begin(57600);
  for (uint8_t i = 2; i <= 13; i++) {
    pinMode(i, INPUT);
  }
}

void loop() {
  serial_loop();
}
