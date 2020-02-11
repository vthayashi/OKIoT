
#include <SoftwareSerial.h>
#define ss_speed 38400 // SoftwareSerial
SoftwareSerial mySerial(ss_rx_pin, ss_tx_pin); // RX, TX SoftwareSerial(rxPin, txPin, inverse_logic, buffer size);
String mySerial_read_buffer;

void ss_setup(){
  mySerial.begin(ss_speed); delay(10);
  Serial.print(F("Iniciando: ")); Serial.println(Versao);
  mySerial.print(F("Iniciando: ")); mySerial.println(Versao);
}

void ss_loop(){
  //
  if (mySerial.available()) {
    char sa; sa=mySerial.read();
    if(sa==13){
      Serial.print("esp> "); Serial.println(mySerial_read_buffer);
      ss_run(mySerial_read_buffer);
      mySerial_read_buffer="";
    }
    if(sa>=32) mySerial_read_buffer+=sa;
  }
  //
  if(Serial.available()){
    String str;
    str = Serial.readStringUntil('\r');
    str.trim();
    if(str.length()>0){
      Serial.print("> "); Serial.println(str);
      ss_run(str);
      String sa;
      for(uint8_t i=0; i<8;i++){
        sa="s"; sa+=i; sa+="=";
        if(str.substring(0,3)==sa) mySerial.println(str);
        sa="r"; sa+=i; sa+="=";
        if(str.substring(0,3)==sa) mySerial.println(str);
        sa="f"; sa+=i; sa+="=";
        if(str.substring(0,3)==sa) mySerial.println(str);
      }
      sa="l="; if(str.substring(0,2)==sa) mySerial.println(str);
      sa=F("time");  if(str==sa){  mySerial.println(str); }
    }
  }
}

void ss_run(String str){
  String sa;
  sa=F("Versao"); if(str==sa){ Serial.print(F("Versao: ")); Serial.println(Versao); }
  sa=F("Reset");  if(str==sa){ delay(1); asm volatile ("  jmp 0"); }
  sa=F("esp=");   if(str.indexOf(sa)==0){ mySerial.println(str); }
  sa=F("wifi=");  if(str.indexOf(sa)==0){ mySerial.println(str); }
}

// esp=reset
// wifi=ssid:password
// wifi=reconnect
// wifi=disconnect
// s0=1; s0=2;
// f0=3.14;
// r0=0; (turn) r0=1; (off) ro=2; (on)
// l=texto a ser adicionado no log

