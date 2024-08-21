#include <Adafruit_BMP085.h>

#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600);
  
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
}

void loop() {
  // Read temperature in degrees Celsius
  float temperature = bmp.readTemperature();
  
  // Read pressure in hPa (hectopascals)
  float pressure = bmp.readPressure() / 100.0; // Convert to hPa
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");
  
  delay(1000); // Wait for a second before taking another reading
}
