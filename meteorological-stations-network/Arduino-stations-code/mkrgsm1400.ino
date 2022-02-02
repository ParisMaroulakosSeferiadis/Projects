#include <MKRGSM.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"
#include <Adafruit_LPS2X.h>
#include <SD.h> // include Arduino SD library
#include <ThreeWire.h>  
#include <RtcDS1302.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define SECRET_PINNUMBER     ""
#define SECRET_GPRS_APN      "internet" // replace your GPRS APN
#define SECRET_GPRS_LOGIN    ""    // replace with your GPRS login
#define SECRET_GPRS_PASSWORD "" // replace with your GPRS password
#define countof(a) (sizeof(a) / sizeof(a[0]))
// For SPI mode, we need a CS pin
#define LPS_CS 6

Adafruit_LPS22 lps;
sensors_event_t lps_temp;
sensors_event_t lps_press;
ThreeWire myWire(4,5,3); // IO, SCLK, CE
RtcDS1302<ThreeWire> mkrRtc(myWire);
float sensorVoltage; 
int sensorValue;

// Please enter your sensitive data in the Secret tab or arduino_secrets.h
// PIN Number
const char PINNUMBER[]     = SECRET_PINNUMBER;
// APN data
const char GPRS_APN[]      = SECRET_GPRS_APN;
const char GPRS_LOGIN[]    = SECRET_GPRS_LOGIN;
const char GPRS_PASSWORD[] = SECRET_GPRS_PASSWORD;

// initialize the library instance
GSM gsmAccess;        // GSM access: include a 'true' parameter for debug enabled

GPRS gprs;  // GPRS access

GSMClient client;  // Client service for TCP connection
DHT dht(DHTPIN, DHTTYPE);
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);
// timeout
const unsigned long __TIMEOUT__ = 10 * 1000;
char server[] = "weatherdatapms.ddns.net";
char path[] = "/data_prokat.php?";
int port = 8081; // port 80 is the default for HTTP
File dataLog;

void setup() {
//   initialize serial communications and wait for port to open:
  Serial.begin(9600);
 
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for Leonardo only
//  }

  Serial.println("starting,..");
  // connection state
  bool connected = false;

  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while (!connected) {
    if ((gsmAccess.begin(PINNUMBER) == GSM_READY) &&
        (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD) == GPRS_READY)) {
      connected = true;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("Connected to GPRS network");
  pinMode(16, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(A3,INPUT);
  digitalWrite(16, HIGH); // disable sd cs
  digitalWrite(6, HIGH); // disable lps cs
   if (tsl.begin()) 
  {
    Serial.println(F("Found a TSL2591 sensor"));
  } 
  else 
  {
    Serial.println(F("No sensor found ... check your wiring?"));
    while (1);
  }
  tsl.setGain(TSL2591_GAIN_MED);
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
  dht.begin();
  digitalWrite(6, LOW); // disable lps cs
  lps.begin_SPI(LPS_CS);
  digitalWrite(6, HIGH); // disable lps cs
  digitalWrite(16, LOW);
  if ( !SD.begin(16) )
    Serial.println("failed!");  // initialization error
  digitalWrite(16, HIGH);
  mkrRtc.Begin();
  if (mkrRtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        mkrRtc.SetIsWriteProtected(false);
    }

  if (!mkrRtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        mkrRtc.SetIsRunning(true);
    }
    
  RtcDateTime now = mkrRtc.GetDateTime();
}

void loop() {
  delay (2000);
  float humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();
  // Compute heat index in Celsius (isFahreheit = false)
  float heat_index = dht.computeHeatIndex(temperature,humidity, false);
  digitalWrite(6, LOW); // disable lps cs
  lps.getEvent(&lps_press, &lps_temp);// get lps pressure & lps temp
  float ltemperature = lps_temp.temperature;
  float lpressure = lps_press.pressure;
  digitalWrite(6, HIGH); // disable lps cs
  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  float L= tsl.calculateLux(full, ir) ;
  sensorValue = analogRead(A3);
  sensorVoltage = (5.0/1023.0)*(sensorValue)*(1000);
  int uv=volts_to_uv(sensorVoltage);
  Serial.print(F(" Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.print(F("C "));
  Serial.print(F("  Heat index: "));
  Serial.print(heat_index);
  Serial.print(F("C "));
  Serial.print("Lux = ");
  Serial.println(L);
  Serial.print("Pressure = "); 
  Serial.println(lpressure);
  Serial.print("Ltemp = ");
  Serial.println(ltemperature);
  Serial.print("UV-Index = ");
  Serial.println(uv);
  
   // initialize http service
//    client.print("AT+HTTPINIT");
//    delay(2000); 
//    
//
//    // set http param value // SOS CHECK THE VARIABLES SYNTAX GRAMMAR AND DELAY
//    client.print("AT+HTTPPARA=\"URL\",\"http://localhost/ethernet_example/data.php?"); 
  if (client.connect(server, port)) {
       Serial.println("connected");
       client.print("GET ");
       client.print(path);
       client.print("temperature="); 
       client.print(temperature); 
       client.print("&humidity="); 
       client.print(humidity);
       client.print("&Lux="); 
       client.print(L); 
       client.print("&lps_temperature=");
       client.print(ltemperature);
       client.print("&lps_pressure=");
       client.print(lpressure);
       client.print("&UV-Light=");
       client.println(uv);
  } else {
    // if you didn't get a connection to the server:
       Serial.println("connection failed");
  }

  RtcDateTime now = mkrRtc.GetDateTime();
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
  
  digitalWrite(16, LOW);// ENABLE SD
  // open Log.txt file with write permission                    
  dataLog = SD.open("LogCN.txt", FILE_WRITE);
  dataLog.print(datestring);
  dataLog.print("     "); 
  dataLog.print(temperature) ;
  dataLog.print( "°C   |   ");
  dataLog.print(humidity);
  dataLog.print("  | ");
  dataLog.print(L);
  dataLog.print("  | ");
  dataLog.print(lpressure);
  dataLog.print("   |  ");
  dataLog.println(ltemperature);
  dataLog.close();       
  
  delay(100);   // wait 100ms
    digitalWrite(16, HIGH); // DISABLE SD



    
    delay(2000); 
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
