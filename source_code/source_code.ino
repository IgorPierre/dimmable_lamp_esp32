#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "Your network ssid";
const char* password = "Your network password";

// Create a WebServer object listening on port 80
WebServer server(80);

// Pin definitions
#define dimmer 5    // Pin chosen to control the dimmer (GPIO 5)
#define potPin 36   // Potentiometer read pin (GPIO 36 on ESP32)

// Variables for brightness control
volatile long lum = 128;  // Initial brightness value of 50% (0 to 255)
long lastPotValue = 0;    // To track the last potentiometer value

// Function to handle the root URL ("/")
void handleRoot() {
  String html = "<h1>Dimmable Light Control</h1>";
  html += "<p>Current brightness: " + String(lum) + "</p>";
  html += "<button onclick=\"location.href='/increase'\">Increase</button>";
  html += "<button onclick=\"location.href='/decrease'\">Decrease</button>";
  server.send(200, "text/html", html);
}

// Function to handle brightness increase
void handleIncrease() {
  long temp = lum + 25;  // Increase brightness by 25
  if (temp > 255) temp = 255;  // Ensure brightness does not exceed the maximum value
  lum = temp;
  analogWrite(dimmer, lum);  // Apply the new brightness value
  Serial.println("Brightness increased via web");
  handleRoot();  // Reload the webpage with updated brightness
}

// Function to handle brightness decrease
void handleDecrease() {
  long temp = lum - 25;  // Decrease brightness by 25
  if (temp < 0) temp = 0;  // Ensure brightness does not fall below the minimum value
  lum = temp;
  analogWrite(dimmer, lum);  // Apply the new brightness value
  Serial.println("Brightness decreased via web");
  handleRoot();  // Reload the webpage with updated brightness
}

// Setup function to initialize the ESP32
void setup() {
  Serial.begin(115200);  // Start serial communication at 115200 baud rate
  WiFi.begin(ssid, password);  // Connect to Wi-Fi network
  
  // Wait for the ESP32 to connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Print the connection details once connected
  Serial.println();
  Serial.println("Connected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());  // Print the IP address assigned to the ESP32

  // Define the routes for the web server
  server.on("/", handleRoot);
  server.on("/increase", handleIncrease);
  server.on("/decrease", handleDecrease);
  server.begin();  // Start the web server
  Serial.println("HTTP server started");

  // Configure the pins
  pinMode(dimmer, OUTPUT);
  pinMode(potPin, INPUT);
  digitalWrite(dimmer, LOW);  // Initialize the dimmer pin to low
}

// Main loop function to run continuously
void loop() {
  int potValue = analogRead(potPin);  // Read the potentiometer value (0 to 4095)

  // Update the brightness only if there's a significant change in potentiometer value
  if (abs(potValue - lastPotValue) > 10) {
    lum = map(potValue, 0, 4095, 0, 255);  // Scale the potentiometer value to match PWM range
    lastPotValue = potValue;  // Store the current potentiometer value
    analogWrite(dimmer, lum);  // Apply the new brightness value
  }

  // Print the potentiometer and brightness values to the serial monitor
  Serial.print("Potentiometer value: ");
  Serial.println(potValue);
  Serial.print("Adjusted brightness: ");
  Serial.println(lum);

  // Handle any incoming client requests to the web server
  server.handleClient();
  
  delay(100);  // Short delay to stabilize the loop
}
