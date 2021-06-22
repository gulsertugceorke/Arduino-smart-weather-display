# Arduino-smart-weather-display
In this project, we can access smart online weather information using the wifi module.
The ESP8266WiFi.h library is a library that is required to connect the wifi module we use.
We use the LiquidCrystal_I2C.h library for the lcd display.
const char * ssid = "NetMASTER Satellite-032B" command is the command of the wifi to connect.
const char * password = "" command contains the modem password.
char servername [] = "api.openweathermap.org" command used to get online weather conditions.
String CityID = "738025"; It contains ID information of the city I live in.
The APIKEY command contains the API key information of the city where I live.
In the void setup section, it says please wait, while trying to connect to wifi.
Later, when the connection is made, it says it is connected. If there is an error in receiving the data, a connection error is returned to the screen.
In the displayConditions function, the information of the location and the air temperature information of the yalova are printed on the screen(in C type).
