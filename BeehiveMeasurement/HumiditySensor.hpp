#include "dht11.h"
#include <Arduino.h>
#include "ISensor.hpp"

#ifndef Humidity_h
#define Humidity_h

class HumiditySensor : public ISensor{
	
	public:
	
	HumiditySensor(IMeasurementSink &iMeasurementSink, int targetInterval, char* type, int index);
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
	int hum;
	int pin;
	
};

#endif

