#include <Arduino.h>
#include <Preferences.h>

#define PIN_18 18
#define PIN_19 19

Preferences preferences;

void setup() {
  // Initialize the serial monitor for debugging
  // Serial.begin(115200);

  // Initialize the pins as output
  pinMode(PIN_18, OUTPUT);
  pinMode(PIN_19, OUTPUT);
  pinMode(22,OUTPUT); //led
  digitalWrite(22, LOW);

  // Open Preferences with my-app namespace. Namespace is used to avoid conflicts with other programs.
  preferences.begin("power_count", false);

  // Read the stored power-on count, default is 0 if no value is stored.
  int powerOnCount = preferences.getInt("count", 0);

  // Increment the power-on count and save it back
  powerOnCount++;
  preferences.putInt("count", powerOnCount);

  // Print the power-on count for debugging
  // Serial.print("Power-on Count: ");
  // Serial.println(powerOnCount);

  // Check if the power-on count is odd or even
  if (powerOnCount % 2 == 1) {
    // Odd power-on count
    digitalWrite(PIN_18, HIGH);  // Turn ON pin 18
     digitalWrite(22, HIGH);  // Turn ON pin 18
    digitalWrite(PIN_19, LOW);   // Turn OFF pin 19
    // Serial.println("Odd power-on: Pin 18 ON, Pin 19 OFF");
  } else {
    // Even power-on count
    digitalWrite(PIN_18, LOW);   // Turn OFF pin 18
     digitalWrite(22, LOW);  // Turn ON pin 18
    digitalWrite(PIN_19, HIGH);  // Turn ON pin 19
    // Serial.println("Even power-on: Pin 18 OFF, Pin 19 ON");
  }

  // Close the preferences to free up resources
  preferences.end();
}

void loop() {
  // No need for loop logic in this case
}
