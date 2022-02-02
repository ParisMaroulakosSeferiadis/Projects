#include <SPI.h>
#include <RadioHead.h>
#include "RH_RF95.h"
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_LPS2X.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"
#include <SD.h> // include Arduino SD library
#include <ThreeWire.h>  
#include <RtcDS1302.h>
 

#define LPS_CS 8
#define RFM95_CS 10 //CS if Lora connected to pin 10
#define RFM95_RST 9 //RST of Lora connected to pin 9
#define RFM95_INT 2 //INT of Lora connected to pin 2
#define RF95_FREQ 434.0 // Change to 434.0 or other frequency, must match RX's freq!
#define countof(a) (sizeof(a) / sizeof(a[0]))

ThreeWire myWire(4,5,7); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
RH_RF95 rf95(RFM95_CS, RFM95_INT);
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);
DHT dht(3,DHT22);
Adafruit_LPS22 lps;
sensors_event_t lps_temp;
sensors_event_t lps_press;
String ide = "1.2";
File dataLog;
float sensorVoltage; 
int sensorValue;
void setup() 
{
//    Serial.print("compiled: ");
//    Serial.print(__DATE__);
//    Serial.println(__TIME__);

    Rtc.Begin();
//    Only the first time just to set the time
//    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);   
//    printDateTime(compiled);
//    Serial.println();

//    if (!Rtc.IsDateTimeValid()) 
//    {
//        // Common Causes:
//        //    1) first time you ran and the device wasn't running yet
//        //    2) the battery on the device is low or even missing
//
//        Serial.println("RTC lost confidence in the DateTime!");
//        Rtc.SetDateTime(compiled);
//    }

    if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

  RtcDateTime now = Rtc.GetDateTime();
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(A3,INPUT);
  digitalWrite(10, HIGH); // disable ethernet cs
  digitalWrite(6, HIGH);
  digitalWrite(8, LOW); // enable lps cs
  lps.begin_SPI(LPS_CS);
  digitalWrite(8, HIGH); // disable lps cs
  Serial.begin(9600);
  dht.begin();
  tsl.begin();
//  if (tsl.begin()) 
//  {
//    Serial.println(F("Found a TSL2591 sensor"));
//  } 
//  else 
//  {
//    Serial.println(F("No sensor found ... check your wiring?"));
//    while (1);
//  }
  tsl.setGain(TSL2591_GAIN_MED);
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
 // manual reset
 digitalWrite(10, LOW); // enable rf
  digitalWrite(RFM95_RST, LOW);
    pinMode(RFM95_RST, OUTPUT);

  delayMicroseconds(100); 
   pinMode(RFM95_RST, INPUT); 
  delay(20);
  
  while (!rf95.init()) {
    Serial.println("LoRas radio init failed");
    delay (1000);
  }
//rf95.init();
// 
//rf95.setFrequency(RF95_FREQ);
 //Set the default frequency 434.0MHz
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  digitalWrite(10, HIGH); // disable rf
  digitalWrite(6, LOW);
  if ( !SD.begin(6) )
    Serial.println("failed!");  // initialization error
  digitalWrite(6, HIGH);
}



