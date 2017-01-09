#include "SFE_BMP180.h"
#include <Arduino.h>

#ifndef Pressure_h
#define Pressure_h

class Pressure:ISensor{
	
	public:
	
		Pressure(&IMesurementSink MesurementSink, int targetInterval, char* type, int id);
		void run();
		void SetTargetInterval(int targetInterval);
		int getTargetInterval();
		char* getType();
		void setType();
		int getIndex();
		void setIndex();
	
	private:
	
	int interval;
	unsigned long lastmillis;
	IMesurementSink* s;
	int index;
	char* type;
	int Press;	
};

#endif