#include "SFE_BMP180.h"
#include "IMeasurementSink.hpp"
#include "ISensor.hpp"
#include <Arduino.h>

#ifndef Pressure_h
#define Pressure_h

class PressureSensor : public ISensor {

  public:

    PressureSensor(IMeasurementSink &iMeasurementSink, int targetInterval, char* type, int id);
    void init();
    void run();
    void SetTargetInterval(int targetInterval);
    int getTargetInterval();
    char* getType();
    int getIndex();
    void setIndex(int Index);

  private:

    int interval;
    unsigned long lastmillis;
    IMeasurementSink& s;
    int index;
    char* type;
    int Press;
};

#endif
