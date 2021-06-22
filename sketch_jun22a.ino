#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const char* ssid = "NetMASTER Uydunet-032B";   
const char* password = "";           
String APIKEY = "25e55702ac799e04cbc9b9119615573d";                                 
String CityID = "738025";  //Istanbul City ID
char servername[]= "api.openweathermap.org"; 
String result;
int  counter = 50;                                      
String weatherForecast ="";
String weatherMyLocation = "";
float temp;
WiFiClient client;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD

void setup() {
  Serial.begin(115200);
  int cursorPosition=0;
  lcd.begin();
  lcd.backlight();
  lcd.print("Please Wait");  
  WiFi.begin(ssid, password);  // wifi start
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    lcd.setCursor(cursorPosition,2); 
    lcd.print(".");
    cursorPosition++;
  }
  lcd.clear();
  lcd.print(" Connected");
  delay(1000);
}

void loop() {
    if(counter == 60){
      counter = 0;
      getWeatherData();
    }
    else{
      counter++;
      displayConditions(temp,weatherMyLocation,weatherForecast);
      delay(2000);
    }
}

void getWeatherData(){
  if (client.connect(servername, 80)){ 
     client.println("GET /data/2.5/weather?id=" + CityID + "&units=metric&APPID="+APIKEY);
     client.println("Host: api.openweathermap.org");
     client.println("User-Agent: ArduinoWiFi/1.1");
     client.println("Connection: close"); 
     client.println();
  } 
  else{
   Serial.println("connection failed"); 
   Serial.println();
  }

  while(client.connected() && !client.available()) 
    delay(1);                                       
  while (client.connected() || client.available()){ 
     char c = client.read();       
     result = result+c;
  }
  client.stop();  //stop client
  
  result.replace('[', ' ');
  result.replace(']', ' ');
  char jsonArray [result.length()+1];
  result.toCharArray(jsonArray,sizeof(jsonArray));
  jsonArray[result.length() + 1] = '\0';
  StaticJsonBuffer<1024> json_buf;
  JsonObject &root = json_buf.parseObject(jsonArray);
  
  if (!root.success())
    Serial.println("parseObject() failed");
  
  String location = root["name"];
  float temperature = root["main"]["temp"];
  String weather = root["weather"]["main"];

  
  weatherForecast = forecast;
  weatherMyLocation = location;
  temp = temperature;
}

void displayConditions(float temp,String location,String forecast){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(location);// yalova
  
  lcd.setCursor(8,0);
  lcd.print(temp,1);  // tempature for yalova
  lcd.print((char)223);
  lcd.print("C ");
  
}
