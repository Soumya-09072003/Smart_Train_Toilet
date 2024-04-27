// Define pins
const int flowSensorPin = 2;   // Water flow sensor connected to digital pin 2
const int switchPin = 8;       // SPST switch connected to digital pin 3
const int waterSensorPin = 4;  // Water float sensor connected to digital pin 4
const int redLedPin = 13;       // Red LED connected to digital pin 5
const int greenLedPin = 11;     // Green LED connected to digital pin 6
const int yellowLedPin = 12;    // Yellow LED connected to digital pin 7
const int relayPin = 3;        // Relay connected to digital pin 8

// Variables
volatile int flowPulseCount = 0;
bool relayActivated = false;   // Flag to track if relay is activated
bool doorLocked = false;       // Flag to track if the door is locked
bool waterDetected = false;    // Flag to track if water is detected
bool waterDetectedFlush = false;    // Flag to track if water is detected in flush
// Setup
void setup() {
  pinMode(switchPin, INPUT_PULLUP); // Enable internal pull-up resistor for the switch
  pinMode(waterSensorPin, INPUT_PULLUP); // Set the water sensor pin as an input with internal pull-up resistor enabled
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(flowSensorPin, INPUT_PULLUP); // Set the water sensor pin as an input with internal pull-up resistor enabled
  pinMode(relayPin, OUTPUT); // Set the relay pin as an output
  digitalWrite(relayPin, LOW); // Ensure the relay is initially turned off
  Serial.begin(9600); // Initialize serial communication
}

// Main loop
void loop() {
  // Read the state of the switch
  int switchState = digitalRead(switchPin);
  // Read the state of the water float sensor
  int waterLevel = digitalRead(waterSensorPin);
  // Read the state of the water float sensor in flush
  int waterLevelFlush = digitalRead(flowSensorPin);
  // Update door lock status based on switch state
  if (switchState == LOW) {
    doorLocked = true;
  } else {
    doorLocked = false;
  }

  // Update water detection status
  if (waterLevel == HIGH) {
    waterDetected = true;
  } else {
    waterDetected = false;
  }
 
 // Update water detection status in flush
  if (waterLevelFlush == LOW) {
    waterDetectedFlush = true;
  } else {
    waterDetectedFlush = false;
  }

  // Control LEDs and electromagnet based on conditions
  if (doorLocked) {
    digitalWrite(redLedPin, HIGH); // Turn on red LED
    digitalWrite(greenLedPin, LOW); // Turn off green LED
    if (waterDetected) {
      digitalWrite(yellowLedPin, LOW); // Turn off yellow LED
      if (!relayActivated) {
        digitalWrite(relayPin, HIGH); // Turn on relay
        relayActivated = true;
        if (waterDetectedFlush) {
        digitalWrite(relayPin,HIGH);
        }
        else{
          digitalWrite(relayPin,LOW);
        }
      }
    } else {
      digitalWrite(yellowLedPin, HIGH); // Turn on yellow LED
      digitalWrite(relayPin, LOW); // Turn off relay
      relayActivated = false;
    }
  } else {
    digitalWrite(redLedPin, LOW); // Turn off red LED
    digitalWrite(greenLedPin, HIGH); // Turn on green LED
    digitalWrite(yellowLedPin, LOW); // Turn off yellow LED
    digitalWrite(relayPin, LOW); // Turn off relay
    relayActivated = false;
  }

  // Print status to serial monitor for debugging
  Serial.print("Door Locked: ");
  Serial.println(doorLocked);
  Serial.print("Water Detected: ");
  Serial.println(waterDetected);
  delay(1000); // Delay for stability
}

// Interrupt service routine
void countFlow() {
  flowPulseCount++;
}
