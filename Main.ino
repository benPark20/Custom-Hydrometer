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
//settign up rgb pins
const RGBPins [] = {16, 17, 18, 19, 20, 21, 26, 27}
//global variables
float lastH;
float lastT;

void setup() {
  Serial1.begin(9600);
  Serial1.println("Hello, Raspberry Pi Pico W!");
  dht.begin();
  for( int i=0; i<9; i++)
    pinMode(RGBPins[i], OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(F("Booting..."));
  display.display();
  delay(2000);
  display.setCursor(0, 20);
  display.println(F("Done!"));
  display.display();
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
    display.println(F("ERROR 1"));
    display.display();
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
    
    //show humidity on LEDs
    if (h < 30){
      analogWrite(RGBPins[17], 255);
    }
  
    // display contitions
    display.clearDisplay();
    display.display();
    display.setTextSize(4);
    display.setCursor(7,7);
    char hStr[6];
    dtostrf(h, 4, 1, hStr);
    display.print(hStr);
    display.println(F("%"));
    display.setCursor(20,47);
    display.setTextSize(2);
    display.print(t);
    display.println(F(" F"));
    display.setTextSize(0);
    display.setCursor(86,44);
    display.print("o");
    display.display();
  }
  else {
    return;
  }
  delay(2000);
}
