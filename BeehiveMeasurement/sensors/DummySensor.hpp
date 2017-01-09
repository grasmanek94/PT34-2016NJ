#ifndef DUMMYSENSOR_H
#define DUMMYSENSOR_H

#include "../IMeasurementSink.hpp"
#include "../ISensor.hpp"

class DummySensor : public ISensor
{
public:
    DummySensor(IMeasurementSink &sink, int targetInterval, char* type, int index)
        : ISensor(sink, targetInterval, type, index),
          _sink(sink)
    { }
    virtual ~DummySensor() { }

    virtual void run() override
    {
        Measurement meas(123, "Dummy", 0);
        _sink.sendMeasurement(meas);
    }

    virtual char* getType() override { return "Dummy"; }

    virtual int getIndex() override { return 0; }
    virtual void setIndex(int index) override { }

private:
    IMeasurementSink &_sink;
};

#endif // DUMMYSENSOR_H
