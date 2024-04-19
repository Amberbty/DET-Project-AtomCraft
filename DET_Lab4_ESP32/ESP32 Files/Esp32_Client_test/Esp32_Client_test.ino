/****************************************************************************************************************************
  ESP32-Client.ino
  For ESP32.

  Based on and modified from Gil Maimon's ArduinoWebsockets library https://github.com/gilmaimon/ArduinoWebsockets
  to support STM32F/L/H/G/WB/MP1, nRF52 and SAMD21/SAMD51 boards besides ESP8266 and ESP32


  The library provides simple and easy interface for websockets (Client and Server).

  Built by Khoi Hoang https://github.com/khoih-prog/Websockets2_Generic
  Licensed under MIT license
 *****************************************************************************************************************************/
/****************************************************************************************************************************
  Esp32 Websockets Client

  This sketch:
        1. Connects to a WiFi network
        2. Connects to a Websockets server
        3. Sends the websockets server a message ("Hello to Server from ......")
        4. Prints all incoming messages while the connection is open

  Hardware:
        For this sketch you only need an ESP32 board.

  Originally Created  : 15/02/2019
  Original Author     : By Gil Maimon
  Original Repository : https://github.com/gilmaimon/ArduinoWebsockets

*****************************************************************************************************************************/

#include "defines.h"

#include <WebSockets2_Generic.h>
#include <WiFi.h>

using namespace websockets2_generic;

WebsocketsClient client;
const int FORCE_SENSOR_PIN = A0;

void onEventsCallback(WebsocketsEvent event, String data)
{
  (void) data;

  if (event == WebsocketsEvent::ConnectionOpened)
  {
    Serial.println("Connnection Opened");
  }
  else if (event == WebsocketsEvent::ConnectionClosed)
  {
    Serial.println("Connnection Closed");
  }
  else if (event == WebsocketsEvent::GotPing)
  {
    Serial.println("Got a Ping!");
  }
  else if (event == WebsocketsEvent::GotPong)
  {
    Serial.println("Got a Pong!");
  }
}

void setup()
{
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  Serial.print("\nStart ESP32-Client on ");
  Serial.println(ARDUINO_BOARD);
  Serial.println(WEBSOCKETS2_GENERIC_VERSION);

  Serial.println();
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

  // Serial.println();
  // Serial.println("Scanning available networks ...");
  // listNetworks();
  // delay(10000);

  // Connect to wifi
  WiFi.begin(ssid, password);

  // Wait some time to connect to wifi
  for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++)
  {
    Serial.print(".");
    delay(1000);
  }

  // Check if connected to wifi
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("No Wifi!");
    return;
  }

  Serial.print("Connected to Wifi, Connecting to WebSockets Server @");
  Serial.println(websockets_server_host);

  // run callback when messages are received
  client.onMessage([&](WebsocketsMessage message)
  {
    Serial.print("Got Message: ");
    Serial.println(message.data());
  });

  // run callback when events are occuring
  client.onEvent(onEventsCallback);

  // try to connect to Websockets server
  bool connected = client.connect(websockets_server_host, websockets_server_port, "/");

  if (connected)
  {
    Serial.println("Connected!");
    String WS_msg = String("Hello to Server from ") + BOARD_NAME;
    client.send(WS_msg);
  }
  else
  {
    Serial.println("Not Connected!");
  }

  pinMode(FORCE_SENSOR_PIN, INPUT);
}

void loop()
{
  // let the websockets client check for incoming messages
  if (client.available())
  {
    client.poll();
  }

  String WS_msg = String("ping ping yay ") + BOARD_NAME;
  client.send(WS_msg);

  delay(100);

  // Read the analog value from the force sensor
  int sensorValue = analogRead(FORCE_SENSOR_PIN);

  // Print the sensor value to the serial monitor
  Serial.println(sensorValue);

  // You can add additional code here to process the sensor value

  delay(100); // Add a small delay to prevent flooding the serial monitor

}

void listNetworks() {
  // scan for nearby networks
  int numSsid = WiFi.scanNetworks();
  while (numSsid == -1) {
    Serial.println("Couldn't get a wifi connection");
    delay(3000);
    numSsid = WiFi.scanNetworks();
  }

  // print the list of networks seen
  Serial.print("Number of available networks:");
  Serial.println(numSsid);

  // print the network number and name for each network found
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
  }
}

void touch_ISR() {
  // This function will be called when touch is detected
  Serial.println("Touch detected!");
}