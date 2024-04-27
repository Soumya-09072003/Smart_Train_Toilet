// Define pins
const int flowSensorPin = 2;   // Water float sensor connected to digital pin 2
const int relayPin = 3;         // Relay connected to digital pin 3

// Variables
bool waterDetectedFlush = false;    // Flag to track if water is detected

// Setup
void setup() {
  pinMode(flowSensorPin, INPUT_PULLUP); // Set the water sensor pin as an input with internal pull-up resistor enabled
  pinMode(relayPin, OUTPUT); // Set the relay pin as an output
  digitalWrite(relayPin, LOW); // Ensure the relay is initially turned off
  Serial.begin(9600); // Initialize serial communication
}

// Main loop
void loop() {
  // Read the state of the water float sensor
  int waterLevelFlush = digitalRead(flowSensorPin);

  // Update water detection status
  if (waterLevelFlush == LOW) {
    waterDetectedFlush = true;
  } else {
    waterDetectedFlush = false;
  }

  // Control electromagnet (relay) based on water detection status
  if (waterDetectedFLush) {
    // Lock the door (activate the electromagnet) if water is detected
    digitalWrite(relayPin, HIGH); // Turn on the relay to activate the electromagnet
    Serial.println("Door locked - Water detected");
  } else {
    // Unlock the door (deactivate the electromagnet) if no water is detected
    digitalWrite(relayPin, LOW); // Turn off the relay to deactivate the electromagnet
    Serial.println("Door unlocked - No water detected");
  }

  delay(1000); // Delay for stability
}
