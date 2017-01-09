#ifndef SERIAL_SENDER_HPP_
#define SERIAL_SENDER_HPP_

#include "IMeasurementSink.hpp"

class SerialSender : public IMeasurementSink {
public:
    SerialSender(unsigned int baudrate);
    virtual ~SerialSender();

    unsigned int getBaudrate();
    void setBaudrate(unsigned int baudrate);

    virtual void sendMeasurement(Measurement measurement) override;

private:
    unsigned int _baudrate;
};

#endif // SERIAL_SENDER_HPP_
