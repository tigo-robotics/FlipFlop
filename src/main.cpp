/***
 * This car gate entry system is a hack to its existing remote controller interface, 
 * by book keeping a elapsed time (total time), at every frame the time is written to 
 * the prefrences. and if it did not complete, 
 */

#include <Arduino.h>
#include <Preferences.h>
#define PIN_17 17 // stop
#define PIN_18 18 // down 
#define PIN_19 19 // up

Preferences preferences;


void allOff()
{
  digitalWrite(PIN_17, HIGH);
  digitalWrite(PIN_18, HIGH);
  digitalWrite(PIN_19, HIGH);
  digitalWrite(22, HIGH);
  for(int i=0;i<30;i++){
    delay(10);
    digitalWrite(22, LOW);
    delay(10);
    digitalWrite(22, HIGH);
  }
}
void setup()
{
  // Initialize the serial monitor for debugging
  // Serial.begin(115200);

  // Initialize the pins as output
  pinMode(PIN_17, OUTPUT);
  pinMode(PIN_18, OUTPUT);
  pinMode(PIN_19, OUTPUT);
  pinMode(22, OUTPUT); // led
  digitalWrite(PIN_17, HIGH);
  digitalWrite(PIN_18, HIGH);
  digitalWrite(PIN_19, HIGH);
  digitalWrite(22, HIGH); //LED  off
  
  // Open Preferences with my-app namespace. Namespace is used to avoid conflicts with other programs.
  preferences.begin("power_count", false); //this is namespace

  // Read the stored power-on count, default is 0 if no value is stored.
  int powerOnCount = preferences.getInt("count", 0);

  // Increment the power-on count and save it back
  powerOnCount++;
  preferences.putInt("count", powerOnCount);

  // Check if the power-on count is odd or even
  if (powerOnCount % 4 == 1) //open gate
  {
    digitalWrite(PIN_19, LOW);  
    digitalWrite(PIN_18, HIGH); 
    digitalWrite(PIN_17, HIGH); 
    digitalWrite(22, LOW);     // Turn ON  LED on
  }
  else if (powerOnCount % 4 == 2 || powerOnCount % 4 == 0) // stop
  {
    // Even power-on count
    digitalWrite(PIN_18, HIGH);  // Turn OFF pin 18
    digitalWrite(PIN_19, HIGH); // Turn ON pin 19
    digitalWrite(PIN_17, LOW); 
    digitalWrite(22, HIGH);      // Turn LED on
    // Serial.println("Even power-on: Pin 18 OFF, Pin 19 ON");
  }
  else if (powerOnCount % 4 == 3) // Down
  {
    digitalWrite(PIN_19, HIGH);  
    digitalWrite(PIN_18, LOW); 
    digitalWrite(PIN_17, HIGH); 
    digitalWrite(22, LOW);
  }
  delay(100);
  allOff();
  // Close the preferences to free up resources
  preferences.end();
}

void loop()
{
  // No need for loop logic in this case
}

