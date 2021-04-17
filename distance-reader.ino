#include <LiquidCrystal.h>

// Define pins
#define echoPin 2
#define trigPin 4
#define redLightPin 3
#define blueLightPin 5
#define greenLightPin 6

long duration; // Travel time in microseconds
double distanceInCm; // Distance in centimeters
double distanceInInch; // Distance in inches

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLightPin, OUTPUT);
  pinMode(blueLightPin, OUTPUT);
  pinMode(greenLightPin, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);

}

void loop() {
  timeMeasurement(); // Get sensor time
  distanceMeasurement(); // Get distance from sensor
  displayDistance(); // Display distance
  setColour(); // Set LED colour
}

// Measure time
void timeMeasurement() {

  // Clear trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Turn on trigPin for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Duration in microseconds
  duration = pulseIn(echoPin, HIGH);
}

// Measure distance
void distanceMeasurement() {

  // Calculate distance
  distanceInCm = duration * (0.0343) / 2; // Duration in microseconds multiplied by speed of sound in cm/μs divided by 2
  distanceInInch = distanceInCm / 2.54; // Convert cm to inch

  // Distance is set to -1 when the sensor is unreadable
  if (distanceInCm >= 400 || distanceInCm <= 3) {
    distanceInCm = -1;
    distanceInInch = -1;
  }

}

// Display distance onto LCD
void displayDistance() {

  lcd.setCursor(0, 0); // First line
  lcd.print("D (cm): "); // Centimeter Label
  if (distanceInCm > 0) { // Check if the distance is valid
    lcd.print(distanceInCm, 1); // Print centimeters and round to 1 decimal
  } else
    lcd.print("N/A  "); // Invalid distance


  lcd.setCursor(0, 1); // Second line
  lcd.print("D (in): "); // Inch label
  if (distanceInCm > 0) { // Check if the distance is valid
    lcd.print(distanceInInch, 1); // Print inches and round to 1 decimal
  } else
    lcd.print("N/A  "); // Invalid distance

  delay(500);
  lcdFormat(); // Format LCD text
}

// Format LCD text
void lcdFormat() {

  // Ones
  if (distanceInCm > 0 && distanceInCm < 10) {
    lcd.setCursor(11, 0);
    lcd.print("  ");
    lcd.setCursor(11, 1);
    lcd.print("  ");
  }

  // Tens
  if (distanceInCm >= 10 && distanceInCm < 100) {
    lcd.setCursor(12, 0);
    lcd.print("  ");
    lcd.setCursor(12, 1);
    lcd.print("  ");
  }
}

// Set RGB colours
void setRGBColour(int redLightValue, int greenLightValue, int blueLightValue) {

  analogWrite(redLightPin, redLightValue);
  analogWrite(greenLightPin, greenLightValue);
  analogWrite(blueLightPin, blueLightValue);

}

// Set specific colours based on the sensor distance
void setColour() {
  if (distanceInCm >= 400 || distanceInCm <= 3)
    setRGBColour(255, 0, 0);
  else if (distanceInCm > 3 && distanceInCm <= 10)
    setRGBColour(224, 125, 38);
  else if (distanceInCm > 10 && distanceInCm <= 20)
    setRGBColour(224, 184, 38);
  else if (distanceInCm > 20 && distanceInCm <= 30)
    setRGBColour(187, 224, 38);
  else if (distanceInCm > 40 && distanceInCm <= 50)
    setRGBColour(54, 224, 38);
  else if (distanceInCm > 50 && distanceInCm <= 100)
    setRGBColour(38, 97, 224);
  else if (distanceInCm > 100 && distanceInCm < 400)
    setRGBColour(255, 255, 255);
  else
    setRGBColour(0, 0, 0);
}
