// Arduino 1.8.12
// esp8266 2.6.3 http://arduino.esp8266.com/stable/package_esp8266com_index.json
// TimeLib 1.5

#define Versao "OKiotReg_200321c"

#define SCL_pin D1
#define SDA_pin D2
#define i2c_rtc 0x68

#define ss_tx_pin D6
#define ss_rx_pin D7
#define ss_speed 19200

#define EspLedPin D4

#include <ESP8266WiFi.h>
String DeviceID;
String  apPass = "12345678";

#include <ESP8266WebServer.h>
ESP8266WebServer server(80);
#include <ESP8266HTTPUpdateServer.h>
ESP8266HTTPUpdateServer httpUpdater;

#include <TimeLib.h>

#include <Wire.h>

#include <FS.h>

String  log_buffer;
String  log_recent;

uint32_t loop100count;
uint32_t prevMillis;

uint32_t fs_usedBytes,fs_totalBytes;

#include <SoftwareSerial.h>
SoftwareSerial mySerial(ss_rx_pin, ss_tx_pin); // RX, TX SoftwareSerial(rxPin, txPin, inverse_logic, buffer size);

void setup() {
  Serial.begin(19200); Serial.println();  
  //
  String ChipId=String(ESP.getChipId(),HEX);
  ChipId.toUpperCase();
  DeviceID=Versao;
  if(DeviceID.indexOf("_")>0){
    DeviceID=DeviceID.substring(0,DeviceID.indexOf("_")+1);
    DeviceID+=ChipId;
  }
  Serial.println(DeviceID);
  //
  WiFi.mode(WIFI_AP);
  WiFi.softAP(DeviceID.c_str(), apPass.c_str());

  fs_setup();

  ws_setup();
  //
  Wire.begin(SDA_pin,SCL_pin);
  ds1307_read();

  addLog(F("Iniciando ESP"));

  ss_setup();
  pinMode(EspLedPin,OUTPUT);
  // put your setup code here, to run once:
  
}

void loop() {
  server.handleClient();
  loop100();
  ss_loop();
  // put your main code here, to run repeatedly:
  
}

void loop100(){
  if ((millis()-prevMillis)<100) return;
  prevMillis = millis();
  if(loop100count%10==0) digitalWrite(EspLedPin, LOW );
  if(loop100count%10==1) digitalWrite(EspLedPin, HIGH );
  if(loop100count%10==2 && year()<2020) digitalWrite(EspLedPin, LOW );
  if(loop100count%10==3) digitalWrite(EspLedPin, HIGH );
  log_loop100();
  if (loop100count%36000==10) fs_log_auto_del("/log/", 50); //a cada 1 hora
  //if(loop100count%600==300) addLog("minuto");
  loop100count++;
}

void wsTimeSet(String stime){
  stime = stime.substring(0, stime.length() - 3);
  time_t itime;
  int8_t timeZone = -3;
  itime = stime.toInt()+(timeZone*SECS_PER_HOUR);
  setTime(itime);  //addLog(F("wsTimeSet "));
  ds1307_write();
}

// O sketch usa 361468 bytes (34%) de espaço de armazenamento para programas. O máximo são 1044464 bytes.
// Variáveis globais usam 28820 bytes (35%) de memória dinâmica, deixando 53100 bytes para variáveis locais. O máximo são 81920 bytes.
