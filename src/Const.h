//
// Created by oren on 09/08/2020.
//

#ifndef WEATHERPP_SRC_CONST_H
#define WEATHERPP_SRC_CONST_H
#include <string>
using std::string;
namespace weatherpp
{
const string os =
#ifdef _WIN32
    "windows";
#else
    "unix";
#endif
const string DEGREES_SYMBOL = os =="windows" ? "\370 F" : "\u00B0";
const string DEGREES_METRIC = "C";
const string DEGREES_IMPERIAL = "F";
}



#endif // WEATHERPP_SRC_CONST_H
