
int motorPin = 9;
int pingPin = 6;
int echoPin = 7;
int timeButton = 2;
int timeAlarm = 0;
int ledPin = 4;
bool start = false;


void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(timeButton, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  long cm, duration;
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  delay(100);
  if (digitalRead(timeButton) == HIGH) {
    start = true;
    timeAlarm = + 1;
    digitalWrite(ledPin, HIGH);
    delay(10);
  }

  if (cm > 20 && start) {
    delay(timeAlarm * 5000);
    analogWrite(motorPin, 255);
    digitalWrite(ledPin, LOW);
    timeAlarm = 0;
  } else if (cm < 20) {
    analogWrite(motorPin, 0);
    start = false;
  }
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
