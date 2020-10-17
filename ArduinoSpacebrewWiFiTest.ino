/*
	Esp32 Websockets Client

	This sketch:
        1. Connects to a WiFi network
        2. Connects to a Websockets server
        3. Sends the websockets server a message ("Hello Server")
        4. Prints all incoming messages while the connection is open

	Hardware:
        For this sketch you only need an ESP32 board.

	Created 15/02/2019
	By Gil Maimon
	https://github.com/gilmaimon/ArduinoWebsockets

*/

#include <ArduinoWebsockets.h>
#include <Arduino_JSON.h>
#include <WiFi.h>
#include "connection.h"

using namespace websockets;

WebsocketsClient client;
void setup() {
    Serial.begin(115200);
    // Connect to wifi
    WiFi.begin(ssid, password);

    // Wait some time to connect to wifi
    for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
        Serial.print(".");
        delay(1000);
    }

    // Check if connected to wifi
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("No Wifi!");
        return;
    }

    Serial.println("Connected to Wifi, Connecting to server.");
    // try to connect to Websockets server
    bool connected = client.connect(websockets_server_host, websockets_server_port, "/");
    if(connected) {
        Serial.println("Connected!");
        JSONVar reg;
        reg["config"]["name"] = "duino";
        reg["config"]["description"] = "";
        reg["config"]["publish"]["messages"][0]["name"]="out";
        reg["config"]["publish"]["messages"][0]["type"]="string";
        reg["config"]["subscribe"]["messages"][0]["name"]="out";
        reg["config"]["subscribe"]["messages"][0]["type"]="string";
        Serial.println(JSON.stringify(reg));
        client.send(JSON.stringify(reg));
    } else {
        Serial.println("Not Connected!");
    }
    
    // run callback when messages are received
    client.onMessage([&](WebsocketsMessage message){
        Serial.print("Got Message: ");
        Serial.println(message.data());
        JSONVar in = JSON.parse(message.data());
        Serial.println(in["message"]["value"]);
        JSONVar out;
        out["message"]["name"] = "out";
        out["message"]["clientName"] = "duino";
        out["message"]["type"] = "string";
        out["message"]["value"] = ((const char*) in["message"]["value"]);
        Serial.println(JSON.stringify(out));
        client.send(JSON.stringify(out));
    });
}

void loop() {
    // let the websockets client check for incoming messages
    if(client.available()) {
        client.poll();
    }
    delay(500);
}
