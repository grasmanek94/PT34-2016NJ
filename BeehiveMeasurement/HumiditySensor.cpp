#include "HumiditySensor.hpp"
#include "Measurement.hpp"
#include "dht11.h"

HumiditySensor::HumiditySensor(IMeasurementSink &iMeasurementSink, int targetInterval, char* type, int index)
:ISensor(iMeasurementSink, targetInterval, type, index)
,interval(targetInterval)
,lastmillis(0)
,s(iMeasurementSink)
,index(index)
,type(type)
,hum(0)
,pin(2)
{

	
}

void HumiditySensor::run(){
	if(millis() - lastmillis >= interval){
    dht11 Sensor;
		if(Sensor.getValue(pin) == 0){
			hum = Sensor.getHumidity();
		}
		
		Measurement ms(hum, type, index);
		s.sendMeasurement(ms);
		lastmillis = millis();
	}	
}

void HumiditySensor::SetTargetInterval(int targetInterval){
	if(targetInterval > 0){
		interval = targetInterval;
	}
}

int HumiditySensor::getTargetInterval(){
	return interval;
}

char* HumiditySensor::getType(){
	return type;	
}

int HumiditySensor::getIndex(){
	return index;
	
}

void HumiditySensor::setIndex(int Index){
	if(Index > 0){
		index = Index;
	}	
}
