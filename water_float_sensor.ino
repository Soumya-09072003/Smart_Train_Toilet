#define WATER_SENSOR_PIN 4 // Define the pin connected to the water float sensor
#define LED_PIN 12 // Define the pin connected to the LED

void setup() {
  pinMode(WATER_SENSOR_PIN, INPUT_PULLUP); // Set the water sensor pin as an input with internal pull-up resistor enabled
  pinMode(LED_PIN, OUTPUT); // Set the LED pin as an output
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  int waterLevel = digitalRead(WATER_SENSOR_PIN); // Read the state of the water float sensor
  
  if (waterLevel == LOW) {
    Serial.println("Water detected!"); // Print a message when water is detected
    digitalWrite(LED_PIN, HIGH); // Turn on the LED
  } else {
    Serial.println("No water detected."); // Print a message when no water is detected
    digitalWrite(LED_PIN, LOW); // Turn off the LED
  }
  
  delay(1000); // Delay for stability
}
