#ifndef Sensor_h
#define Sensor_h

#include "ISensor.h"

class Sensor: public ISensor
{
	public:
		Sensor(String k, int p)
		{
			keyword = k;
			pin = p;
		}
		virtual int getMeasurementData() = 0;
		int getPin()
		{
			return pin;
		}
		void setPin(int p)
		{
			pin = p;
		}
		String getKeyword()
		{
			return keyword;
		}
	private:
		String keyword;
		int pin;
};
#endif /* Sensor_h */