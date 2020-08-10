//
// Created by oren on 09/08/2020.
//

#ifndef WEATHERPP_SRC_CONST_H
#define WEATHERPP_SRC_CONST_H
#include <string>
#include <cpprest/details/basic_types.h>

using std::string;
namespace weatherpp
{
const string os =
#ifdef _WIN32
    "windows";
#else
    "unix";
#endif

const string DEGREES_SYMBOL = os =="windows" ? "\370" : "\u00B0";
const string DEGREES_METRIC = DEGREES_SYMBOL + "C";
const string DEGREES_IMPERIAL = DEGREES_SYMBOL + "F";
const string WIND_SPEED_METRIC = "m/sec";
}

#endif // WEATHERPP_SRC_CONST_H
