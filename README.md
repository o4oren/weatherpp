## WeatherPP
A command line weather tool written in C++.

This is a first naive implementation of a command line tool to query and display weather data.
At this point in can only use the openweathermap service, and displays the result as a raw json text.
It only works on POSIX compliant machines at this point.

Usage: ./weatherpp -provider openweathermap -a [API KEY] LOCATION_NAME

## Configuration
The program checks for the existence of a configuration file named .weatherpp in the user's home directory.
If such file does not exist, the help message will be displayed. Weather provider and api key can be supplied in such
file or via cli arguments.

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