#include <SPI.h>
#include <WiFiNINA.h>
#include <MQTT.h>

WiFiSSLClient net;
MQTTClient mqtt(1024);


const char wifi_ssid[] = "DailyLab2";
const char wifi_password[] = "DailyLab0525";

const char server[] = "MyFeeder.azure-devices.net";
const char clientId[] = "Feeder1";
const char username[] = "MyFeeder.azure-devices.net/Feeder1/?api-version=2018-06-30";
const char password[] = "SharedAccessSignature sr=MyFeeder.azure-devices.net%2Fdevices%2FFeeder1&sig=2En%2Bu0GkTmcpLJjVsuT6rGsm7eDvdDYvO%2FRavGxvSic%3D&se=1643956343";

// Azure IoT Hub MQTT topics
// https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-mqtt-support#sending-device-to-cloud-messages
String subTopic = "devices/Feeder1/messages/devicebound/#";

int status = WL_IDLE_STATUS;

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
