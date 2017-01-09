#include "TemperatureSensor.hpp"
#include "Measurement.hpp"

TemperatureSensor::TemperatureSensor(IMeasurementSink &iMeasurementSink, int targetInterval, char* type, int index)
:ISensor(iMeasurementSink, targetInterval, type, index)
,interval(targetInterval)
,lastmillis(0)
,s(iMeasurementSink)
,index(index)
,type(type)
,temp(0)
,pin(2)
{	

}

void TemperatureSensor::init(){
  
}

void TemperatureSensor::run(){
	if(millis() - lastmillis >= interval){
    dht11 Sensor;
		if(Sensor.getValue(pin) == 0){
			temp = Sensor.getTemperature();
		}
		
		Measurement ms(temp, type, index);
		s.sendMeasurement(ms);
		lastmillis = millis();
	}
	
}

void TemperatureSensor::SetTargetInterval(int targetInterval){
	if(targetInterval > 0){
		interval = targetInterval;
	}
}

int TemperatureSensor::getTargetInterval(){
	return interval;
}

char* TemperatureSensor::getType(){
	return type;	
}

int TemperatureSensor::getIndex(){
	return index;
	
}

void TemperatureSensor::setIndex(int Index){
	if(Index > 0){
		index = Index;
	}	
}
