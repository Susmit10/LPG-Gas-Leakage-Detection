/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  Note: This only works on Android!
        iOS does not support Bluetooth 2.0 Serial Port Profile
        You may need to pair the module with your smartphone
        via Bluetooth settings. Default pairing password is 1234

  Feel free to apply it to any other example. It's simple!

  NOTE: Bluetooth support is in beta!

  This example shows how value can be pushed from Arduino to
  the Blynk App.

  WARNING :
  For this example you'll need Adafruit DHT sensor libraries:
    https://github.com/adafruit/Adafruit_Sensor
    https://github.com/adafruit/DHT-sensor-library

  App project setup:
    Value Display widget attached to V5
    Value Display widget attached to V6
 *************************************************************/

/* Comment this out to disable prints and save space */

#include <SoftwareSerial.h>
SoftwareSerial BT(2,3); // RX, TX

#include <BlynkSimpleSerialBLE.h>
SoftwareSerial SerialBLE(2,3);

#include <DHT.h>

#define BLYNK_PRINT Serial
#define DHTPIN 7          // What digital pin we have connected the temp sensor
#define PIN V8

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "esfzcyndXrl5W0smKLtI7wscoKnb20lJ";

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

float a;
int c;
int i;
float t;

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;



void LPG()
{
  dht.begin();
  a=analogRead(A0);
  //z=digital
  if (isnan(a)) {
    Serial.println("Failed to read from LPG sensor!");
    return;
  }
  Blynk.virtualWrite(V8, a);
  
//  if(a>100)
//  digitalWrite(9, HIGH);
//  
 // Serial.println(a);
  
    
}

void sendSensor()
{
  float h = dht.readHumidity();
   t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  //Serial.println(t);
   
}

BLYNK_WRITE(V8)
{
  //int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
   float d = param.asFloat();
     if(d>100)
     {
        digitalWrite(9, HIGH);
     }
  //Serial.print("V1 Slider value is: ");
  //Serial.println(d);
  //delay(1000);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
   BT.begin(9600);
    SerialBLE.begin(9600);
    Blynk.begin(SerialBLE, auth);

  Serial.println("Waiting for connections...");

  dht.begin();
  pinMode(9, OUTPUT);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
  timer.setInterval(1000L, LPG);
}

void loop()
{
  Blynk.run();
  timer.run();
  if(a>200)
     {
       NOTIFICATION();
      
      for(i=1;i<100;i++)
      {
        digitalWrite(9,HIGH);
        RGBColour(255, 0, 0);
        delay(550);
        digitalWrite(9,LOW);
        RGBColour(0, 0, 0);
        delay(750);
        Blynk.run();
        timer.run();
      }
        

        Blynk.run();
        timer.run();

       if(a>200)
     {
       NOTIFICATION();
      
      for(i=1;i<10;i++)
      {
        digitalWrite(9,HIGH);
        RGBColour(255, 0, 0);
        delay(300);
        digitalWrite(9,LOW);
        RGBColour(0, 0, 0);
        delay(300);
        Blynk.run();
        timer.run();
      }

       Blynk.run();
       timer.run();

       if(a>200)
      {
          NOTIFICATION();
          digitalWrite(9,HIGH);
          RGBColour(255, 0, 0);
          delay(5000);
          Blynk.run();
          timer.run();
      }
        
     }
     else
     {
        digitalWrite(9, LOW);
        RGBColour(0, 0, 0);
     }
   }
}




void RGBColour(int R, int G, int B)
{
  //int a=255;
  analogWrite(11, R);
//  analogWrite(Gpin, G);
//  analogWrite(Bpin, B);

   //delay(delayLEDS);
}

void NOTIFICATION()
{
  
    String e= String(t);
    String f= String(a);
   Blynk.notify("GAS Leakage Detected! Temp : " + e + " Gas Level : " + f);
}


  
