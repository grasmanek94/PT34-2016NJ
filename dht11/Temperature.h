
#include "dht11.h"
#include <arduino.h>

#ifndef Temperatuur_h
#define Temperatuur_h

class Temperatuur:ISensor{
	
	public:
		Temperatuur(&IMesurementSink MesurementSink, int targetInterval, char* type, int index);
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
		int temp;
		int pin;
	
};

#endif