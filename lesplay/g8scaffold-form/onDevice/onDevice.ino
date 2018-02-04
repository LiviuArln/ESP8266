#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

 
// Connect to the WiFi
const char* mqtt_server = "192.168.0.136";


const char* ssid = "UPCE182474";
const char* password = "Aykaf6h4czrx";
 
WiFiClient espClient;
PubSubClient client(espClient);
const byte ledPin = 0; // Pin with LED on Adafruit Huzzah

int idx = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    char receivedChar = (char)payload[i];
    Serial.print(receivedChar);
    if (receivedChar == '0')
      digitalWrite(LED_BUILTIN, HIGH);
    if (receivedChar == '1')
      digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println();
  idx++;
  char charBuf[50];
  String(idx, BIN).toCharArray(charBuf, 50); 
  client.publish("webTopic", charBuf);
}

void reconnect() {
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266 Client")) {
      Serial.println("connected");
      // ... and subscribe to topic
      client.subscribe("thingyTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
 
void setup()
{
  Serial.begin(115200);
  // Print the IP address
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
 
  pinMode(LED_BUILTIN, OUTPUT);
}
 
void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
