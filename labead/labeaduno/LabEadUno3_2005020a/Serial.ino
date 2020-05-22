void serial_loop(){
  if (Serial.available()) {
    String str = Serial.readStringUntil('\r');
    str.replace("\n", "");
    str.trim();
    if (str.length() > 0) { serial_run("?" + str);}
  }
}

void serial_run(String str) {
  str.replace("??", "&");
  str.replace("?", "&");
  String sa, sb, sc;
  //String fields=",dr,ar,re,";
  //
  sa = "rst"; if (str.indexOf(sa) >= 0) {
    Serial.println("{\"rst\":\"ok\"}"); delay(100);
    asm volatile ("  jmp 0");
    return;
  }
  // Servo
  sa = "&pos=";
  if (str.indexOf(sa) >= 0) {
    sb = str.substring(str.indexOf(sa) + sa.length()) + "&";
    sb = sb.substring(0, sb.indexOf("&"));
    uint8_t port, angle;
    port = sb.substring(0, sb.indexOf(",")).toInt();
    angle = sb.substring(sb.indexOf(",") + 1).toInt();
    pos(port, angle);
  }
  // &d=
  sa = "&d=";
  if (str.indexOf(sa) >= 0) {
    sb = str.substring(str.indexOf(sa) + sa.length()) + "&";
    sb = sb.substring(0, sb.indexOf("&"));
    uint8_t port, state;
    port = sb.substring(0, sb.indexOf(",")).toInt();
    state = sb.substring(sb.indexOf(",") + 1).toInt();
    pinMode(port, OUTPUT); digitalWrite(port, state);
  }
  //&anw=[port],[value]
  sa="&anw=";
  if (str.indexOf(sa) >= 0) {
    sb = str.substring(str.indexOf(sa) + sa.length()) + "&";
    sb = sb.substring(0, sb.indexOf("&"));
    uint16_t port, value;
    port = sb.substring(0, sb.indexOf(",")).toInt();
    value = sb.substring(sb.indexOf(",") + 1).toInt();
    analogWrite(port,value);
  }
  // Resposta
  Serial.print("{"); String pg="";
  ///// wave
  sa = "&w=";
  if (str.indexOf(sa) >= 0) {
    uint8_t v_chn=0; uint16_t v_sinc=511;
    sb = str.substring(str.indexOf(sa) + sa.length())+"&";
    sb = sb.substring(0, sb.indexOf("&"));
    if(sb.indexOf(",")>=0){
      v_sinc=sb.substring(sb.indexOf(",")+1).toInt();
      sb = sb.substring(0, sb.indexOf(","));
    }
    v_chn=sb.toInt();
    uint32_t prev_micros=micros();
    uint16_t rv, prev_rv=analogRead(A0);
    while(true){
      rv=analogRead(A0);
      if( (prev_rv<v_sinc)&&(rv>=v_sinc) ) break;
      if( (micros()-prev_micros) > 40000 ) break;
      prev_rv=rv;
    }
    //
    uint16_t ia[100];
    prev_micros=micros();
    for(uint8_t i=0; i<100;i++){
      while((micros()-prev_micros)<170) {}
      ia[i]=analogRead(A0+v_chn);
      prev_micros+=166;
    }
    pg+="\"w\":[";
    for(uint8_t i=0; i<100;i++){
      pg+=String(ia[i]);
      if(i<99) pg+=","; else pg+="],";
    }
  }
  if(pg.length()>0) Serial.print(pg);
  pg="";
  sa="&dr=";
  if (str.indexOf(sa) >= 0) {
    Serial.print("\"dr\":["); pg="";
    sb=str.substring( str.indexOf(sa) + sa.length() )+"&";
    sb=sb.substring(0,sb.indexOf("&"))+",";
    while(sb.indexOf(",")>=0){
      sc=sb.substring(0,sb.indexOf(","));sb=sb.substring(sb.indexOf(",")+1);
      //
      if(sc.indexOf("-")>0){
        uint8_t ini=sc.substring(0,sc.indexOf("-")).toInt();
        uint8_t fim=sc.substring(sc.indexOf("-")+1).toInt();
        for(uint8_t i=ini;i<=fim;i++){
          if (digitalRead(i)) pg += "1"; else pg += "0";
          pg += ",";
        }
      }else{
        uint8_t pin=sc.toInt();
        if(pin>1){
          if (digitalRead(pin)) pg += "1"; else pg += "0";
          pg += ",";
        }
      }
      //
    }
    pg=pg.substring(0,pg.length()-1);
    Serial.print(pg+"],"); pg="";
  }
  /*/
  pg += "\"ar\":[";
  for (uint8_t i = 0; i <= 3; i++) {
    pg += analogRead(A0+i);
    if (i < 3) pg += ","; else pg += "],";
  }
  Serial.print(pg); pg="";
  //*/
  sa="&ar=";
  if (str.indexOf(sa) >= 0) {
    Serial.print("\"ar\":["); pg="";
    sb=str.substring( str.indexOf(sa) + sa.length() )+"&";
    sb=sb.substring(0,sb.indexOf("&"))+",";
    while(sb.indexOf(",")>=0){
      sc=sb.substring(0,sb.indexOf(","));sb=sb.substring(sb.indexOf(",")+1);
      if(sc.indexOf("-")>0){
        uint8_t ini=sc.substring(0,sc.indexOf("-")).toInt();
        uint8_t fim=sc.substring(sc.indexOf("-")+1).toInt();
        for(uint8_t i=ini;i<=fim;i++){
          pg += analogRead(A0+i);
          pg += ",";
        }
      }else{
        uint8_t pin=sc.toInt();
        pg += analogRead(A0+pin);
        pg += ",";
      }
    }
    pg=pg.substring(0,pg.length()-1);
    Serial.print(pg+"],"); pg="";
  }
  sa="&re=";
  if (str.indexOf(sa) >= 0) {
    Serial.print("\"re\":["); pg="";
    sb=str.substring( str.indexOf(sa) + sa.length() )+"&";
    sb=sb.substring(0,sb.indexOf("&"))+",";
    while(sb.indexOf(",")>=0){
      sc=sb.substring(0,sb.indexOf(","));sb=sb.substring(sb.indexOf(",")+1);
      if(sc.indexOf("-")>0){
        uint8_t ini=sc.substring(0,sc.indexOf("-")).toInt();
        uint8_t fim=sc.substring(sc.indexOf("-")+1).toInt();
        for(uint8_t i=ini;i<=fim;i++){
          if (digitalRead(i)) pg += "1"; else pg += "0";
          pg += ",";
        }
      }else{
        uint8_t pin=sc.toInt();
        if(pin>1){
          if (digitalRead(pin)) pg += "1"; else pg += "0";
          pg += ",";
        }
      }
    }
    pg=pg.substring(0,pg.length()-1);
    Serial.print(pg+"],"); pg="";
  }
  if(pg.length()>0) Serial.print(pg);
  Serial.print("\"fim\":\"ok\"}\n");
}
