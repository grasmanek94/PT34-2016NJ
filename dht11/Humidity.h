#include "dht11.h"
#include <arduino.h>

#ifndef Humidity_h
#define Humidity_h

class Humidity:ISensor{
	
	public:
	
	Humidity(&IMesurementSink MesurementSink, int targetInterval, char* type, int id);
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
	int hum;
	int pin;
	
};

#endif

