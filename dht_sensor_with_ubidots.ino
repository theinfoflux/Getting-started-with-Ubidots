// This example sends data to multiple variables to
// Ubidots through HTTP protocol.

/****************************************
 * Include Libraries
 ****************************************/

#include "Ubidots.h"
#include "DHT.h"
int DHTPIN= D3;
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
float temp; //to store the temperature value
float hum; // to store the humidity value

/****************************************
 * Define Instances and Constants
 ****************************************/

const char* UBIDOTS_TOKEN = "BBFF-B9Um2T2lf1wtQ99aBcja8axoqdycya";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "theinfoflux";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "12345678";      // Put here your Wi-Fi password
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

/****************************************
 * Auxiliar Functions
 ****************************************/

// Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  Serial.begin(115200);
  dht.begin();          //Begins to receive Temperature and humidity values.  
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  // ubidots.setDebug(true);  // Uncomment this line for printing debug messages
}

void loop() {
 temp = dht.readTemperature();
 hum = dht.readHumidity();
  ubidots.add("Temperature", temp);  // Change for your variable name
  ubidots.add("Humidity", hum);

  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id

  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
  }

  delay(5000);
}
