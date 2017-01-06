#include <SmartBeeHive/Packet.hpp>


Packet::Packet(Measurement &measurement) : _measurement(measurement)
{

}

Packet::~Packet()
{

}

char *Packet::toJsonFormat()
{
    
}
