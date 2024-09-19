#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Your network ssid";
const char* password = "Your network password";

WebServer server(80);

#define dimmer 5    // Pin chosen to control the dimmer (GPIO 5)
#define potPin 36   // Potentiometer read pin (GPIO 36 on ESP32)

volatile long lum = 128;  // Initial brightness value of 50% (0 to 255)
long lastPotValue = 0;

void handleRoot() {
  String html = "<h1>Dimmable Light Control</h1>";
  html += "<p>Current brightness: " + String(lum) + "</p>";
  html += "<button onclick=\"location.href='/increase'\">Increase</button>";
  html += "<button onclick=\"location.href='/decrease'\">Decrease</button>";
  server.send(200, "text/html", html);
}

void handleIncrease() {
  long temp = lum + 25;
  if (temp > 255) temp = 255;
  lum = temp;
  analogWrite(dimmer, lum);
  Serial.println("Brightness increased via web");
  handleRoot();
}

void handleDecrease() {
  long temp = lum - 25;
  if (temp < 0) temp = 0;
  lum = temp;
  analogWrite(dimmer, lum);
  Serial.println("Brightness decreased via web");
  handleRoot();
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/increase", handleIncrease);
  server.on("/decrease", handleDecrease);
  server.begin();
  Serial.println("HTTP server started");

  pinMode(dimmer, OUTPUT);
  pinMode(potPin, INPUT);
  digitalWrite(dimmer, LOW);
}

void loop() {
  int potValue = analogRead(potPin);

  if (abs(potValue - lastPotValue) > 10) {
    lum = map(potValue, 0, 4095, 0, 255);
    lastPotValue = potValue;
    analogWrite(dimmer, lum);
  }

  Serial.print("Potentiometer value: ");
  Serial.println(potValue);
  Serial.print("Adjusted brightness: ");
  Serial.println(lum);

  server.handleClient();
  
  delay(100);
}
