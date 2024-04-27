// Define pins
const int flowSensorPin = 2;    // Water flow sensor connected to digital pin 2
const int switchPin = 8;        // SPST switch connected to digital pin 8
const int waterSensorPin = 4;   // Water float sensor connected to digital pin 4
const int redLedPin = 13;       // Red LED connected to digital pin 13
const int greenLedPin = 11;     // Green LED connected to digital pin 11
const int yellowLedPin = 12;    // Yellow LED connected to digital pin 12
const int relayPin = 3;         // Relay connected to digital pin 3

// Variables
volatile int flowPulseCount = 0;
bool relayActivated = false;   // Flag to track if relay is activated
bool doorLocked = false;       // Flag to track if the door is locked
bool waterDetected = false;    // Flag to track if water is detected

// Setup
void setup() {
  pinMode(flowSensorPin, INPUT);
  pinMode(switchPin, INPUT_PULLUP);       // Enable internal pull-up resistor for the switch
  pinMode(waterSensorPin, INPUT_PULLUP); // Set the water sensor pin as an input with internal pull-up resistor enabled
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), countFlow, RISING);
  Serial.begin(9600);
}

// Main loop
void loop() {
  // Read the state of the switch
  int switchState = digitalRead(switchPin);
  // Read the state of the water float sensor
  int waterLevel = digitalRead(waterSensorPin);

  // Update door lock status based on switch state
  if (switchState == LOW) {
    doorLocked = true;
  } else {
    doorLocked = false;
  }

  // Update water detection status
  if (waterLevel == LOW) {
    waterDetected = true;
  } else {
    waterDetected = false;
  }

  // Control LEDs and electromagnet based on conditions
  if (doorLocked) {
    digitalWrite(redLedPin, HIGH); // Turn on red LED
    digitalWrite(greenLedPin, LOW); // Turn off green LED
    if (waterDetected || flowPulseCount > 0) {
      digitalWrite(yellowLedPin, LOW); // Turn off yellow LED
      if (!relayActivated) {
        digitalWrite(relayPin, HIGH); // Turn on relay
        delay(1000); // Delay to ensure the door has time to unlock
        relayActivated = true;
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
  Serial.print("Flow Pulse Count: ");
  Serial.println(flowPulseCount);
  // Reset flow pulse count after processing
  flowPulseCount = 0;
  delay(1000); // Delay for stability
}

// Interrupt service routine
void countFlow() {
  flowPulseCount++;
}
