#include <SPI.h>
#include <WiFiNINA.h>

// Define the pin numbers
#define LDR_PIN A0             // LDR sensor connected to analog pin A0
#define REED_SWITCH_PIN 2      // Reed Switch connected to digital pin 2

// Set the threshold for LDR to determine if the lights are on or off
#define LDR_THRESHOLD 300      // Light threshold for considering the light as "on"

// WiFi credentials
const char* ssid = "your_SSID";          // Wi-Fi SSID
const char* password = "your_PASSWORD";  // Wi-Fi password

// WiFi client object
WiFiClient client;

// IP address of your computer on the local network
const char* serverIP = "192.168.x.x";  // Replace with your computer's local IP
const int port = 3000;                 // Port number (should match the server's port)

// Variables for sensor data
int ldrValue = 0;
int reedSwitchState = 0;

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  
  // Initialize Wi-Fi connection
  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    delay(1000);
  }
  
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  // Initialize reed switch pin
  pinMode(REED_SWITCH_PIN, INPUT_PULLUP); // Set reed switch pin as input with pull-up resistor
  
  // Display initial message
  Serial.println("Arduino Sensor Data Logging Started...");
}

void loop() {
  // Read the LDR value (Light Level)
  ldrValue = analogRead(LDR_PIN); // Read analog value from LDR

  // Read the Reed Switch state (door open/close)
  reedSwitchState = digitalRead(REED_SWITCH_PIN);  // HIGH if door is closed, LOW if door is open

  // Convert reed switch state to a human-readable format
  String doorStatus = (reedSwitchState == HIGH) ? "closed" : "open";
 
  String lightStatus;

  if (ldrValue < LDR_THRESHOLD) {
    lightStatus = "off";
  } else {
    lightStatus = "on";
  }
  // Print the LDR value, door status, and light status to the Serial Monitor for debugging
  Serial.print("LDR Value: ");
  checkLightStatus(ldrValue);  // Check and print the light status
  Serial.print("Door Status: ");
  Serial.print(doorStatus);  // Display the door status
 

  // Send the data over Wi-Fi to the local server
  sendDataToServer(lightStatus, doorStatus);

  // Wait for 5 seconds before sending the next data
  delay(5000);
}

// Function to send data to the server via HTTP POST
void sendDataToServer(String lightStatus, String doorStatus) {
  if (client.connect(serverIP, port)) {  // Connect to the server (your computer)
    Serial.println("Connected to server");

    // Construct the HTTP POST request
    client.println("POST /submit_data HTTP/1.1");  // Match the server endpoint
    client.println("Host: " + String(serverIP));  // Set the host (your computer IP)
    client.println("Content-Type: application/x-www-form-urlencoded");  // Form data type
    client.print("Content-Length: ");
    client.println(String("lightStatus=" + lightStatus + "&doorStatus=" + doorStatus).length());
    client.println();  // Blank line to end headers

    // Send the POST data (URL-encoded format)
    client.print("lightStatus=" + lightStatus + "&doorStatus=" + doorStatus);

    // Wait for the server's response
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);  // Print the server response to the Serial Monitor
    }

    Serial.println("\nData sent to server successfully!");
  } else {
    Serial.println("Connection to server failed.");
  }

  client.stop();  // Close the connection
}


