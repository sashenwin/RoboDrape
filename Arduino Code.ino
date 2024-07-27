const int led = 13;
const int sensor_pin = A0;
int motorSpeedPin = 3;
int motorDirection1 = 4;
int motorDirection2 = 5;
int sensor;
const int threshold = 500;
unsigned long rotationStartTime = 0;
const int rotationDuration = 1300; // Rotation duration in milliseconds

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  pinMode(motorSpeedPin, OUTPUT);
  pinMode(motorDirection1, OUTPUT);
  pinMode(motorDirection2, OUTPUT);
}

void loop() {
  sensor = analogRead(sensor_pin);
  Serial.println(sensor);

  // Check if the rotation duration has elapsed
  if (millis() - rotationStartTime >= rotationDuration) {
    digitalWrite(led, LOW); // Turn off the LED
    digitalWrite(motorDirection1, LOW);
    digitalWrite(motorDirection2, LOW);
  } else {
    // Continue rotating in the current direction
    if (sensor < threshold) { // If sensor reading is less than threshold
      digitalWrite(led, HIGH);

      

      analogWrite(motorSpeedPin, 120);
      digitalWrite(motorDirection1, LOW);
      digitalWrite(motorDirection2, HIGH);
    } else { // If sensor reading is greater than threshold
      digitalWrite(led, HIGH);
analogWrite(motorSpeedPin, 140);
      digitalWrite(motorDirection1, HIGH);
      digitalWrite(motorDirection2, LOW);
      
    }
  }

  // Check for a change in the sensor state
  static int prevSensorState = HIGH;
  int currentSensorState = (sensor < threshold) ? LOW : HIGH;

  if (currentSensorState != prevSensorState) {
    // Change in sensor state, reset the rotation start time
    rotationStartTime = millis();
  }

  prevSensorState = currentSensorState;
}
