
#include "dht11.h"
#include <Arduino.h>
#include "IMeasurementSink.hpp"
#include "ISensor.hpp"

#ifndef Temperature_h
#define Temperature_h

class TemperatureSensor : public ISensor{
	
	public:
		TemperatureSensor(IMeasurementSink &iMeasurementSink, int targetInterval, char* type, int index);
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
		double temp;
		int pin;
	
};

#endif
