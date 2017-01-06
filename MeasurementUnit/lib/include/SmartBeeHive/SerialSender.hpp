#ifndef SERIAL_SENDER_HPP_
#define SERIAL_SENDER_HPP_

#include <cstddef>
#include <SmartBeeHive/IMeasurementSink.hpp>
#include <SmartBeeHive/Packet.hpp>

class SerialSender : IMeasurementSink {
public:
    SerialSender(unsigned int baudrate);
    virtual ~SerialSender();

    unsigned int getBaudrate();
    void setBaudrate(unsigned int baudrate);

    virtual void sendMeasurement(Measurement measurement) override;

private:
    unsigned int _baudrate;

    void sendPacket(Packet packet);
};

#endif // SERIAL_SENDER_HPP_
