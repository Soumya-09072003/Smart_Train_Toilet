// Define pins
const int switchPin = 8;        // SPST switch connected to digital pin 2
const int waterSensorPinFlush = 2;   // Water float sensor for flushing connected to digital pin 4
const int waterSensorPinTank = 4;    // Water float sensor for tank connected to digital pin 5
const int redLedPin = 13;        // Red LED connected to digital pin 6
const int greenLedPin = 11;      // Green LED connected to digital pin 7
const int yellowLedPin = 12;     // Yellow LED connected to digital pin 8
const int relayPin = 3;         // Relay connected to digital pin 9

// Variables
bool doorLocked = false;           // Flag to track if the door is locked
bool waterDetectedFlush = false;   // Flag to track if water is detected for flushing
bool waterDetectedTank = false;    // Flag to track if water is detected in the tank

// Setup
void setup() {
  pinMode(switchPin, INPUT_PULLUP); // Enable internal pull-up resistor for the switch
  pinMode(waterSensorPinFlush, INPUT_PULLUP); // Set the water sensor pin for flushing as input with internal pull-up resistor enabled
  pinMode(waterSensorPinTank, INPUT_PULLUP);  // Set the water sensor pin for tank as input with internal pull-up resistor enabled
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, HIGH); // Ensure the relay is initially turned off
  Serial.begin(9600); // Initialize serial communication
}

// Main loop
void loop() {
  // Read the state of the switch
  int switchState = digitalRead(switchPin);
  // Read the state of the water float sensor for flushing
  int waterLevelFlush = digitalRead(waterSensorPinFlush);
  // Read the state of the water float sensor for tank
  int waterLevelTank = digitalRead(waterSensorPinTank);

  // Update door lock status based on switch state
  if (switchState == LOW) {
    doorLocked = true;
  } else {
    doorLocked = false;
  }

  // Update water detection status for flushing
  if (waterLevelFlush == LOW) {
    waterDetectedFlush = true;
  } else {
    waterDetectedFlush = false;
  }

  // Update water detection status for tank
  if (waterLevelTank == LOW) {
    waterDetectedTank = true;
  } else {
    waterDetectedTank = false;
  }

  // Control LEDs and electromagnet based on conditions
  if (doorLocked) {
    digitalWrite(redLedPin, HIGH); // Turn on red LED
    digitalWrite(greenLedPin, LOW); // Turn off green LED
    if (waterDetectedFlush) {
      digitalWrite(yellowLedPin, LOW); // Turn off yellow LED
      if (waterDetectedTank) {
        digitalWrite(relayPin, LOW); // Turn on relay (door locked)
        Serial.println("Door closed - Water detected in tank");
      } else {
        digitalWrite(relayPin, HIGH); // Turn off relay (door unlocked)
        Serial.println("Door open - No water detected in tank");
      }
    } else {
      digitalWrite(yellowLedPin, HIGH); // Turn on yellow LED
      digitalWrite(relayPin, LOW); // Turn on relay (door locked)
      Serial.println("Door closed - No water detected for flushing");
    }
  } else {
    digitalWrite(redLedPin, LOW); // Turn off red LED
    digitalWrite(greenLedPin, HIGH); // Turn on green LED
    digitalWrite(yellowLedPin, LOW); // Turn off yellow LED
    digitalWrite(relayPin, HIGH); // Turn off relay (door unlocked)
    Serial.println("Door open - Unlocked");
  }

  delay(1000); // Delay for stability
}
