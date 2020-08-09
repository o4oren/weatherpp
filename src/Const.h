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

const utility::string_t DEGREES_SYMBOL = os =="windows" ? U("") : U("\u00B0");
const utility::string_t DEGREES_METRIC = DEGREES_SYMBOL + U("C");
const utility::string_t DEGREES_IMPERIAL = U("F");
}

#endif // WEATHERPP_SRC_CONST_H
