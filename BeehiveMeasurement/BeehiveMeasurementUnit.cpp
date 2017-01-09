#include "BeehiveMeasurementUnit.hpp"

BeehiveMeasurementUnit::BeehiveMeasurementUnit(size_t nrSensors, ISensor** sensors)
    :_nrSensors(nrSensors), _sensors(sensors), _running(false)
{
  init();
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
        ISensor** _sensorsCopy = _sensors;

        for(int i = 0; i < _nrSensors; i++)
        {
            (*_sensorsCopy)->run();
            _sensorsCopy++;
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
