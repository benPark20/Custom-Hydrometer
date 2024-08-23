// Now turn this trash into treasure!
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
//define dht object
#define DHTPIN 28
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//define screen object
Adafruit_SSD1306 display(128, 64);
//define rgb
#define G 6
#define R 7
#define B 8
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
  //set rbg pins
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
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
      if (!displayOn) {
        display.clearDisplay();
        display.display();
      }
      else {
        lastT = 1;
      }
    }
  }
}

  lastButtonState = reading;

  if (displayOn) {
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
      display.setCursor(25, 7);
      int hInt = static_cast<int>(round(h));
      display.print(hInt);
      display.println(F("%"));
      display.setCursor(20, 47);
      display.setTextSize(2);
      display.print(t);
      display.println(F(" F"));
      display.setTextSize(0);
      display.setCursor(86, 44);
      display.print("o");
      display.display();

      if (h > 50) {
        analogWrite(R, 255);
        analogWrite(G, 0);
        analogWrite(B, 0);
      } else if (h > 30) {
        analogWrite(R, 100);
        analogWrite(G, 100);
        analogWrite(B, 0);
      } else {
        analogWrite(R, 0);
        analogWrite(G, 255);
        analogWrite(B, 0);
      }
    }
  } else {
    display.clearDisplay();
    display.display();
  }
}
