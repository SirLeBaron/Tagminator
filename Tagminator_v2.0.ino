
//set debug to 1 to enable serial printing
int debug = 1;

// set pin numbers:
const int detectorPin = 43;          // contrast sensor input pin
const int motorPin = 51;             // motor1 output pin
const int tagPin = 53;               // tag detected -signal output pin
const int nextTagPin = 47;           // next tag -signal input pin
const int motorEnablePin = 45;       // motor enable output pin

// set detectorState to 0 when using a contrast sensor that turns signal HIGH when a tag is detected
// set detectorState to 1 when using a contrast sensor that turns signal LOW when a tag is detected
int detectorState = 1;             
int readContrastSensor = 1;          // the current reading from the input pin
int detectorOff = 0;                 // contrast sensor will be ignored when this value is set to 1
int readNextTag = 0;
int nextTagState = 0;
int steps = 0;                       // step count for acceleration
int accSteps = 3200;                 // acceleration length in steps
// motor speed settings. the higher the values the slower the motor runs and vice versa
double speedDelay = 2000;            // motor step signal duration in microseconds   
int motorSignalOff = 5;              // delay between motor step signals in microseconds
int maxDelay = speedDelay;           // slowest speed 
int minDelay = 69;                   // fastest speed
int delayReset = speedDelay;         // speed reset
double speedChange = 10;             // the higher the value the faster acceleration and slowdown
int runState = 0;                    // 
int motorRunState = 0;               // 
int motorState = 0;                  //
double jumpLength = 7000;            // the amount of steps for jump. contrast sensor will be ignored during the jump
int jumpState = 1;                   // initial state of jump. 0 is off 1 is on.

void setup() {
  pinMode(motorPin, OUTPUT);         // set the motor pin as OUTPUT
  pinMode(motorEnablePin, OUTPUT);   // set the motor pin as OUTPUT  
  pinMode(tagPin, OUTPUT);  
  pinMode(detectorPin, INPUT);
  pinMode(nextTagPin, INPUT);
  digitalWrite(motorEnablePin, HIGH);
  Serial.begin(9600);
}
void runMotor()
{
  if(motorRunState==1){
  digitalWrite(motorPin, HIGH);
  delayMicroseconds(speedDelay);
  digitalWrite(motorPin, LOW);
  delayMicroseconds(motorSignalOff);
  steps++;
  }
}
void contrastSensor()
{
  if(steps<jumpLength){
    detectorOff=1;
  }else{
    detectorOff=0;
  }
  if(detectorOff==0){
    readContrastSensor = digitalRead(detectorPin);    // read the nextTag pin value  
    if (readContrastSensor != detectorState) {        // check if nextTag signal has changed
      detectorState = readContrastSensor;             // set detectorState to the new value
      if(debug == 1){
        Serial.print("detectorState changed to= ");
        Serial.println(detectorState);
      } 
      if (detectorState == LOW) {          // checks value
        stopMotor();
        jumpState = 0;
        digitalWrite(motorEnablePin, HIGH);      
        if(debug == 1){
          Serial.print("motorRunState changed to= ");
          Serial.println(motorRunState);
          Serial.print("jumpState changed to= ");
          Serial.println(jumpState);
        }        
      }
    }  
  } 
}
void nextTag()
{
  readNextTag = digitalRead(nextTagPin);    // read the nextTag pin value  
  if (readNextTag != nextTagState) {        // check if nextTag signal has changed
    nextTagState = readNextTag;             // set detectorState to the new value
    if(debug == 1){
      Serial.print("nextTagState changed to= ");
      Serial.println(nextTagState);
    } 
    if (nextTagState == HIGH) {          // checks value
      motorRunState = 1;                         //
      jumpState = 1;
      steps=0;
      digitalWrite(motorEnablePin, LOW);      
      if(debug == 1){
        Serial.print("runState changed to= ");
        Serial.println(runState);
        Serial.print("jumpState changed to= ");
        Serial.println(jumpState);
      }        
    }
  }  
}

void accelerate()
{
  speedDelay=speedDelay - speedChange;
  if(speedDelay < minDelay){
    speedDelay=minDelay;
  }
}
void stopMotor()
{
    speedDelay=delayReset;
    motorRunState=0;
    steps=0;
    digitalWrite(motorEnablePin, HIGH);
}
void loop(){
  nextTag();
  contrastSensor();  
  runMotor(); 
  if(steps < accSteps){
    accelerate();
  }
}
