#include "json.hpp"

String Json::measurementToJson(const Measurement &measurement)
{
    String result;

    result += "{\"type\": \"";
    result += measurement.getType();
    result += "\", \"index\":";
    result += measurement.getId();
    result += ", \"value\":";
    result += measurement.getData();
    result += "}";

    return result;
}
