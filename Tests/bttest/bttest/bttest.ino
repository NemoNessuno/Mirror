#include <SoftwareSerial.h>

/*
 * This Script is a simple test if the
 * Arduino receives anything via BlueTooth.
 * The bluetooth adapter works like any
 * other serial bus device.
 */
const int INPUT_SIZE = 1;
char input[INPUT_SIZE + 1];

void setup(void)
{
  // Initialize the serial connection.
  // We used the default ports
  // for Serial1 i.e. pins 19 (RX) and 18 (TX)
  Serial1.begin(9600); // init bluetooth
}

/*
 * Simply echo what you receive.
 */
void loop(void)
{
  if(Serial1.available()){
    byte size = Serial1.readBytes(input, INPUT_SIZE);
    input[size] = 0;
    Serial1.println(input);
  }  
  delay(100);
}
