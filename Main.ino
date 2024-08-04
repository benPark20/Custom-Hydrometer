#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial1.begin(9600);
  Serial1.println("Hello, Raspberry Pi Pico W!");
  dht.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  // variables
  float t = dht.readTemperature(true);
  float h = dht.readHumidity();
  //print humidity
  Serial.print(F("Humidity: "));
  Serial.print(h);
}
