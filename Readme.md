
# ESP8266 dweet.io library


## Requiremets

* [Arduino IDE 1.6.5 or higher](https://www.arduino.cc/en/Main/Software)
* [ArduinoJson library](https://github.com/bblanchon/ArduinoJson/archive/master.zip)
* [dweetESP8266 library](https://github.com/gamo256/dweet-esp/archive/master.zip)


## Setup

1. Go to the Arduino IDE, click on **Files -> Preferences** and enter http://arduino.esp8266.com/versions/2.2.0/package_esp8266com_index.json into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas
2. Open Boards Manager from **Tools -> Board menu** and install esp8266 platform (and don't forget to select your ESP8266 board from Tools > Board menu after installation)
3. Download the dweetESP8266 library [here](https://github.com/gamo256/dweet-esp/archive/master.zip)
4. Now, click on **Sketch -> Include Library -> Add .ZIP Library**
5. Select the .ZIP file of dweet-esp and then "Accept" or "Choose"
6. Close the Arduino IDE and open it again.
    
## Send one value to dweet.io

To send a value to dweet.io, go to **Sketch -> Examples ->  dweet-esp library** and select the "DweetValue" example. 
Put your thing name where indicated, as well as the WiFi settings.
Upload the code, open the Serial monitor to check the results. If no response is seen, try unplugging your board and then plugging it again. Make sure the baud rate of the Serial monitor is set to the same one specified in your code.

```c++
#include "dweetESP8266.h"
#define THIG_NAME  "Your_thing_neme_here"  // Put here your thing name
#define WIFISSID "ssid"
#define PASSWORD "password"

dweet client;

void setup(){
    Serial.begin(115200);
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
}
void loop(){
    String val = String(analogRead(A0));
    client.add(key, val); // specifies the args of type "String"
    client.sendAll(THIG_NAME);
}
```


## Get one value from dweet.io

To get the last value of a variable from dweet.io, go to **Sketch -> Examples -> dweet-esp library** and select the "GetDweet" example. 
Put your thing name where indicated, as well as the WiFi settings.
Upload the code, open the Serial monitor to check the results. If no response is seen, try unplugging your boaurd and then plugging it again. Make sure the baud rate of the Serial monitor is set to the same one specified in your code.

```c++
#include "dweetESP8266.h"
#define THIG_NAME  "Your_thing_neme_here"  // Put here your thing name
#define WIFISSID "ssid"
#define PASSWORD "password"

dweet client;

void setup() {
    Serial.begin(115200);
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
}

void loop() {
    // specifies the args of type "String"
    String value = client.getDweet(THIG_NAME, key);
    Serial.println(value);
}
```

## Send multiple values to dweet.io 

To send multiple values to dweet.io, go to **Sketch -> Examples -> dweet-esp library** and select the "DweetMultiValues" example. 
Put your thing name where indicated, as well as the WiFi settings.
Upload the code, open the Serial monitor to check the results. If no response is seen, try unplugging your boaurd and then plugging it again. Make sure the baud rate of the Serial monitor is set to the same one specified in your code.

```c++
#include "dweetESP8266.h"
#define THIG_NAME  "Your_thing_neme_here"  // Put here your thing name
#define WIFISSID "ssid"
#define PASSWORD "password"

dweet client;

void setup(){
    Serial.begin(115200);
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
}
void loop(){
    String value1 = String(analogRead(A0));
    String value2 = String(analogRead(A1));
    String value3 = String(analogRead(A2));
    client.add(key1, value1);  // specifies the args of type "String"
    client.add(key2, value2);
    client.add(key3, value3);
    client.sendAll(THIG_NAME);
}
```
