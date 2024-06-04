/* 
* Sensor de llenado de estanque de agua
* altura del estanque: 1.5 mts (sin revalsar)
* dev: Cristian Carreras
*/

#include <Arduino.h>
#include <Ultrasonic.h>
#include <ESP8266WiFi.h>
#include <time.h>
#include <env.h>

Ultrasonic pingPing(16); // gpio 16 (D0) 

class LedStrip {
  public:
    LedStrip(uint8_t pin, uint8_t intensity) : pin(pin), intensity(intensity) {
      pinMode(pin, OUTPUT);
    }

    void on() {
      digitalWrite(pin, intensity);
    }

    void off() {
      digitalWrite(pin, LOW);
    }

  private:
    uint8_t pin;
    uint8_t intensity;
};
LedStrip red(5, 200); // gpio 5 (D1), 200 intensity
LedStrip yellow(4, 200); // gpio 4 (D2), 200 intensity
LedStrip green(0, 50); // gpio 0 (D3), 200 intensity [warning: D3 is used for serial communication, so don't connect anything to it while programming]!

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  configTime(-4, 0, "ntp.shoa.cl");

  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    Serial.println("Waiting for time to be set...");
    delay(1000);
    now = time(nullptr);
  }
  Serial.println("Time set!");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.println(asctime(&timeinfo));
}

void lowWater() {
  Serial.println("Low water");
  red.on();
  yellow.off();
  green.off();
}

void mediumWater() {
  Serial.println("Medium water");
  red.on();
  yellow.on();
  green.off();
}

void highWater() {
  Serial.println("High water");
  red.on();
  yellow.on();
  green.on();
}

void error() {
  Serial.println("Error");
  red.on();
  yellow.off();
  green.on();
}

void warning(){
  Serial.println("Cuidado!!, el agua esta llegando al sensor");
  red.on();
  yellow.on();
  size_t count = 3;
  for (size_t i = 0; i < count; i++)
  {
    green.on();
    delay(100);
    green.off();
    delay(100);
  }
}

void off(){
  Serial.println("Apagando leds");
  red.off();
  yellow.off();
  green.off();
}

void loop() {

  time_t now = time(nullptr);
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.println(asctime(&timeinfo));
  if (timeinfo.tm_hour >= 8 || timeinfo.tm_hour < 19) {
    Serial.println("Encendiendo led, Buenos dias");

    int distance = 0;
    distance = pingPing.read();
  
  // corrección para leer de forma más simple el agua restante
  Serial.print("Agua restante: ");
    Serial.print(150 - distance);
    Serial.println(" cm");
    
    switch (distance)
    {
    case 0 ... 19:
      warning();
      break;
    case 20 ... 59:
      highWater();
      break;
    case 60 ... 119:
      mediumWater();
      break;
    case 120 ... 155:
      lowWater();
      break;
    default:
      error();
      break;
  }
    delay(5000);
  } 
  else {
    off();
    delay(1000 * 60 * 60 * 1); // 1 hr
  }
}