#include <SmartBeeHive/SerialSender.hpp>
//#include <Arduino.h>

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
    Packet packet(measurement);
    sendPacket(packet);
}

void SerialSender::sendPacket(Packet packet)
{
    //Serial.println(packet.toJsonFormat());
}
