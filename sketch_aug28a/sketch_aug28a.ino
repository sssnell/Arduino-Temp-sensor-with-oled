#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
  
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
 
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 8 // digital pin connected to sensor
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)


DHT dht(DHTPIN, DHTTYPE); 

const int ledpin13 = 13; //SET'S PIN 13 AS THE LED POWER PIN
const int ledpin12 = 12;
const int ledpin11 = 11;

 
void setup() {
  Serial.begin(115200);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  pinMode(ledpin13, OUTPUT);
  pinMode(ledpin12, OUTPUT);
  pinMode(ledpin11, OUTPUT);
}
 
void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  }
 
  //clear display
  display.clearDisplay();
 
  // display temperature
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(10,9);
  display.print(t);
  display.print(" ");
  display.setCursor(80,10);
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");
  
  // display humidity
  display.setTextSize(1);
  display.setCursor(30, 25);
  display.print("Humidity: ");
  display.setTextSize(1);
  display.setCursor(85, 25);
  display.print(h);
  display.setCursor(115, 25);
  display.print(" %"); 
  
  display.display(); 

  if (t < 20) digitalWrite(ledpin13, HIGH); // IF TEMP IS UNDER 20 SET PIN 13 TO HIGH. GREEN LED

  if (t > 20, t < 25) digitalWrite(ledpin11, HIGH); // IF TEMP IS GREATER THAN 20 SET PIN 11 TO HIGH. AMBER LED

  if (t > 25) digitalWrite(ledpin12, HIGH); // IF TEMP IS OVER 25 SET PIN 12 TO HIGH. RED LED
}
