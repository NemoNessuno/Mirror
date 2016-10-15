#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

/*
 * This script controls the vibration
 * of the motors.
 */

// Setup the NeoPixel as status LED
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 8, NEO_GRB + NEO_KHZ800);

// Set up input buffer
const int INPUT_SIZE = 8;
char input[INPUT_SIZE + 1];
// The last received input so we 
// can check if it changed
int lastInput;

// The digital IOs to which our motors are connected
const int MOTOR_RIGHT = 12;
const int MOTOR_LEFT = 3;
const int MOTOR_TOP = 10;
const int MOTOR_BOTTOM = 6;
const int MOTOR_FRONT = 9;
const int MOTOR_BACK = 2;

// Delay between toggles
const int DELAY = 20;

// Modulation variables
int initialDuration = 160;
int curDuration = 160;
int sleepDuration = 80;
int curSleep = 0;
int curMotor = -1;
int curProgram = -1;
int curStep = 0;
int maxStep = 1;

// Buffer to hold the motors
// currently used in a motion
int motors[4];

void initialize_motors() {
  pinMode(MOTOR_BACK, OUTPUT);  
  pinMode(MOTOR_FRONT, OUTPUT);  
  pinMode(MOTOR_BOTTOM, OUTPUT);  
  pinMode(MOTOR_TOP, OUTPUT);  
  pinMode(MOTOR_LEFT, OUTPUT);  
  pinMode(MOTOR_RIGHT, OUTPUT);

  digitalWrite(MOTOR_BACK, LOW);
  digitalWrite(MOTOR_FRONT, LOW);
  digitalWrite(MOTOR_BOTTOM, LOW);
  digitalWrite(MOTOR_TOP, LOW);
  digitalWrite(MOTOR_LEFT, LOW);
  digitalWrite(MOTOR_RIGHT, LOW); 
}
  
void setup() {
  initialize_motors();

  Serial.begin(9600);
  strip.begin();
  strip.show();
}

// Read the incoming command and run the
// appropriate motor program
void loop() {
  if (Serial.available()) {
    byte size = Serial.readBytes(input, INPUT_SIZE);
    input[size] = 0;
    Serial.println(input);
    int offset = 0;
    while(input[offset] != '(') offset++;
        
    setStatusLED(input[offset+1]-'0');
    setMotorProgram(input[offset+2]-'0');
  } else {
    setStatusLED(0);
  }

  delay(DELAY);  
}

// Activates the given IO if it should pulse
// else it deactivates it. Also handles the
// sleep time between pulses.
bool activate(int motor) {
  bool done = false;
  if (curDuration > 0){
    if (curSleep <= 0){
      curMotor = motor;
      digitalWrite(motor, HIGH);
      curDuration -= DELAY;
    } else {
      curSleep -= DELAY;      
    }
  } else {
    curSleep = sleepDuration;
    curDuration = initialDuration;
    curMotor = -1;
    digitalWrite(motor, LOW);
    done = true;
  }

  return done;
}

void setStatusLED(int status){
  setFloraColor(255-(85*status),status*85,0);
}

void setMotorProgram(int input){
  Serial.println(input);

  // Check if we got a new program
  if(curProgram != input){
    // If it's a strafing motion
    if(input < 6){
      initialDuration = 180;
      sleepDuration = 120;
    // if its a rotating motion
    } else {
      initialDuration = 160;
      sleepDuration = 60;
    }
    
    curProgram = input;
    curDuration = initialDuration;
    curSleep = 0;
    curStep = 0;

    if(curMotor != -1){
      digitalWrite(curMotor,LOW);
      curMotor = -1;
    }
  }
  
  // OFF Button
  switch (input) {
    case 0: // Forward
      activate(MOTOR_FRONT);
      break;
    case 1: // Top
      activate(MOTOR_TOP);
      break;
    case 2: // Right
      activate(MOTOR_RIGHT);
      break;
    case 3: // Left
      activate(MOTOR_LEFT);
      break;
    case 4: // Back
      activate(MOTOR_BACK);
      break;
    case 5: // Down
      activate(MOTOR_BOTTOM);
      break;
    case 6: //Rotate Right
      if (motors[0] != MOTOR_LEFT){
        motors[0] = MOTOR_LEFT;
        motors[1] = MOTOR_TOP;
        motors[2] = MOTOR_RIGHT;
        motors[3] = MOTOR_BOTTOM;
        curStep = 0;
      }
      if (activate(motors[curStep])){
        curStep = (curStep + 1) % 4;
      }
      break;
    case 7: // Rotate Left
      if (motors[0] != MOTOR_RIGHT){
        motors[0] = MOTOR_RIGHT;
        motors[1] = MOTOR_TOP;
        motors[2] = MOTOR_LEFT;
        motors[3] = MOTOR_BOTTOM;
        curStep = 0;
      }
      if (activate(motors[curStep])){
        curStep = (curStep + 1) % 4;
      }
      break;
    case 8: // Tilt Front
     if (motors[0] != MOTOR_TOP){
        motors[0] = MOTOR_TOP;
        motors[1] = MOTOR_FRONT;
        motors[2] = MOTOR_BOTTOM;
        curStep = 0;
      }
      if (activate(motors[curStep])){
        curStep = (curStep + 1) % 3;
      }
      break;
    case 9: // Tilt Back
      if (motors[0] != MOTOR_BOTTOM){
        motors[0] = MOTOR_BOTTOM;
        motors[1] = MOTOR_FRONT;
        motors[2] = MOTOR_TOP;
        curStep = 0;
      }
      if (activate(motors[curStep])){
        curStep = (curStep + 1) % 3;
      }
   default:
      break;
  }
}

void setFloraColor(int r, int g, int b)
{
  strip.setPixelColor(0, strip.Color(r, g, b));
  strip.show();
}
