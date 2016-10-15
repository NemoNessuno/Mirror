#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

/*
 * This is the receiver part of our
 * direct serial connection test
 * between two Arduinos. It echoes the
 * received data and turns the onboard
 * NeoPixel green when data is received.
 * The idea is that both Flora's NeoPixels
 * show the same colour.
 */

// Set up a custom serial connection with
// RX and TX reversed.
const int RX_PIN = 9;
const int TX_PIN = 10;
SoftwareSerial conn(RX_PIN, TX_PIN);

// Set up the onboard neo pixel
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 8, NEO_GRB + NEO_KHZ800);

// Create an input buffer
const int INPUT_SIZE = 1;
char input[INPUT_SIZE + 1];

// The status is the data we receive
int status = 0;

// Initialize all the parts
void setup() {
  conn.begin(9600);
  Serial.begin(9600);
  strip.begin();
  strip.show();
}

// Read the software serial and echo the received data
// also color the onboard NeoPixel depending on the received
// status
void loop() {
  if (conn.available()) {
    Serial.println("Input: ");
    byte size = conn.readBytes(input, INPUT_SIZE);
    input[size] = 0;
    status = input[0];
  }
  
  setFloraColor(255-85*status,status*85,0);

  delay(50);
  
}

// Convenience function to recolour the NeoPixel
void setFloraColor(int r, int g, int b)
{
  strip.setPixelColor(0, strip.Color(r, g, b));
  strip.show();
}
