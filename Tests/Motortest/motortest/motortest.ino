/*
 * With this script we simply wanted
 * to test the connection of the motors
 * with the digital IOs. It sets up
 * some digital IOs as outputs and
 * toggles them continously.
 */

const int MOTOR_RIGHT = 12;
const int MOTOR_LEFT = 3;
const int MOTOR_TOP = 10;
const int MOTOR_BOTTOM = 6;
const int MOTOR_FRONT = 9;
const int MOTOR_BACK = 2;

/*
 * Set up digital IOs as outputs.
 */
void setup() {
  pinMode(MOTOR_BACK, OUTPUT);  
  pinMode(MOTOR_FRONT, OUTPUT);  
  pinMode(MOTOR_BOTTOM, OUTPUT);  
  pinMode(MOTOR_TOP, OUTPUT);  
  pinMode(MOTOR_LEFT, OUTPUT);  
  pinMode(MOTOR_RIGHT, OUTPUT);
}

/*
 * Toggle set up IOs periodically.
 */
void loop() {
  digitalWrite(MOTOR_BACK, HIGH);
  delay(1000);
  digitalWrite(MOTOR_BACK, LOW);

  digitalWrite(MOTOR_FRONT, HIGH);
  delay(1000);
  digitalWrite(MOTOR_FRONT, LOW);

  digitalWrite(MOTOR_BOTTOM, HIGH);
  delay(1000);
  digitalWrite(MOTOR_BOTTOM, LOW);

  digitalWrite(MOTOR_TOP, HIGH);
  delay(1000);
  digitalWrite(MOTOR_TOP, LOW);
  digitalWrite(MOTOR_RIGHT, HIGH);
  delay(1000);
  digitalWrite(MOTOR_RIGHT, LOW);
  digitalWrite(MOTOR_LEFT, HIGH);
  delay(1000);
  digitalWrite(MOTOR_LEFT, LOW);
}
