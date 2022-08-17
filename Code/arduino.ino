#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MQ7.h"
//#include <MQ2.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   5
#define OLED_DC    6
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
#define DHTPIN 4

#define DHTTYPE DHT11   // DHT 11

MQ7 mq7(A2, 5.0);

DHT dht(DHTPIN, DHTTYPE);
int mq135, smoke;
int mq77;
int h, t, f;
String se1, se2, se3, se;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  dht.begin();
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("HELLO  ");
  display.display();

  delay(1000);
}
void disp(){
   display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Temperature: " + String(t) + " C ");
  display.println("Humidity: " + String(h) + " %");
  display.println("PPM OF CO " + String(mq77));
  display.println("PPM OF SMOKE " + String(smoke));
 
  if (mq135 > 500)
    display.println("Poor Air");
  if (mq135 < 500)
    display.println("Fresh Air");
  display.display();
  display.display();
  }
void loop() {
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();

 
  mq77 = mq7.getPPM();
  smoke = analogRead(A1);
   mq135 = analogRead(A0);
   se1=String(t);
   se2=String(h);
   mySerial.println(se1+','+se2+','+ String(mq77, DEC) + ',' + String(smoke, DEC) + ',' + String(mq135, DEC));  
  mySerial.end();
 
  delay(1000);
 disp();
mySerial.begin(9600);
}