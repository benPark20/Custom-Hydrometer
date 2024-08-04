
#include "DHT.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
//define dht object
#define DHTPIN 28
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//define screen object
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial1.begin(9600);
  Serial1.println("Hello, Raspberry Pi Pico W!");
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.drawRect(10, 10, 50, 30, WHITE);
}
void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  // variables
  float t = dht.readTemperature(true);
  float h = dht.readHumidity();
  float lastH = 10;
  float lastT = 30;
//check if variables get a reading
  if (isnan(h) || isnan(t)) {
    Serial1.println(F("Failed to read from DHT sensor!"));
    display.clearDisplay();
    display.println(F("ERROR"));
  return;
  }
  if
  //print conditions
  Serial1.print(F("Humidity: "));
  Serial1.println(h);
  Serial1.print(F("Tempurature: "));
  Serial1.println(t);
  // display contitions
  display.clearDisplay();
  display.setTextSize(6);
  display.setCursor(10,10);
  display.print(h);
  display.println(F("%"));
  display.setCursor(50,10);
  display.setTextSize(2);
  display.print(t);
  display.println(F("Deg"));
}
