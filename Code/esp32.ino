

#define BLYNK_TEMPLATE_ID "TMPLwqqy0uxk"
#define BLYNK_DEVICE_NAME "Atmosphere dashboard"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT

#include "BlynkEdgent.h"
#include <SoftwareSerial.h>
BlynkTimer timer;
SoftwareSerial ardu;
int smoke,mq135,mq7,tem,hum;

void updates()
{
  Blynk.virtualWrite(V0, tem);
  Blynk.virtualWrite(V1, hum);
  Blynk.virtualWrite(V2,mq135 );
  Blynk.virtualWrite(V3, mq7);
  Blynk.virtualWrite(V4, smoke);
  if (mq135 < 500)
  Blynk.virtualWrite(V5, "FRESH AIR");
  if (mq135 > 500)
  Blynk.virtualWrite(V5, "POOR AIR");
  
}

void setup()
{
  Serial.begin(115200);
  
  ardu.begin(9600, SWSERIAL_8N1, 32, 33, false);
  delay(100);

  BlynkEdgent.begin();
  
  timer.setInterval(5000L, updates);
}

void loop() {
  BlynkEdgent.run();
timer.run();
   if (ardu.available())
  { String dat = ardu.readString();
  int c = 0;
  String val_read = "";

  

  while (dat.charAt(c) != ',')
  {
    val_read += dat.charAt(c);
    c++;
  }
  tem = val_read.toInt();
 // Serial.print("Temperature: ");
 // Serial.println(tem);
  c++;
  val_read = "";

  while (dat.charAt(c) != ',')
  {
    val_read += dat.charAt(c);
    c++;
  }
  hum = val_read.toInt();
 // Serial.print("Humidity: ");
 // Serial.println(hum);
  c++;
  val_read = "";

  while (dat.charAt(c) != ',')
  {
    val_read += dat.charAt(c);
    c++;
  }
  mq7 = val_read.toInt();
 // Serial.print("MQ77: ");
 // Serial.println(mq7);
  c++;
  val_read = "";

  while (dat.charAt(c) != ',')
  {
    val_read += dat.charAt(c);
    c++;
  }
  smoke = val_read.toInt();
 // Serial.print("SMOKE: ");
 // Serial.println(smoke);
  c++;
  val_read = "";
   while (dat.charAt(c) != '\0')
  {
    val_read += dat.charAt(c);
    c++;
  }
  mq135 = val_read.toInt();
 // Serial.print("MQ 135: ");
 // Serial.println(mq135);
    }
}
