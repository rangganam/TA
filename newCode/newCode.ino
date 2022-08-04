#include <PZEM004Tv30.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Max 20A Unfused";
const char* password = "bonaparte";

//Your Domain name with URL path or IP address with path
String serverName = "http://172.20.10.6/";

//#define batA 27
//#define batB 14
#define relay1 32
#define relay2 33

#if !defined(PZEM_RX_PIN) && !defined(PZEM_TX_PIN)
#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17
#endif

#if !defined(PZEM_SERIAL)
#define PZEM_SERIAL Serial2
#endif

#if defined(ESP32)
PZEM004Tv30 pzem(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN);
#elif defined(ESP8266)
//PZEM004Tv30 pzem(Serial1);
#else
PZEM004Tv30 pzem(PZEM_SERIAL);
#endif

Adafruit_INA219 ina219A(0x41);
Adafruit_INA219 ina219B(0x40);
Adafruit_INA219 ina219C(0x44);
Adafruit_INA219 ina219D(0x45);

int batAPercentage, batBPercentage = 0;
float voltage, current, power, energy, frequency, pf = 0;
float shuntvoltageA, busvoltageA, current_mAA, loadvoltageA, power_mWA = 0;
float shuntvoltageB, busvoltageB, current_mAB, loadvoltageB, power_mWB = 0;
float busvoltageC, busvoltageD = 0;
String charging = "";
unsigned long myTimes = 0;

void setup() {
  Serial.begin(115200);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, 0);
  digitalWrite(relay2, 1);
  uint32_t currentFrequency;

  Serial.println("Hello!");

  if (! ina219A.begin()) {
    Serial.println("Failed to find ina219A");
    while (1) {
      delay(10);
    }
  }
  if (! ina219B.begin()) {
    Serial.println("Failed to find ina21B9B");
    while (1) {
      delay(10);
    }
  }
  if (! ina219C.begin()) {
    Serial.println("Failed to find ina219C");
    while (1) {
      delay(10);
    }
  }
  if (! ina219D.begin()) {
    Serial.println("Failed to find ina219D");
    while (1) {
      delay(10);
    }
  }
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219A.setCalibration_32V_1A();
  //ina219B.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219A.setCalibration_16V_400mA();
  //ina219B.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with ina219A and ina219B ...");
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  dcMeasure();
  acMeasure();
  batSensing();
  if ( batAPercentage < batBPercentage ){
    digitalWrite(relay1, 0);
    digitalWrite(relay2, 1);
    charging = "A";
  }else if ( batBPercentage < batAPercentage ){
    digitalWrite(relay1, 1);
    digitalWrite(relay2, 0);
    charging = "B";
  }
  realtime();
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  dcMeasure();
  acMeasure();
  batSensing();
  realtime();
  if (millis() - myTimes >= 60000UL) {
    history();
    myTimes = millis();
  }
  if (batAPercentage < 20) {
    digitalWrite(relay1, 1);
    digitalWrite(relay2, 0);
    charging = "A";
  } else if (batBPercentage < 20) {
    digitalWrite(relay1, 0);
    digitalWrite(relay2, 1);
    charging = "B";
  } 
  delay(1000);

}
