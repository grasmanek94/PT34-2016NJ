#ifndef PACKET_HPP_
#define PACKET_HPP_

#include "Measurement.hpp"

class Packet {
public:
    Packet(Measurement& measurement);
    virtual ~Packet();

    char* toJsonFormat();

private:
    Measurement& _measurement;
};

#endif // PACKET_HPP_
