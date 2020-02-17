#include <SPI.h>
#include <WiFiNINA.h>
#include <MQTT.h>

WiFiSSLClient net;
MQTTClient mqtt(1024);


const char wifi_ssid[] = "와이파이 아이디";
const char wifi_password[] = "와이파이 비밀번호";

const char server[] = "허브이름.azure-devices.net";
const char clientId[] = "디바이스이름";
const char username[] = "허브이름.azure-devices.net/디바이스이름/?api-version=2018-06-30";
const char password[] = "SAS토큰";

String subTopic = "devices/디바이스이름/messages/devicebound/#";

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
