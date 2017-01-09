#ifndef WEIGHTSENSOR_HPP_
#define WEIGHTSENSOR_HPP_

#include "HX711.h"
#include "ISensor.hpp"
#include "IMeasurementSink.hpp"
#include "Timer.hpp"

class WeightSensor : public ISensor
{
	private:
		HX711 scale;
    IMeasurementSink &sink;
    int targetInterval;
    char* type;
    int index;
    int pin;
    int pin2;
		float calibration_factor = -43800; // This is the correct value for 1 load cell attached with output in kg, use calibration to alter this value
    Timer timer;

	public:
		//Create Weightsensor object; &s = reference to IMeasurementSink, t = target interval, T = sensor type, i = sensorindex, p = DOUT and p2 = CLK
		WeightSensor(IMeasurementSink &s, int t, char* T, int i, int p, int p2);

    //Delete Weightsensor
    ~WeightSensor();
		
		//Start calibration process, use serial monitor on baudrate 9600 and follow instructions printed
		void reset();

		//Return first pin as int
		int getPin();

    //Return second pin as int
    int getPin2();

    //Use this to keep the sensor running, it checks if the interval has passed and sends the measured data
    void run();

    //Use this to return the sensor type
    char* getType();

    //Use this to set the sensor type
    void setType(char* keyword);

    //Use this to return the sensor index
    int getIndex();

    //Use this to set the sensor index
    void setIndex(int index);
};

#endif /* WEIGHTSENSOR_HPP_ */
