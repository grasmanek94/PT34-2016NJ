
#include <SmartBeeHive/BeehiveMeasurementUnit.hpp>

BeehiveMeasurementUnit::BeehiveMeasurementUnit(size_t nrSensors, ISensor* sensors)
    :_nrSensors(nrSensors), _sensors(sensors), _running(false)
{

}

BeehiveMeasurementUnit::~BeehiveMeasurementUnit()
{

}

void BeehiveMeasurementUnit::init()
{
    _running = true;
}

void BeehiveMeasurementUnit::run()
{
    if(_running)
    {
        for(int i = 0; i < _nrSensors; i++)
        {
            _sensors->run();
            _sensors++;
        }
    }
}

void BeehiveMeasurementUnit::stop()
{
    _running = false;
}

bool BeehiveMeasurementUnit::status()
{
    return _running;
}
