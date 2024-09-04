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
#define TOTAL_TIME 6000
Preferences preferences;
long current_time = 0;
long startTime = 0;

void allOff()
{
  digitalWrite(PIN_17, LOW);
  digitalWrite(PIN_18, LOW);
  digitalWrite(PIN_19, LOW);
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
  digitalWrite(PIN_17, HIGH); //pause whenever started.
  digitalWrite(PIN_18, LOW);
  digitalWrite(PIN_19, LOW);
  pinMode(22, OUTPUT); // led
  digitalWrite(22, LOW); //LED  on
  delay(100);
   digitalWrite(PIN_17, LOW);
  startTime = millis();
  // Open Preferences with my-app namespace. Namespace is used to avoid conflicts with other programs.
  preferences.begin("power_count", false); //this is namespace

  // Read the stored power-on count, default is 0 if no value is stored.
  int powerOnCount = preferences.getInt("count", 0);

  // Increment the power-on count and save it back
  powerOnCount++;
  preferences.putInt("count", powerOnCount);
  bool prev_completed = preferences.getBool("prev_comp",true);
  long prev_time = preferences.getLong("prev_time",0);
  // Print the power-on count for debugging
  // Serial.print("Power-on Count: ");
  // Serial.println(powerOnCount);

  // Check if the power-on count is odd or even
  if (powerOnCount % 2 == 1) // raise
  {
    // Odd power-on count
    digitalWrite(PIN_18, HIGH); // Turn ON pin 18
    digitalWrite(22, HIGH);     // Turn ON  LED off
    digitalWrite(PIN_19, LOW);  // Turn OFF pin 19

    // Serial.println("Odd power-on: Pin 18 ON, Pin 19 OFF");
  }
  else
  {
    // Even power-on count
    digitalWrite(PIN_18, LOW);  // Turn OFF pin 18
    digitalWrite(22, LOW);      // Turn LED on
    digitalWrite(PIN_19, HIGH); // Turn ON pin 19
    // Serial.println("Even power-on: Pin 18 OFF, Pin 19 ON");
  }
  //start tracking completion
  preferences.putBool("prev_comp", false);
  // public
  if(prev_completed){ //if prev completed, then travel entire total time
    current_time = millis() - startTime;
    while(current_time < TOTAL_TIME){
      preferences.putLong("prev_time",current_time);
      current_time = millis() - startTime;
      delay(10);
    }
  }else{//if prev did not complete, arm can go total - prev time
    current_time = millis() - startTime;
    while(current_time < TOTAL_TIME - prev_time){
      preferences.putLong("prev_time",current_time);
      current_time = millis() - startTime;
      delay(10);
    }
  }
  //ending stop
  digitalWrite(PIN_17, HIGH);
  delay(100);
  allOff();
  preferences.putBool("prev_comp", true);

  // Close the preferences to free up resources
  preferences.end();
}

void loop()
{
  // No need for loop logic in this case
}

