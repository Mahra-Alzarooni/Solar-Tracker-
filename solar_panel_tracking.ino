
#include <Servo.h>

Servo solarServo;        // Create servo object to control the solar panel

int ldrLeft = A0;        // Left light sensor connected to analog pin A0
int ldrRight = A1;       // Right light sensor connected to analog pin A1
int pos = 90;            // Servo starts at center position (90 degrees)

void setup() {
  solarServo.attach(9);  // Attach servo on pin 9
  solarServo.write(pos); // Initialize servo position
  Serial.begin(9600);    // Start serial communication for debugging
}

void loop() {
  int leftValue = analogRead(ldrLeft);    // Read light intensity from left sensor
  int rightValue = analogRead(ldrRight);  // Read light intensity from right sensor
  int diff = leftValue - rightValue;      // Calculate difference between sensors

  // If difference is significant, adjust servo position
  if (abs(diff) > 50) {
    if (diff > 0 && pos < 180) {
      pos++;    // Rotate servo right if left sensor is brighter
    } else if (diff < 0 && pos > 0) {
      pos--;    // Rotate servo left if right sensor is brighter
    }
    solarServo.write(pos);  // Move servo to new position
    delay(15);              // Short delay for smooth movement
  }

  // Output sensor readings to serial monitor
  Serial.print("Left: ");
  Serial.print(leftValue);
  Serial.print(" | Right: ");
  Serial.println(rightValue);
}
