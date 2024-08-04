// Now turn this trash into treasure!
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

//global variables
float lastH;
float lastT;

void setup() {
  Serial1.begin(9600);
  Serial1.println("Hello, Raspberry Pi Pico W!");
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
}
void loop() {
  // put your main code here, to run repeatedly:
  // variables
  float t = dht.readTemperature(true);
  float h = dht.readHumidity();

//check if variables get a reading
  if (isnan(h) || isnan(t)) {
    Serial1.println(F("Failed to read from DHT sensor!"));
    display.clearDisplay();
    display.println(F("ERROR"));
  return;
  }
  if(lastH != h || lastT != t){
    lastH = h;
    lastT = t;
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
  else {
    return;
  }
  delay(2000);
}
