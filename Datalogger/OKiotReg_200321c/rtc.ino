#ifdef i2c_rtc

void ds1307_read(){
  Wire.beginTransmission(0x68); if (Wire.endTransmission() != 0) return;
  byte rtc_second, rtc_minute, rtc_hour;
  byte rtc_day, rtc_date, rtc_month;  // rtc_day of the week (1-7), Sunrtc_day is rtc_day 1
  uint16_t rtc_year;
  Wire.beginTransmission(0x68);       // Start I2C protocol with DS3231 address
  Wire.write(0);                      // Send register address
  Wire.endTransmission(false);        // I2C restart
  Wire.requestFrom(0x68, 7);          // Request 7 bytes from DS3231 and release I2C bus at end of reading
  rtc_second = Wire.read();           // Read rseconds from register 0
  rtc_minute = Wire.read();           // Read minuts from register 1
  rtc_hour   = Wire.read();           // Read rtc_hour from register 2
  rtc_day    = Wire.read();           // Read rtc_day from register 3 (not used)
  rtc_date   = Wire.read();           // Read rtc_date from register 4
  rtc_month  = Wire.read();           // Read rtc_month from register 5
  rtc_year   = Wire.read();           // Read rtc_year from register 6
  //
  rtc_second=(rtc_second&0x7F); rtc_second=(rtc_second >> 4) * 10 + (rtc_second & 0x0F);
  rtc_minute=(rtc_minute&0x7F); rtc_minute=(rtc_minute >> 4) * 10 + (rtc_minute & 0x0F);
  rtc_hour  =(rtc_hour >> 4) * 10 + (rtc_hour & 0x0F);
  rtc_date  = (rtc_date >> 4)   * 10 + (rtc_date & 0x0F);
  rtc_month = (rtc_month >> 4)  * 10 + (rtc_month & 0x0F);
  rtc_year  = (rtc_year >> 4)   * 10 + (rtc_year & 0x0F); rtc_year+=1970;
  rtc_day   = (rtc_day >> 4) * 10 + (rtc_day & 0x07);
  if(rtc_year>2018) setTime(rtc_hour,rtc_minute,rtc_second,rtc_date,rtc_month,rtc_year);
}

void ds1307_write(){
  Wire.beginTransmission(0x68); if (Wire.endTransmission() != 0) return;
  byte rtc_second, rtc_minute, rtc_hour;
  byte rtc_day, rtc_date, rtc_month;  // rtc_day of the week (1-7), Sunrtc_day is rtc_day 1
  uint16_t rtc_year;
  time_t t=now();
  rtc_year=year(t); 
  rtc_month=month(t);
  rtc_date=day(t);
  rtc_hour=hour(t);
  rtc_minute=minute(t);
  rtc_second=second(t);
  rtc_day=weekday(t);
  //Serial.println(rtc_year);  Serial.println(rtc_month); Serial.println(rtc_date);
  //
  rtc_year-=1970;
  // Convert decimal to BCD
  rtc_second = ((rtc_second / 10) << 4) + (rtc_second % 10);
  rtc_minute = ((rtc_minute / 10) << 4) + (rtc_minute % 10);
  rtc_hour = ((rtc_hour / 10) << 4) + (rtc_hour % 10);
  rtc_date = ((rtc_date / 10) << 4) + (rtc_date % 10);
  rtc_month = ((rtc_month / 10) << 4) + (rtc_month % 10);
  rtc_year = ((rtc_year / 10) << 4) + (rtc_year % 10);
  //
  Wire.beginTransmission(0x68); if (Wire.endTransmission() != 0) return;
  // Write data to DS3231 RTC
  Wire.beginTransmission(0x68); // Start I2C protocol with DS3231 address
  Wire.write(0);                // Send register address
  Wire.write(rtc_second);       // Reset sesonds and start oscillator
  Wire.write(rtc_minute);       // Write rminute
  Wire.write(rtc_hour);         // Write rtc_hour
  Wire.write(rtc_day);          // Write rtc_day (not used)
  Wire.write(rtc_date);         // Write rtc_date
  Wire.write(rtc_month);        // Write rtc_month
  Wire.write(rtc_year&0xFF);    // Write rtc_year
  Wire.endTransmission();       // Stop transmission and release the I2C bus
  delay(200);                   // Wait 200ms
}

#endif
