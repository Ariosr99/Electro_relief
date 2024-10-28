#include <Arduino.h>

// Pin Definitions
#define BUTTON_POWER  D1  // Middle button for power on/off and mode
#define BUTTON_UP     D2  // Button to increase frequency
#define BUTTON_DOWN   D3  // Button to decrease frequency

// Variables
bool powerOn = false;         // Device power status
bool tensMode = false;        // TENS mode status
int frequency = 0;            // TENS frequency (Hz)

// Constants
const int MAX_FREQUENCY = 100;  // Maximum frequency limit (in Hz)
const int MIN_FREQUENCY = 0;    // Minimum frequency limit (in Hz)

// Function to update TENS frequency
void updateFrequency() {
  // Code to adjust TENS pulse frequency based on 'frequency' variable
  Serial.print("Current Frequency: ");
  Serial.println(frequency);
}

// ISR functions for button presses
void handlePowerButton() {
  unsigned long pressTime = millis();
  delay(50); // Debounce delay
  
  if (digitalRead(BUTTON_POWER) == LOW) {
    if (millis() - pressTime > 1000) {  // Long press for power on/off
      powerOn = !powerOn;
      tensMode = false;
      Serial.println(powerOn ? "Power ON" : "Power OFF");
    } else {  // Short press for toggling TENS mode
      if (powerOn) {
        tensMode = !tensMode;
        Serial.println(tensMode ? "TENS Mode Activated" : "TENS Mode Deactivated");
      }
    }
  }
}

void handleUpButton() {
  if (powerOn && tensMode && frequency < MAX_FREQUENCY) {
    frequency++;
    updateFrequency();
  }
}

void handleDownButton() {
  if (powerOn && tensMode && frequency > MIN_FREQUENCY) {
    frequency--;
    updateFrequency();
  }
}

void setup() {
  Serial.begin(115200);
  
  // Initialize button pins as inputs with pullup
  pinMode(BUTTON_POWER, INPUT_PULLUP);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);

  // Attach interrupt functions
  attachInterrupt(digitalPinToInterrupt(BUTTON_POWER), handlePowerButton, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_UP), handleUpButton, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_DOWN), handleDownButton, FALLING);
}

void loop() {
  // Additional code for signal generation if required
}
