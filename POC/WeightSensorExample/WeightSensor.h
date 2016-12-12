#ifndef WeightSensor_h
#define WeightSensor_h

#include "HX711.h"
#include "Sensor.h"

class WeightSensor : Sensor
{
	private:
		HX711 scale;
		float calibration_factor = -43800; // This is the correct value for 1 load cell attached with output in kg, use calibration to alter this value
		int pin2;

	public:
		//Create Weightsensor object; k = keyword, p = DOUT and p2 = CLK
		WeightSensor(String k, int p, int p2);
		
		//Start calibration process, use serial monitor on baudrate 9600 and follow instructions printed
		void calibrate();

		//Use this function to get measurement in kg
		int getMeasurementData();

		//Return second pin used by sensor as int
		int getPin2();

		//Return pin used by sensor as int
		//int getPin();

		//Return keyword of sensor
		//String getKeyword();
};

#endif /* WeightSensor_h */