// Define pins for LEDs
const int redLED = 13;
const int greenLED = 11;
const int yellowLED = 12;

// Define pins for sensors
const int floatSensor = 4;
const int flowSensor = 2;

// Define pin for relay control
const int relayPin = 3;

// Define variables to track system state
bool doorLocked = false;
bool waterPresent = true; // Assuming water is present initially

void setup() {
  // Initialize pins
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(floatSensor, INPUT);
  pinMode(flowSensor, INPUT);
  pinMode(relayPin, OUTPUT);

  // Initial state: door unlocked, water present
  digitalWrite(relayPin, LOW); // Relay off initially
}

void loop() {
  // Check water level
  waterPresent = digitalRead(floatSensor);

  // Update LED indicators based on system state
  if (!waterPresent) {
    digitalWrite(yellowLED, HIGH);  // No water
  } else {
    digitalWrite(yellowLED, LOW);  // Water present
  }

  if (doorLocked) {
    digitalWrite(redLED, HIGH);  // Door locked
    digitalWrite(greenLED, LOW);
  } else {
    digitalWrite(redLED, LOW);  // Door unlocked
    digitalWrite(greenLED, HIGH);
  }

  // Check for flushing action
  if (digitalRead(flowSensor) == HIGH) {
    doorLocked = false; // If flushed, unlock the door
    digitalWrite(relayPin, LOW); // Activate relay to release electromagnet
    delay(1000); // Delay to ensure door unlocks properly
  }

  delay(1000); // Adjust delay as needed
}
