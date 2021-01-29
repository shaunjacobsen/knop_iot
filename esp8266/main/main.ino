#include <ESP8266WiFi.h>
#include "config.h"

int RED_LED = 5; // D1
int GREEN_LED = 4; // D2
int WHITE_LED = 2; // D4
int BUTTON = 14; // D5

const char* device_id = "abc123";

// no protocol here, assuming HTTP
const char* host = "3.64.101.15";
const uint16_t port = 3005;

void fetch() {
  // turn on white LED
  digitalWrite(WHITE_LED, HIGH);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Explicitly set the ESP8266 to be a WiFi-client
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    // turn off white LED
    digitalWrite(WHITE_LED, LOW);
    // turn on red LED
    digitalWrite(RED_LED, HIGH);
    // keep it on for 3 seconds
    delay(3000);
    // turn off red LED
    digitalWrite(RED_LED, LOW);
  }
  
  // Make GET Request with Headers (CloudFront requires this)
  if (client.connected() ) {
     client.println((String)"GET /hello?device_id=" + device_id + " HTTP/1.0");
     client.println((String)"Host: " + host);
     client.println("Connection: keep-alive");
     client.println("Cache-Control: max-age=0");
     client.println("User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko)");
     client.println("Accept-Language: en-US,en;q=0.9"); 
     client.println(); 
  }

  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 20000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(5000);
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  // turn off white LED
  digitalWrite(WHITE_LED, LOW);
  // turn on green LED
  digitalWrite(GREEN_LED, HIGH);
  delay(200);
  digitalWrite(GREEN_LED, LOW);
  delay(200);
  digitalWrite(GREEN_LED, HIGH);
  delay(200);
  digitalWrite(GREEN_LED, LOW);
  
  // not testing 'client.connected()' since we do not need to send data here
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
    delay(10);
  }

  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();
  // turn off the LEDs
  digitalWrite(GREEN_LED, LOW);

  // Wait 1 second and then initiate Deep Sleep to conserve battery
//  delay(1000);
//  ESP.deepSleep(0);
}

void setup() {
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(WHITE_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

void loop() {
  Serial.println("Looping");
  if (digitalRead(BUTTON) == HIGH) {
    Serial.println("Button pressed!");
    fetch();
  }

  if (digitalRead(BUTTON) == LOW) {
    Serial.println("Button not pressed");
    delay(200);
  }
 }
