#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

/*
 * In this script the current data from the BNO055
 * is read and send via USB/BlueTooth. Also relays
 * the current motor program to the motor controler
 */

// Initialize the Bosch BNO055
Adafruit_BNO055 bno = Adafruit_BNO055();

// Setup the direct connection to the motor controller
const int RX_PIN_SER = 9;
const int TX_PIN_SER = 10;
SoftwareSerial conn(RX_PIN_SER, TX_PIN_SER);

// Setup input and output buffers
const int INPUT_SIZE = 1;
const int OUTPUT_SIZE = 4;
char input[INPUT_SIZE + 1];
char output[OUTPUT_SIZE + 1];

// Create a counter to check if
// the connection is ok
const int COUNTER_MAX = 9;
int counter = 0;

// Initialize to program 11 = no motion
int program = 11 + '0';

// Send the 3 Vector via USB
void printVector(imu::Vector<3> vector, bool newLine){
  Serial.print(vector.x()); Serial.print(","); Serial.print(vector.y()); Serial.print(","); 
  if (newLine) {
    Serial.println(vector.z());
  } else {
    Serial.print(vector.z());
    Serial.print(",");
  }
}  

// Send the 3 Vector via bluetooth
void printVectorBluetooth(imu::Vector<3> vector, bool newLine){
  Serial1.print(vector.x()); Serial1.print(","); Serial1.print(vector.y()); Serial1.print(","); Serial1.print(vector.z());
  if (newLine) {
    Serial1.println();
  } else {   
    Serial1.print(",");
  }
}

/**************************************************************************/
/*!
    @brief  Initialises all the sensors used by this example
*/
/**************************************************************************/
void initSensors()
{
    /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  bno.setExtCrystalUse(true);
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
void setup(void)
{
  conn.begin(9600);      // init software serial
  delay(50);
  Serial1.begin(9600); // init bluetooth
  delay(50);
  Serial.begin(9600);
  
  /* Initialise the sensors */
  initSensors();
}

/**************************************************************************/
/*! 
 @brief  Constantly check the roll/pitch
*/
/**************************************************************************/
void loop(void)
{
  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2
  imu::Vector<3> linAcc = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);  

  uint8_t system, gyro, accel, mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);
  
  if(Serial1.available()){
    byte size = Serial1.readBytes(input, INPUT_SIZE);
    input[size] = 0;
    Serial1.println(input[0]);
    program = input[0];
  }

  // Construct the output buffer
  output[0] = '(';
  output[1] = accel + '0';
  output[2] = program;
  output[3] = ')';
  output[4] = 0;
  conn.print(output);
  
  if (gyro >= 2 && accel >= 2 && mag >= 2)
  {
    Serial1.print("Start "); Serial1.print(counter); Serial1.print(": ");
    printVectorBluetooth(euler, false);
    printVectorBluetooth(linAcc, true);
    counter = (counter + 1) % COUNTER_MAX ;
  } else {
    Serial.print("CALIBRATION: Sys=");
    Serial.print(system, DEC);
    Serial.print(" Gyro=");
    Serial.print(gyro, DEC);
    Serial.print(" Accel=");
    Serial.print(accel, DEC);
    Serial.print(" Mag=");
    Serial.println(mag, DEC);
  }
  delay(50);
}
