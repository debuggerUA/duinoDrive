#include <Ultrasonic.h>

#define PIN_ENA 9
#define PIN_ENB 3
#define PIN_IN1 7
#define PIN_IN2 6
#define PIN_IN3 5
#define PIN_IN4 4

#define DRIVE_POWER 125
#define SLOW_DRIVE_POWER 75
#define STEERING_POWER 100
uint8_t testDrivePower = DRIVE_POWER;

#define FAR_AWAY 200 //cm
#define NOT_FAR_AWAY 50 //cm

#define LEFT 1
#define RIGHT 2

int previousObstacleDistance = -1;

Ultrasonic ultrasonic(10, 11, 40000UL);

void setup() {

  // Setup the control PINs
  pinMode(PIN_ENA, OUTPUT);
  pinMode(PIN_ENB, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);
  allStop();
}

void loop() {
  allStop();
  int forwardDistance = ultrasonic.read();
  
  if (forwardDistance >= FAR_AWAY) {
    // go forward for a FAR_AWAY distance
    driveForward(DRIVE_POWER);
    delay(1500);
  } else if (forwardDistance >= NOT_FAR_AWAY) {
    // go forward for about half of NOT_FAR_AWAY distance
    driveForward(SLOW_DRIVE_POWER);
    delay(1500);
  } else {

    if (previousObstacleDistance < 0) {
      // we are too close to the obstacle (for a first time)
      // lets check try driving left or right for a while
      previousObstacleDistance = forwardDistance;    
      if (random(LEFT, RIGHT+1) == LEFT) steerLeft();
      else steerRight();
      driveForward(SLOW_DRIVE_POWER);
      delay(1000);
    } else {
      if (forwardDistance <= previousObstacleDistance) {
        // didn't help, lets try driving backwards
        driveBackward(SLOW_DRIVE_POWER);
        previousObstacleDistance = -1;
      }
    }
  }
}

void allStop() {
  mainStop();
  secondaryStop();
  delay(100);
}

void driveForward(int withPower) {
  analogWrite(PIN_ENA, withPower);
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
}

void driveBackward(int withPower) {
  analogWrite(PIN_ENA, withPower);
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, HIGH);
}

void steerLeft() {
  analogWrite(PIN_ENB, STEERING_POWER);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, HIGH);
}

void steerRight() {
  analogWrite(PIN_ENB, STEERING_POWER);
  digitalWrite(PIN_IN3, HIGH);
  digitalWrite(PIN_IN4, LOW);
}

void mainStop() {
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
}

void secondaryStop() {
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, LOW);
}

void testRun() {
  driveForward(DRIVE_POWER);
  delay(1000);
  allStop();
  driveBackward(SLOW_DRIVE_POWER);
  delay(1000);
  steerLeft();
  delay(500);
  allStop();
  steerRight();
  delay(500);
  allStop();
}
