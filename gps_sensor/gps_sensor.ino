#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Create a SoftwareSerial object for the GPS module
SoftwareSerial gpsSerial(0, 1); // RX, TX

// Create a TinyGPS++ object
TinyGPSPlus gps;

void setup() {
  // Start the serial communication with the GPS module
  gpsSerial.begin(9600);

  // Start the serial communication with the computer
  Serial.begin(9600);
}

void loop() {
  // Read data from the GPS module and update the TinyGPS++ object
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  // Display GPS data if a fix is available
  if (gps.location.isValid()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
  } else {
    Serial.println("Waiting for GPS fix...");
  }

  // Delay between readings
  delay(1000); // Adjust the delay time as needed
}
