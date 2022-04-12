
int motorPin = 10;
int pingPin = 8;
int echoPin = 9;
int timeButtonPin = 6;
int ledPin = 7;
int onOffPin = 3;
int buzzerPin = 5;
int timeAlarm = 0;
bool start = false;
bool alarm = false;


void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(timeButtonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(onOffPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
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
  
  //snooze button doubles as 
  if (digitalRead(timeButtonPin) == HIGH) {
    timeAlarm = timeAlarm + 1;
    ledFlash();
    delay(500);
  }
  //when switch is on the timer starts
  if (digitalRead(onOffPin) == LOW) {
    start = true;
    for (int i = 1; i <= timeAlarm; i++) {
      ledFlash();
      delay(500);
    }
  }
  

  if (cm > 20 && start) {
    delay(timeAlarm * 1000);
    alarm = true;
    analogWrite(motorPin, 255);
    timeAlarm = 0;
    tone(buzzerPin, 500);
  } else if (cm < 20) {
    analogWrite(motorPin, 0);
    start = false;
  } else if (digitalRead(timeButtonPin) == HIGH) {
    alarm = false;
    noTone(buzzerPin);
  }
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void ledFlash() {
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
}
