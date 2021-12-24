#include <AccelStepper.h>
#include <MultiStepper.h>

#define JoyX A0       // Joystick X pin
#define JoyY A1       // Joystick Y pin
#define slider A2     // Slider potentiometer
#define inOutPot A3   // In and Out speed potentiometer
#define JoySwitch 10  // Joystick switch connected
#define InOutSet 12   // Set Button
#define limitSwitch 11
#define inLED 8
#define outLED 9
#define stp 7
#define dir 6

// Define the stepper motors and the pins the will use
AccelStepper stepper1(1, 7, 6); // (Type:driver, STEP, DIR)
AccelStepper stepper2(1, 5, 4);
AccelStepper stepper3(1, 3, 2);

MultiStepper StepperControl;  // Create instance of MultiStepper

int JoyXPos = 0;
int JoyYPos = 0;
int sliderPos = 0;
int currentSpeed = 500;
int inOutSpeed = 100;

int XInPoint = 0;
int YInPoint = 0;
int ZInPoint = 0;
int XOutPoint = 10000;
int YOutPoint = 0;
int ZOutPoint = 0;
int InandOut = 0;
int button;
char user_input;
int x = 0;
int y = 0;
int z = 0;
int i = 0;
int j = 0;
int k = 0;
int state;

void setup() {
  // Set initial seed values for the steppers
  stepper1.setMaxSpeed(3000);
  stepper1.setSpeed(2000);
  stepper2.setMaxSpeed(3000);
  stepper2.setSpeed(0);
  stepper3.setMaxSpeed(3000);
  stepper3.setSpeed(0);
  pinMode(JoySwitch, INPUT_PULLUP);
  pinMode(InOutSet, INPUT_PULLUP);
  pinMode(limitSwitch, INPUT_PULLUP);
  pinMode(inLED, OUTPUT);
  pinMode(outLED, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(9600);

  // Create instances for MultiStepper - Adding the 3 steppers to the StepperControl instance for multi control
  StepperControl.addStepper(stepper1);
  StepperControl.addStepper(stepper2);
  StepperControl.addStepper(stepper3);

  // Move the slider to the initial position - homing
  while (digitalRead(limitSwitch) != 0) {
    stepper1.setSpeed(2000);
    stepper1.runSpeed();
    stepper1.setCurrentPosition(0);
  }
  delay(20);
  // Move 200 steps back from the limit switch
  while (stepper1.currentPosition() != -400) {
    stepper1.setSpeed(-2000);
    stepper1.run();
  }
}
        
void loop() {
  
  // Limiting the movement - Do nothing if limit switch pressed or distance traveled in other direction greater then 80cm
  while (digitalRead(limitSwitch) == 0) {
    stepper1.setSpeed(0);
    stepper1.runSpeed();
    stepper1.setCurrentPosition(0);
    delay(20); 
    stepper1.setSpeed(-inOutSpeed);
    stepper1.run();
  }
  while (stepper1.currentPosition() < -64800) {
    stepper1.setSpeed(inOutSpeed);
    stepper1.run();
  }
  JoyXPos = analogRead(JoyX);
       if (JoyXPos > 600) {
         stepper3.setSpeed(100);
       }
       else if (JoyXPos < 400) {
         stepper3.setSpeed(-100);
       }
       else {
         stepper3.setSpeed(0);
       }
      JoyYPos = analogRead(JoyY);
      if (JoyYPos > 600) {
         stepper2.setSpeed(100);
      }
      else if (JoyYPos < 400) {
         stepper2.setSpeed(-100);
      }
      else {
        stepper2.setSpeed(0);
      }
      sliderPos = analogRead(slider);
      if (sliderPos > 600) {
        inOutSpeed = speedUp();
        sliderPos = map(sliderPos, 600, 1024, 0, 3000);
        stepper1.setSpeed(inOutSpeed); // Increase speed as turning
        digitalWrite(inLED, HIGH);
        digitalWrite(outLED, LOW);
      }
      else if (sliderPos < 400 ) {
        inOutSpeed = speedUp();
        sliderPos = map(sliderPos, 400, 0, 0, 3000);
        stepper1.setSpeed(-inOutSpeed); 
        digitalWrite(inLED, LOW);
        digitalWrite(outLED, HIGH);
      }
  // If potentiometer in middle, no movement
      else {
        inOutSpeed = speedUp();
        stepper1.setSpeed(0);
        digitalWrite(inLED, LOW);
        digitalWrite(outLED, LOW);
      }
  stepper1.runSpeed();
  stepper2.runSpeed();
  stepper3.runSpeed();
  button = digitalRead(InOutSet);
  if (button == 1){
     x++;
     Serial.println(x);
     delay(500);
     if (x == 1){
      kiri();
      delay(500);
      kanan();   
    }
    if (x == 2){
      x= 0;
    }
  }
 }
int speedUp() {
  int customDelay = analogRead(inOutPot); // Reads the potentiometer
  int newCustom = map(customDelay, 0, 1024, 0,3000); // Convrests the read values of the potentiometer from 0 to 1023 into desireded delay values (300 to 4000)
  return newCustom;  
}

void kiri(){
  digitalWrite(6, LOW);
  for(i = 0; i <20000; i++){
    digitalWrite(7, HIGH);
    delayMicroseconds(700);
    digitalWrite(7, LOW);
    delayMicroseconds(700);
  }
}
void kanan(){
  digitalWrite(6, HIGH);
  for(i = 0; i <20000; i++){
    digitalWrite(7, HIGH);
    delayMicroseconds(700);
    digitalWrite(7, LOW);
    delayMicroseconds(700);
  }
}
void atas(){
  digitalWrite(4, LOW);
  for(y = 0; y <2000; y++){
    digitalWrite(5, HIGH);
    delayMicroseconds(700);
    digitalWrite(5, LOW);
    delayMicroseconds(700);
  }
}
void bawah(){
  digitalWrite(4, LOW);
  for(y = 0; y <2000; i++){
    digitalWrite(4, HIGH);
    delayMicroseconds(700);
    digitalWrite(4, LOW);
    delayMicroseconds(700);
  }
}

void skiri(){
  digitalWrite(2, LOW);
  for(z = 0; z <2000; z++){
    digitalWrite(3, HIGH);
    delayMicroseconds(700);
    digitalWrite(3, LOW);
    delayMicroseconds(700);
  }
}
void skanan(){
  digitalWrite(2, LOW);
  for(z = 0; z <2000; z++){
    digitalWrite(3, HIGH);
    delayMicroseconds(700);
    digitalWrite(3, LOW);
    delayMicroseconds(700);
  }
}

