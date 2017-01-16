#include "SerialSender.hpp"
#include "json.hpp"
#include <Arduino.h>

SerialSender::SerialSender(unsigned int baudrate) : _baudrate(baudrate)
{

}

SerialSender::~SerialSender()
{

}

unsigned int SerialSender::getBaudrate()
{
    return _baudrate;
}

void SerialSender::setBaudrate(unsigned int baudrate)
{
    _baudrate = baudrate;
}

void SerialSender::sendMeasurement(Measurement measurement)
{
    auto data = Json::measurementToJson(measurement);
    Serial.println(data);
}
