#include <Arduino.h>

// Define the pin numbers
#define LDR_PIN A3             // LDR sensor connected to analog pin A0
#define REED_SWITCH_PIN 2      // Reed Switch connected to digital pin 2

// Set the threshold for LDR to determine if the lights are on or off
#define LDR_THRESHOLD 500      // Light threshold for considering the light as "on"

// Variables to hold sensor readings
int ldrValue = 0;
int reedSwitchState = 0;

// Setup the pins and Serial Communication
void setup() {
  // Initialize Serial Communication for debugging and sending data to computer
  Serial.begin(9600);         // Start serial communication at 9600 baud rate
  while (!Serial);            // Wait for Serial Monitor to open (necessary for some boards)

  // Initialize reed switch pin
  pinMode(REED_SWITCH_PIN, INPUT_PULLUP); // Set reed switch pin as input with pull-up resistor
  
  // Display initial message
  Serial.println("Arduino Sensor Data Logging Started...");
  Serial.println("Threshold for LDR: 500");
  Serial.println("Data format: LDR Value, Door Status");
}

// Function to print the light status based on LDR value
void checkLightStatus(int ldrValue) {
  if (ldrValue < 300) {
    Serial.println("Shut off");
  } else {
    Serial.println("Turned on");
  }
}

// Main loop to read sensor data and send it to the serial monitor
void loop() {
  // Read the LDR value (Light Level)
  ldrValue = analogRead(LDR_PIN); // Read analog value from LDR

  // Read the Reed Switch state (door open/close)
  reedSwitchState = digitalRead(REED_SWITCH_PIN);  // HIGH if door is closed, LOW if door is open

  // Convert reed switch state to a human-readable format
  String doorStatus = (reedSwitchState == HIGH) ? "Closed" : "Open";

  // Print the data to Serial Monitor
  Serial.print("LDR Value: ");
  Serial.print(ldrValue);  // Display the LDR value
  Serial.print(", Door Status: ");
  Serial.println(doorStatus);  // Display the door status

  // Check the light status based on LDR value
  checkLightStatus(ldrValue);

  // Wait for 1 second before taking another reading
  delay(1000); // Delay in milliseconds
}
