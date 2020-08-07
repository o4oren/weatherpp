
## WeatherPP
![C++ CI](https://github.com/o4oren/weatherpp/workflows/C++%20CI/badge.svg)

weatherpp is a command line weather tool written in C++.

Weatherpp is a command line tool to query and display weather data.
At this point in can only use the openweathermap service, and displays the result as a raw json text.
It only works on POSIX compliant machines at this point.

![weatherpp example](https://github.com/o4oren/weatherpp/blob/master/images/screenshot1.png?raw=true)

Usage: ./weatherpp -provider openweathermap -a [API KEY] LOCATION_NAME

## Configuration
The program accept weather provider, api-key, location and other parameters via command line arguments.
If the -s / --save-config argument is specified, the program will create a config file named .weatherpp in the user's 
home directory.
If a config file exists, the utility will not require subsequent settings, other than an optional location.
You can always override the configuration by passing command line arguments and update the configuration by setting -s. 

Configuration file is of the format:
```
provider=openweathermap
apikey=XXXXXXXXXX
location=london
units=metric
```
Only provider and apikey are mandatory.

## usage
./weatherapp -
```
usage: ./weatherpp [option(s)] [LOCATION]
Options:
	-h, --help		Show this help message
	-p, --provider <PROVIDER>	Specify the weather provider name
	-a, --apikey <API-KEY>		Specify the weather provider's API key
	-u, --units <UNITS>		    Specify "metric" or "imperial" - metric is set by default
    -d, --default-location <LOCATION> Specify a default location to be used
	-s, --save-configuration 	Save passed arguments in configuration file

```
If a location is not provided, the utility will attempt to locate your location through the http://ip-api.com service.

### Requirements
There are no requirements for running the binary.
For building:
* Install Microsoft's rest SDK - as per instructions at https://github.com/microsoft/cpprestsdk.
Currently, this is the only external dependency of this project.
* CMake version >= 3.16

## Build
weatherpp uses cmake as its build tool, run the following after installing the requirements.
```
# to set up cmake run from whithin the project root directory:
cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles" .
# To build
cmake --build . --target all -- -j 3
```

## TODO for 1.0
- [x] Support geo IP location (so there is no need to state location)
- [x] Create a provider interface and factory to enable generic support for multiple weather providers
- [x] Tidy data presentation
- [x] Integrate github actions for compilation/test upon push
- [ ] Refactor providers and configuration to support multiple vendors
- [ ] Support MS Windows
- [ ] Complete data presentation
- [ ] Provide "graphic" (ASCII) representation
- [ ] Add weather forecast to data (Currently shows only current weather)
- [x] Add Config/cli argument to control metric/imperial system
