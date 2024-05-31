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
LedStrip green(0, 200); // gpio 0 (D3), 200 intensity [warning: D3 is used for serial communication, so don't connect anything to it while programming]!

void setup() {
  Serial.begin(9600);
}


void lowWater() {
  red.on();
  yellow.off();
  green.off();
}

void mediumWater() {
  red.on();
  yellow.on();
  green.off();
}

void highWater() {
  red.on();
  yellow.on();
  green.on();
}

void error() {
  red.on();
  yellow.off();
  green.on();
}

void loop() {
  Serial.print("Distancia: ");
  Serial.print(pingPing.read());
  Serial.println(" cm");
  delay(1000);

  switch (pingPing.read())
  {
  case 0 ... 55:
    highWater();
    break;
  case 56 ... 110:
    mediumWater();
    break;
  case 111 ... 170:
    lowWater();
    break;
  default:
    error();
    break;
  }
}