#include <Arduino.h>

// Define the pin numbers
#define LDR_PIN A3             // LDR sensor connected to analog pin A0
#define REED_SWITCH_PIN 2      // Reed Switch connected to digital pin 2
#define LDR_THRESHOLD 300

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
  Serial.println("Data format: LDR Value, Door Status");
}

// Function to print the light status based on LDR value
void checkLightStatus(int ldrValue) {
  if (ldrValue < LDR_THRESHOLD) {
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
  checkLightStatus(ldrValue);
  Serial.println(doorStatus);  // Display the door status
  Serial.print(", Door Status: ");
  



  // Wait for 30 minutes before taking another reading
  delay(1800000); // Delay in milliseconds
}
