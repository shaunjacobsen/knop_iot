#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "config.h"

int RED_LED = 5;   // D1 pin
int GREEN_LED = 4; // D2 pin
int WHITE_LED = 2; // D4 pin
int BUTTON = 14;   // D5 pin

void fetch()
{
  // turn on white LED
  digitalWrite(WHITE_LED, HIGH);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Explicitly set the ESP8266 to be a WiFi-client
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(WHITE_LED, HIGH);
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  HTTPClient http;

  // Make POST request when connected
  if (WiFi.status() == WL_CONNECTED)
  {

    String request_string = (String)url + "/event?type=button_push&device_id=" + device_id;

    Serial.println("request string:");
    Serial.println(request_string);

    http.begin(request_string);
    http.addHeader("Content-Type", "text/plain");
    int httpCode = http.POST("");

    Serial.println("Response code:");
    Serial.println(httpCode);

    if (httpCode > 0 && httpCode <= 200)
    {
      String payload = http.getString();
      Serial.println("Request success!");
      Serial.println(payload);
      // turn off white LED
      digitalWrite(WHITE_LED, LOW);
      // turn on green LED and blink
      digitalWrite(GREEN_LED, HIGH);
      delay(200);
      digitalWrite(GREEN_LED, LOW);
      delay(200);
      digitalWrite(GREEN_LED, HIGH);
      delay(200);
      digitalWrite(GREEN_LED, LOW);
      delay(200);
      digitalWrite(GREEN_LED, HIGH);
      delay(200);
      digitalWrite(GREEN_LED, LOW);
      delay(200);
      digitalWrite(GREEN_LED, HIGH);
      delay(750);
      digitalWrite(GREEN_LED, LOW);
    }
    else if (httpCode > 200 && httpCode <= 500)
    {
      // HTTP error
      Serial.println("Error with request!");
      // turn off white LED
      digitalWrite(WHITE_LED, LOW);
      // turn on red LED and blink
      digitalWrite(RED_LED, HIGH);
      delay(500);
      digitalWrite(RED_LED, LOW);
      delay(500);
      digitalWrite(RED_LED, HIGH);
      delay(500);
      digitalWrite(RED_LED, LOW);
      delay(500);
      digitalWrite(RED_LED, HIGH);
      delay(500);
    }
    else
    {
      // system error
      Serial.println("Error sending request!");
      // turn off white LED
      digitalWrite(WHITE_LED, LOW);
      // turn on red LED
      digitalWrite(RED_LED, HIGH);
      delay(3000);
    }
  }

  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  http.end();
  // turn off the LEDs
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(WHITE_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

void setup()
{
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(WHITE_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

void loop()
{
  Serial.println("Looping");
  if (digitalRead(BUTTON) == HIGH)
  {
    Serial.println("Button pressed!");
    fetch();
  }

  if (digitalRead(BUTTON) == LOW)
  {
    Serial.println("Button not pressed");
    delay(200);
  }
}
