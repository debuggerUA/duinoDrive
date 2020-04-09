#define PIN_ENA 9
#define PIN_ENB 3
#define PIN_IN1 7
#define PIN_IN2 6
#define PIN_IN3 5
#define PIN_IN4 4

#define MAX_POWER 125

#define MINIMUM_POWER 50

uint8_t power = MINIMUM_POWER;

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
  power = MINIMUM_POWER;
  while(power < MAX_POWER) {
    mainForward(power);
    secondaryForward(power);

    delay(1000);
    power += 25;
  }

  allStop();
  delay(250);

  power = MAX_POWER;

  while(power > MINIMUM_POWER) {

    mainBackward(power);
    secondaryBackward(power);

    delay(1000);

    power -= 25;

  }
}

void allStop() {
  mainStop();
  secondaryStop();
}

void mainForward(int withPower) {
  analogWrite(PIN_ENA, withPower);
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
}

void mainBackward(int withPower) {
  analogWrite(PIN_ENA, withPower);
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, HIGH);
}

void secondaryBackward(int withPower) {
  analogWrite(PIN_ENB, withPower);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, HIGH);
}

void secondaryForward(int withPower) {
  analogWrite(PIN_ENB, withPower);
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
