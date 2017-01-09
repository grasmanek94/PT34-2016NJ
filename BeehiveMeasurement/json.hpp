#ifndef JSON_HPP_
#define JSON_HPP_

#include <Arduino.h>
#include "Measurement.hpp"

namespace Json {

String measurementToJson(const Measurement& measurement);


} // namespace Json

#endif // JSON_HPP_
