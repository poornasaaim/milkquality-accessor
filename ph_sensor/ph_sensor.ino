#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial pHSerial(5, 6); // RX, TX
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address, LCD dimensions (16x2)

const int numReadings = 10; // Number of readings to average
float pHReadings[numReadings]; // Array to store pH readings
int pHIndex = 0; // Index for the pH readings array
float pHSum = 0.0; // Sum of pH readings

void setup() {
  Serial.begin(9600); // Serial monitor for debugging
  pHSerial.begin(9600); // Initialize the software serial communication with pH sensor
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  lcd.clear(); // Clear the LCD screen
  lcd.setCursor(0, 0);
  lcd.print("Average pH:");
}

void loop() {
  if (pHSerial.available()) {
    char data = pHSerial.read();

    // Check if the received character is a digit or a decimal point
    if (isdigit(data) || data == '.') {
      Serial.print(data); // Print the character to the serial monitor
      lcd.setCursor(0, 1); // Set the cursor to the second line
      lcd.print("pH: "); // Display "pH: "
      lcd.print(data); // Display the character on the LCD

      // Convert the character to a float and store it in the array
      float pHValue = atof(&data);
      pHSum += pHValue - pHReadings[pHIndex]; // Update the sum with new value and remove old value
      pHReadings[pHIndex] = pHValue; // Store the new value in the array
      pHIndex = (pHIndex + 1) % numReadings; // Increment index with wrap-around

      // Calculate and display the average pH value
      float averagepH = pHSum / numReadings;
      lcd.setCursor(10, 1); // Set the cursor to the second line, 10th position
      lcd.print(averagepH, 2); // Display the average pH with 2 decimal places
    }
  }
}
