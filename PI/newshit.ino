#include <ESP8266WiFi.h>

const char WiFiAPPSK[] = "fuqallbiciz";

WiFiServer server(80);

int ALARM_PIN = 5;
String ssid = "";
String password = "";
int sts = 1;


String MyNetworkSSID = "Repeat of SSID here"; // SSID you want to connect to Same as SSID
bool Fl_MyNetwork = false; // Used to flag specific network has been found
bool Fl_NetworkUP = false; // Used to flag network connected and operational.


void setup() {
  Serial.begin(9600); 
  pinMode(ALARM_PIN, OUTPUT);
  //Scan_Wifi_Networks();
  //connect_wifi();
  setupWiFi();
  server.begin();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    delay(10);
    return;
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  String path = stringSplit(req, ' ', 1);
  String requestType = stringSplit(path, '/', 1);
  if (!"connect".equals(requestType)) {
    return;
  }
  ssid = stringSplit(path, '/', 2));
  password = stringSplit(path, '/', 3);
  if("".equals(ssid) || "".equals(password)) {
    return;
  }
  client.flush();

  // Prepare the response. Start with the common header:
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<br>"; // Go to the next line.
  s += "So you want to connect to " + ssid ;
  s += "</html>\n";
  client.print(s);
  delay(1000);
  Serial.println("Client disonnected");
}

void alarmBuzz(int t) {
  Serial.println(t);
  //digitalWrite(ALARM_PIN, LOW);
  //for(int i=0; i < t; i++) {
  //  digitalWrite(ALARM_PIN, HIGH);
  //  delay(10);
  //  digitalWrite(ALARM_PIN, LOW);
  //  delay(60);
  //}
  delay(100);
}

void Scan_Wifi_Networks()
{
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  // Need to be in dicsonected mode to Run network Scan!
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("Scaning Networks Complete..");
  Serial.print(n); Serial.println(" Networks have been Found");

  if (n == 0)
  {
    Serial.println("no networks found");
  }
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      if (MyNetworkSSID == WiFi.SSID(i))

      {
        Serial.print("My network has been Found! ");
        Fl_MyNetwork = true;
      }
      else
      {
        Serial.print("Not my network... ");
      }
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
}
void setupWiFi()
{
  WiFi.mode(WIFI_AP);

  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "ESP8266 Thing " + macID;
  Serial.println(AP_NameString);
  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);
}

void connect_wifi() {
  sts = 1;
  delay(10);
  WiFi.begin(ssid, password);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    alarmBuzz(++i);
    sts = 1;
  }
  sts = 4;
}

String stringSplit(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}