#ifndef ISensor_h
#define ISensor_h

#include "IMeasurementSink.h"

class ISensor
{

   public:
   	  virtual ISensor(measurementSink: &IMeasurementSink) = 0;
      virtual void run() = 0;
      virtual void setTargetInterval(int interval) = 0;
      virtual int getTargetInterval() = 0;
      virtual String getPlacement() = 0;
      virtual String getPosition() = 0;
};
#endif /* ISensor_h */