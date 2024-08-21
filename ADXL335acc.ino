const int xPin = A0; 
const int yPin = A1; 
const int zPin = A2; 

int stepCount = 0;
float lastMagnitude = 0;
const float stepThreshold = 0.2; // Adjust based on testing

void setup() {
  Serial.begin(9600);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(zPin, INPUT);
}

void loop() {
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  int zValue = analogRead(zPin);

  // Convert to G's (assuming 3.3V range and 10-bit ADC resolution)
  float x = (xValue - 512) * 3.3 / 512.0;
  float y = (yValue - 512) * 3.3 / 512.0;
  float z = (zValue - 512) * 3.3 / 512.0;

  float magnitude = sqrt(x*x + y*y + z*z);

  // Step detection logic: detect spikes in the magnitude 
  if (fabs(magnitude - lastMagnitude) > stepThreshold) {
    stepCount++;
    Serial.print("Steps: ");
    Serial.println(stepCount);
    delay(200); // delay for debounce
  }

  lastMagnitude = magnitude;
  delay(50);
}
