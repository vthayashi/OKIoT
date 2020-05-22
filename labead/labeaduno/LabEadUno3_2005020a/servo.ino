void pos(uint8_t port, uint8_t angle){
  pinMode(port,OUTPUT);
  uint8_t pos=90;
  uint16_t t1;
  t1 = map(angle, 0, 180, 400, 2400);
  for(uint8_t i=0; i<5;i++){
    digitalWrite(port,HIGH);
    delayMicroseconds(t1);
    digitalWrite(port,LOW);
    delayMicroseconds(5000-t1);
  }
}
