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
