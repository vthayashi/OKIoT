#ifdef ss_tx_pin

String mySerial_read_buffer;

void ss_setup(){
  mySerial.begin(ss_speed);
  delay(10);
}

void ss_loop(){
  if(mySerial.available()) {
    char sa; sa=mySerial.read();
    if(sa==10 || sa==13){
      String str;
      str=mySerial_read_buffer;
      str.trim();
      if(str.length()>0){ serial_run(str); }
      mySerial_read_buffer="";
    }
    if(sa>=32) mySerial_read_buffer+=sa;
  }
  if(Serial.available()) {
    String str; str=Serial.readStringUntil('\r');
    str.trim();
    if(str.length()>0){ serial_run(str); }
  }
}

void serial_run(String str){
  str.replace("\"","");  //str.replace(";","");
  str.trim();
  str.replace("\n",""); str.replace("\r","");
  if(str.length()==0) return;
  str+=" ";
  String sa;
  sa="log ";
  if(str.startsWith(sa)){
    str=str.substring(str.indexOf(" ")+1);
    addLog(str);
  }
}

#endif
