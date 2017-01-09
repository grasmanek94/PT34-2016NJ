#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <Arduino.h>

class Timer {
public:
    Timer();
    virtual ~Timer();

    unsigned int getBaudrate();
    void setBaudrate(unsigned int baudrate);

    virtual void sendMeasurement(Measurement measurement) override;

private:
    unsigned int _baudrate;

    void sendPacket(Packet packet);
};

#endif // TIMER_HPP_
