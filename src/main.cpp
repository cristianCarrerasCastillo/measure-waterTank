/* 
* Sensor de llenado de estanque de agua
* altura del estanque: 1.5 mts (sin revalsar)
* dev: Cristian Carreras
*/

#include <Arduino.h>
#include <Ultrasonic.h>

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
void loop() {
  int distance = 0;
  distance = pingPing.read();
  Serial.print("Distancia: ");
  Serial.print(distance);
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