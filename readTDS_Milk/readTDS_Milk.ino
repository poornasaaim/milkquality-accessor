#include <Arduino.h>
#include "GravityTDS.h"


GravityTDS gravityTds;

const int tdsSensorPin = A0;
//const int temperatureSensorPin = A2; 
const float tdsCalibrationFactor = 0.5; // Calibration factor for TDS sensor

float tdsValue = 0, conductivity = 0, impedance = 0, fatContent = 0;

void setup()
{
    Serial.begin(115200);
    
    gravityTds.setPin(tdsSensorPin);
    gravityTds.setAref(5.0);  // Reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  // 1024 for 10-bit ADC; 4096 for 12-bit ADC
    gravityTds.begin();  // Initialization
}

void loop()
{
//     int rawTemperatureValue = analogRead(temperatureSensorPin);
//    int temperature = map(rawTemperatureValue, 0, 1023, 0, 100); // Example conversion, adjust as needed
    int temperature = 25;
    gravityTds.setTemperature(temperature);  // Set the temperature and execute temperature compensation
    gravityTds.update();  // Sample and calculate
    tdsValue = gravityTds.getTdsValue();  // Get the TDS value in ppm

    // Convert TDS ppm to an approximate fat content estimation
    // This is a makeshift conversion and may not be accurate
    fatContent = map(tdsValue, 0, 2000, 0, 100); // Example conversion, adjust as needed

    // Read the analog value from the TDS sensor
    int rawValue = analogRead(tdsSensorPin);

    // Convert the raw value to TDS using a calibration factor
    tdsValue = rawValue * tdsCalibrationFactor;

    // Calculate electrical conductivity (assuming linear relationship)
    // You may need to adjust the constants based on your sensor's characteristics
    conductivity = tdsValue * 0.1; // Example scaling factor

    // Calculate electrical impedance by taking the reciprocal of conductivity
    impedance = 1.0 / conductivity;

    Serial.print("TDS (ppm): ");
    Serial.print(tdsValue, 0);
    Serial.print(", Estimated Fat Content (%): ");
    Serial.println(fatContent / 10, 2); // Print with 2 decimal places
    Serial.print("Conductivity: ");
    Serial.print(conductivity);
    Serial.print(" uS/cm"); // Microsiemens per centimeter
    Serial.print("\tImpedance: ");
    Serial.print(impedance);
    Serial.println(" ohms");

    delay(1000);  // Delay for one second before the next reading
}
