#include "LightSensor.h"

LightSensor sensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
sensor = new LightSensor();
}

void loop() {
  // put your main code here, to run repeatedly:
sensor.requestData();
delay(200);
uint16_t result = 0;
result = sensor.readData();
Serial.print(result, DEC);
}
