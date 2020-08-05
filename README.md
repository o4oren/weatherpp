## WeatherPP
A command line weather tool written in C++.

This is a first naive implementation of a command line tool to query and display weather data.
At this point in can only use the openweathermap service, and displays the result as a raw json text.
It only works on POSIX compliant machines at this point.

Usage: ./weatherpp -provider openweathermap -a [API KEY] LOCATION_NAME

## Configuration
The program accept weather provider, api-key, location and other parameters via command line arguments.
If the -s / --save-config argument is specified, the program will create a config file named .weatherpp in the user's 
home directory.
If a config file exists, the utility will not require subsequent settings, other than an optional location.
You can always override the confguration by passing command line arguments and update the configuration by setting -s. 

Configuration file is of the format:
```
provider=openweathermap
apikey=XXXXXXXXXX
location=london
units=metric
```

## Dependencies
Microsoft's rest SDK - https://github.com/microsoft/cpprestsdk

## TODO
- [ ] Support geo IP location (so there is no need to state location)
- [x] Create a provider interface and factory to enable generic support for multiple weather providers
- [x] Tidy data presentation
- [ ] Refactor providers and configuration to support multiple vendors
- [ ] Support MS Windows
- [ ] Complete data presentation
- [ ] Provide "graphic" (ASCII) representation
- [ ] Add weather forecast to data (Currently shows only current weather)
- [ ] Add Config/cli argument to control metric/imperial system