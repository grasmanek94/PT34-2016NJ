#pragma once
#include <string>
#include <boost/bimap.hpp>
#include <boost/assign.hpp>

enum SensorType
{
	SensorTypeUnknown,
	SensorTypeTemperature,
	SensorTypeSound,
	SensorTypeWeight,
	SensorTypeHumidity,
	SensorTypePressure,
	SensorTypeLightIntensity
};

enum SensorUnit
{
	SensorUnitUnknown,
	SensorUnitDegreesCelsius,
	SensorUnitDecibel,
	SensorUnitKilograms,
	SensorUnitPercent,
	SensorUnitPascal,
	SensorUnitLumen
};

enum SensorPlacement
{
	SensorPlacementInside,
	SensorPlacementOutside
};

typedef boost::bimap<SensorType, std::string> SensorTypeStringType;
const static SensorTypeStringType SensorTypeStrings = boost::assign::list_of< SensorTypeStringType::relation >
	( SensorTypeUnknown, "unknown" )
	( SensorTypeTemperature, "temperature" )
	( SensorTypeSound, "sound" )
	( SensorTypeWeight, "weight" )
	( SensorTypeHumidity, "humidity" )
	( SensorTypePressure, "pressure" )
	( SensorTypeLightIntensity, "light-intensity" );

typedef boost::bimap<SensorUnit, std::string> SensorUnitStringType;
const static SensorUnitStringType SensorUnitStrings = boost::assign::list_of< SensorUnitStringType::relation >
	(SensorUnitUnknown, "unknown")
	(SensorUnitDegreesCelsius, "*C")
	(SensorUnitDecibel, "dB")
	(SensorUnitKilograms, "kg")
	(SensorUnitPercent, "%")
	(SensorUnitPascal, "p")
	(SensorUnitLumen, "lumen");

typedef boost::bimap<SensorPlacement, std::string> SensorPlacementStringType;
const static SensorPlacementStringType SensorPlacementStrings = boost::assign::list_of< SensorPlacementStringType::relation >
	(SensorPlacementInside, "inside")
	(SensorPlacementOutside, "outside");

struct Position
{
	double x;
	double y;
	double z;
};

class Sensor
{
private:
	SensorType type;
	SensorUnit unit;
	SensorPlacement placement;
	size_t num_values;
	Position position;
	double min_value;
	double max_value;
public:
	Sensor();
	Sensor(SensorType _type, SensorUnit _unit, SensorPlacement _placement, size_t _num_values, double min_value, double max_value, const Position& _position);
	virtual ~Sensor();

	virtual SensorType GetSensorType() const;
	virtual SensorUnit GetSensorUnit() const;
	virtual SensorPlacement GetSensorPlacement() const;

	virtual size_t NumValues() const;
	virtual double GetValue(size_t i = 0) const = 0;

	virtual Position GetPosition() const;
	virtual double GetMinValue() const;
	virtual double GetMaxValue() const;
};