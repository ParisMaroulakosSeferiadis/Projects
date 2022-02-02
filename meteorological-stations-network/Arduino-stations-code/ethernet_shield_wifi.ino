#include <SPI.h>
#include <Ethernet.h>
#include "DHT.h"
#include "Adafruit_TSL2591.h"
#include <Wire.h>
#include <Adafruit_LPS2X.h>
#include <Adafruit_Sensor.h>
#include <SD.h> // include Arduino SD library
#include <ThreeWire.h>  
#include <RtcDS1302.h>
 

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22
#define LPS_CS 53
#define LPS_SCK 52
#define LPS_MISO 50
#define LPS_MOSI 51
#define countof(a) (sizeof(a) / sizeof(a[0]))


ThreeWire myWire(5,3,6); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = {192, 168, 137, 13 }; //Enter the IP of ethernet shield 192.168.1.5
char serv[] = "weatherdatapms.ddns.net"; // the ip adress for pi
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);
DHT dht(DHTPIN, DHTTYPE);
File dataLog;
EthernetClient client;
Adafruit_LPS22 lps;
sensors_event_t lps_temp;
sensors_event_t lps_press;
float sensorVoltage; 
int sensorValue;

void setup() {
  pinMode(53, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(A3,INPUT);
  digitalWrite(10, HIGH); // disable ethernet cs
  digitalWrite(4, HIGH);
  digitalWrite(53, LOW); // enable lps cs
  lps.begin_SPI(LPS_CS);
  digitalWrite(53, HIGH); // disable lps cs
  digitalWrite(4, LOW);
  if ( !SD.begin(4) )
    Serial.println("failed!");  // initialization error
  digitalWrite(4, HIGH);
  dht.begin();
  tsl.begin();
  tsl.setGain(TSL2591_GAIN_MED);
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
  Serial.begin(9600); //setting the baud rate at 9600
  Rtc.Begin();
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
  digitalWrite(10, LOW);// enable ethernet
  Ethernet.begin(mac, ip);
}

void loop() {

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  float L = tsl.calculateLux(full, ir) ;
  digitalWrite(10, HIGH); // disable ethernet cs

  digitalWrite(53, LOW); // enable lps cs
  lps.getEvent(&lps_press, &lps_temp);// get lps pressure & lps temp
  float temperature = lps_temp.temperature;
  float pressure = lps_press.pressure;
  digitalWrite(53, HIGH); // disable lps cs
  sensorValue = analogRead(A3);
  sensorVoltage = (5.0/1023.0)*(sensorValue)*(1000);
  int uv=volts_to_uv(sensorVoltage);
  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C "));

//  Serial.print(F("F  Heat index: "));
//  Serial.print(hic);
//  Serial.print(F("C "));

  Serial.print("Lux = ");
  Serial.println(L);
  Serial.print("Pressure = ");
  Serial.println(pressure);
  Serial.print("Ltemp = ");
  Serial.println(temperature);
  Serial.print("sensorVoltage = ");
  Serial.println(sensorVoltage);
  Serial.print("UV-Index = ");
  Serial.println(uv);

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

   digitalWrite(4, LOW);// ENABLE SD
     
  // open Log.txt file with write permission
  
  dataLog = SD.open("LogEthernet.txt", FILE_WRITE);
  dataLog.print(datestring);
  dataLog.print("     "); 
  dataLog.print(t) ;
  dataLog.print( "°C   |  ");
  dataLog.print(h);
  dataLog.print("  | ");
  dataLog.print(L);
  dataLog.print("  | ");
  dataLog.print(pressure);
  dataLog.print("°C   |  ");
  dataLog.println(temperature);
  dataLog.close();       
  delay(100);   // wait 100ms
  digitalWrite(4, HIGH); // DISABLE SD

  digitalWrite(10, LOW);// enable ethernet
  if (client.connect(serv, 8081)) { //Connecting at the IP address and port we saved before
    Serial.println("connected");
    client.print("GET /data_hmmy.php?"); //Connecting and Sending ues to database
    client.print("&temperature=");
    client.print(t);
    client.print("&humidity=");
    client.print(h);
    client.print("&Lux=");
    client.print(L);
    client.print("&lps_temperature=");
    client.print(temperature);
    client.print("&lps_pressure=");
    client.print(pressure);
    client.print("&UV-Light=");
    client.println(uv);
    client.stop(); //Closing the connection
  }
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 // digitalWrite(10, HIGH);// enable ethernet
  delay(5000);
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
