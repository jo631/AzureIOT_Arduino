#include <SPI.h>
#include <WiFiNINA.h>
#include <MQTT.h>

WiFiSSLClient net;
MQTTClient mqtt(1024);

const char wifi_ssid[] = "---";
const char wifi_password[] = "---";

const char server[] = "---IoTHubName---.azure-devices.net";
const char clientId[] = "---DeviceName---";
const char username[] = "---IoTHubName---.azure-devices.net/---DeviceName---/?api-version=2018-06-30";
const char password[] = "---SAS Token---";

// Azure IoT Hub MQTT topics
// https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-mqtt-support#sending-device-to-cloud-messages
String subTopic = "devices/---DeviceName---/messages/devicebound/#";


void setup() {
  Serial.begin(9600);
  
  Serial.println("Connecting WiFi");
  connectWiFi();

  // Start the MQTT connection
  Serial.println("Setting up MQTT");
  mqtt.begin(server, 8883, net);
  
  // define function for incoming messages
  mqtt.onMessage(messageReceived);
  
}

void loop() {
  mqtt.loop();
  
  if (!mqtt.connected()) {
    connectMQTT();
  }

  delay(500);
}


void connectWiFi() {
  // Check for the WiFi module
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  Serial.print("WiFi firmware version ");
  Serial.println(WiFi.firmwareVersion());
  
  // attempt to connect to WiFi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(wifi_ssid);
    status = WiFi.begin(wifi_ssid, wifi_password);

    // wait 3 seconds for connection
    delay(3000);
  }
  Serial.println("Connected to WiFi");
  printWiFiStatus();
}

void connectMQTT() {
  
  Serial.print("Connecting MQTT...");
  while (!mqtt.connect(clientId, username, password)) {
    Serial.print(".");
    delay(500);
  }

  mqtt.subscribe(subTopic);
  Serial.println("connected.");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  if (payload ==   "ON") { 
    // Func()
  } 
}

void printWiFiStatus() {
  // print your WiFi IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}
