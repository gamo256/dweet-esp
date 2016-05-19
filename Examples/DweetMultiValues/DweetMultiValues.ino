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
    client.add(key1, value1); // specifies the args of type "String"
    client.add(key2, value2);
    client.add(key3, value3);
    client.sendAll(THIG_NAME);
}
