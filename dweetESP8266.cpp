#include "dweetESP8266.h"
#include <ArduinoJson.h>

/**
 * Constructor.
 */
dweet::dweet(){
   // _thing_name = thing_name;
    maxValues = 5;
    currentValue = 0;
    val = (Value *)malloc(maxValues*sizeof(Value));
}
/** 
 * This function is to get value from the dweet.io API
 * @arg key the key where you will get the data
 * @return value the data that you get from the dweet.io API
 */
String dweet::getDweet(char* thing_name, char* key){
  String value;
  String response;
  uint8_t bodyPosinit;
  uint8_t bodyPosend;
  String dweetKey ="\"";
  dweetKey += key;
  dweetKey += "\":";
  int length = dweetKey.length();

  if (_client.connect(SERVER, PORT)){
        Serial.println(F("Geting your variable"));
        // Make a HTTP request:
        _client.print(F("GET /get/latest/dweet/for/"));
        _client.print(thing_name);
        _client.println(F(" HTTP/1.1"));
        _client.println(F("Host: dweet.io"));
        _client.println(F("User-Agent: ESP8266-WiFi/1.0")); 
        _client.println(F("Connection: close"));
        _client.println();
    }
    while (!_client.available());
    while (_client.available()){
        response = _client.readString();
    }
        //Serial.write(c);
    Serial.println(response);
    bodyPosinit =4+ response.indexOf("\r\n\r\n");
    response = response.substring(bodyPosinit);
    Serial.println(response);

    bodyPosinit =10+ response.indexOf("\"content\"");
    bodyPosend = response.indexOf("}]}");
    response = response.substring(bodyPosinit,bodyPosend);
    Serial.println(response);

    if (response.indexOf(dweetKey) == -1) {
      value = "Key not found";
    } else {
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(response);
        if (!root.success()){
          Serial.println("parseObject() failed");
          value = "parse error.";
        } else {
          const char* val  = root[key];
          value = String(val);
        }
     }

    _client.flush();
    _client.stop();
    return value;
}
/**
 * Add a value of variable to save
 * @arg key variable key to save in a struct
 * @arg value variable value to save in a struct
 */
void dweet::add(char *key, String value){
  if(currentValue == maxValues){
    Serial.println(F("You are sending more than 5 consecutives variables, you just could send 5 variables. Then other variables will be deleted!"));
    //currentValue = maxValues;
  } else {
    (val+currentValue)->id = key;
    (val+currentValue)->value_id = value;
    currentValue++;
  }
}
/**
 * Send all data of all variables that you saved
 * @reutrn true upon success, false upon error.
 */
bool dweet::sendAll(char* thing_name){
    int i;
    String all;
    String str;
    for(i=0; i<currentValue;){
        str = (val+i)->value_id;
        all += String((val + i)->id);
        all += "=";
        all += str;
        i++;
        if(i<currentValue){
            all += "&"; 
        }
    }
    //i = all.length();
    
    if (_client.connect(SERVER, PORT)){
          Serial.println(F("Posting your variables"));
          _client.print(F("POST /dweet/for/"));
          _client.print(thing_name);
          _client.print(F("?"));
          _client.print(all);
          _client.println(F(" HTTP/1.1"));
          _client.println(F("Host: dweet.io"));
          _client.println(F("User-Agent: ESP8266-WiFi/1.0"));
          _client.println(F("Connection: close"));
          _client.println();          
    }
    while(!_client.available());
    while (_client.available()){
        char c = _client.read();
        Serial.write(c);
    }
    currentValue = 0;
    _client.stop();
    return true;    
}
bool dweet::wifiConnection(char* ssid, char* pass){
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}