void loop()
{
  
  String data= "";
  Serial.print(F(" data: "));
  Serial.println(data);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  digitalWrite(8, LOW); // enable lps cs
  lps.getEvent(&lps_press, &lps_temp);// get lps pressure & lps temp
  float ltemperature = lps_temp.temperature;
  float lpressure = lps_press.pressure;
  digitalWrite(8, HIGH); // disable lps cs
  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  float L= tsl.calculateLux(full, ir);
  sensorValue = analogRead(A3);
  sensorVoltage = (5.0/1023.0)*(sensorValue)*(1000);
  int uv=volts_to_uv(sensorVoltage);
  //Serial.print(F("Lux: ")); Serial.println(L);
  String humidity = String(h,2); //int to String
  String sh= String(humidity.length());
  String temperature = String(t,2);
  String st= String(temperature.length());
  String heatid= String(hic,2);
  String Lux=String (L,2);
  String sl= String(Lux.length());
  String lps_press=String(lpressure,2);
  String slp= String(lps_press.length());
  String lps_temp=String(ltemperature,2);
  String slt= String(lps_temp.length());
  String uvi=String(uv,2);
  String su= String(uvi.length());
  Serial.print(F(" ID: "));
  Serial.println(ide);
  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F(" Sh: "));
  Serial.println(sh);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F(" St: "));
  Serial.println(st);
  Serial.print(F("C "));
  Serial.print(F("F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("F  Lux: "));
  Serial.println(Lux);
  Serial.print(F(" Sl: "));
  Serial.println(sl);
  Serial.print("Pressure = "); 
  Serial.print(lpressure);
  Serial.print(F(" Slp: "));
  Serial.println(slp);
  Serial.print("Ltemp = ");
  Serial.print(ltemperature);
  Serial.print(F(" Slt: "));
  Serial.println(slt);
  Serial.print("UV-Index = ");
  Serial.print(uv);
  Serial.print(F(" Su: "));
  Serial.println(su);
 
  data =ide;
  data.concat(st);
  data.concat(sh);
  data.concat(sl);
  data.concat(slp);
  data.concat(slt);
  data.concat(su);
  data.concat(temperature);
  data.concat(humidity);
  data.concat(Lux);
  data.concat(lps_press);
  data.concat(lps_temp);
  data.concat(uvi);
  Serial.println(data);
  int dat= data.length();
  Serial.println(dat);
  char d[dat+1];
  data.toCharArray(d,dat+1); //String to char array
  data= "";
  Serial.println((d));  
  Serial.println(strlen(d));
  Serial.println(F("Sending to rf95_server"));
  digitalWrite(10, LOW);
  rf95.send((uint8_t *)d, strlen(d));
  rf95.waitPacketSent();
  digitalWrite(10, HIGH);
  RtcDateTime now = Rtc.GetDateTime();
  char datestring[22];
  snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u   %02u:%02u:%02u"),
            now.Month(),
            now.Day(),
            now.Year(),
            now.Hour(),
            now.Minute(),
            now.Second() );
  Serial.println(datestring);
  if (!now.IsValid())
    {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }
  
  digitalWrite(6, LOW);// ENABLE SD
  // open Log.txt file with write permission                    
  dataLog = SD.open("LogRF.txt", FILE_WRITE);
  dataLog.print(datestring);
  dataLog.print("     "); 
  dataLog.print(t) ;
  dataLog.print( "°C   |   ");
  dataLog.print(h);
  dataLog.print("  | ");
  dataLog.print(L);
  dataLog.print("  | ");
  dataLog.print(lpressure);
  dataLog.print("   |  ");
  dataLog.println(ltemperature);
  dataLog.close();       
  
  delay(100);   // wait 100ms
    digitalWrite(6, HIGH); // DISABLE SD
     
  delay(4000);
}

int volts_to_uv(float sensorVoltage)
  {
    int uv;    
    if (sensorVoltage<50.0){
      uv=0;
    }
    else if (sensorVoltage<=227.0){
      uv=1;
    }
    else if (sensorVoltage<=318.0){
      uv=2;
    }
    else if (sensorVoltage<=408.0){
      uv=3;
    }
    else if (sensorVoltage<=503.0){
      uv=4;
    }
    else if (sensorVoltage<=606.0){
      uv=5;
    }
    else if (sensorVoltage<=696.0){
      uv=6;
    }
    else if (sensorVoltage<=795.0){
      uv=7;
    }
    else if (sensorVoltage<=881.0){
      uv=8;
    }
    else if (sensorVoltage<=976.0){
      uv=9;
    }
    else if (sensorVoltage<=1079.0){
      uv=10;
    }
    else {
      uv=11;
    }
    return uv;
    }
