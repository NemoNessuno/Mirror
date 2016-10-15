#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

/*
 * Sender part of the direct serial
 * connection test. It sets up a serial
 * connection and sends a status counter:
 * 0 < counter < 4. 
 * The idea is that both Flora's NeoPixels
 * show the same colour.
 */

// Set up custom serial connection
const int RX_PIN = 9;
const int TX_PIN = 10;
SoftwareSerial conn(RX_PIN, TX_PIN);

// Set up the onboard neo pixel
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 8, NEO_GRB + NEO_KHZ800);

// The counter is the data we send
int counter = 0;

// Initialize everything
void setup() {
  conn.begin(9600);
  Serial.begin(9600);
  strip.begin();
  strip.show();
}

// Increment the counter and send it
// to the receiver. Also colour the NeoPixel
// depending on the counter
void loop() {
  Serial.println(String(counter));
  conn.println(String(counter));
  counter = (counter + 1) % 3;

  switch (counter) {    
    case 0: //red
      setFloraColor(50, 0, 0);
      break;
    case 1: //green
      setFloraColor(0, 50, 0);
      break;
    case 2: //blue
      setFloraColor(0, 0, 50);
      break;
    default: //Do nothing
      break;
  }
  
  delay(500);
}

// Convenience function to recolour the NeoPixel
void setFloraColor(int r, int g, int b)
{
  strip.setPixelColor(0, strip.Color(r, g, b));
  strip.show();
}
