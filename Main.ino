// Now turn this trash into treasure!
#include "DHT.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
//define dht object
#define DHTPIN 28
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//define screen object
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//define LED object
#define LEDPIN 6
#define NUMPIXELS 1
Adafruit_NeoPixel led(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

//define button
#define buttonPin 27

// Global variables
float lastH;
float lastT;
bool displayOn = true;
bool ledOn = true;
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  Serial1.begin(9600);
  Serial1.println("Initialized");

  pinMode(buttonPin, INPUT);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
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

  led.begin();
  led.clear();
  led.setPixelColor(0, led.Color(150, 150, 150));
  led.show();
}
void loop() {
  int reading = digitalRead(buttonPin);

  // Debounce the button press
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

 if ((millis() - lastDebounceTime) > debounceDelay) {
  if (reading != buttonState) {
    buttonState = reading;
    if (buttonState == HIGH) {
      displayOn = !displayOn;
      ledOn = !ledOn;
      if (!displayOn) {
        display.clearDisplay();
        display.display();
        led.clear();
        led.show();
      }
      else {
        lastT = 1;
      }
    }
  }
}

  lastButtonState = reading;

  if (displayOn && ledOn) {
    float t = dht.readTemperature(true);
    float h = dht.readHumidity();

    if (isnan(h) || isnan(t)) {
      Serial1.println(F("Failed to read from DHT sensor!"));
      display.clearDisplay();
      display.println(F("ERROR 1"));
      display.display();
      return;
    }

    if (lastH != h || lastT != t) {
      lastH = h;
      lastT = t;

      Serial1.print(F("Humidity: "));
      Serial1.println(h);
      Serial1.print(F("Temperature: "));
      Serial1.println(t);

      display.clearDisplay();
      display.setTextSize(4);
      display.setCursor(7, 7);
      char hStr[6];
      dtostrf(h, 4, 1, hStr);
      display.print(hStr);
      display.println(F("%"));
      display.setCursor(20, 47);
      display.setTextSize(2);
      display.print(t);
      display.println(F(" F"));
      display.setTextSize(0);
      display.setCursor(86, 44);
      display.print("o");
      display.display();

      if (h > 70) {
        led.setPixelColor(0, led.Color(255, 0, 0));
      } else if (h > 40) {
        led.setPixelColor(0, led.Color(255, 255, 0));
      } else {
        led.setPixelColor(0, led.Color(0, 255, 0));
      }
      led.show();
    }
  } else {
    display.clearDisplay();
    display.display();
    led.clear();
    led.show();
  }
}
