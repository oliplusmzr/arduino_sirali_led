const int ledPins[] = {2,3,4,5,6,7,8,9}; //POWERED BY OLIPLUSMZR

void setup() {
  for (int x = 0; x < 8; x++) {
    pinMode(ledPins[x], OUTPUT);
  }

  for (int y = 0; y < 3; y++) {
    for (int x = 0; x <= 7; x++) {
      digitalWrite(ledPins[x], HIGH);
    }
    delay(1000);
    for (int x = 0; x < 8; x++) {
      digitalWrite(ledPins[x], LOW);
    }
    delay(1000);
  }
}

void loop() {
  for (int x = 0; x < 8; x++) {
    digitalWrite(ledPins[x], HIGH);
    delay(500);
    digitalWrite(ledPins[x], LOW);
  }

  for (int x = 7; x >= 0; x--) {
    digitalWrite(ledPins[x], HIGH);
    delay(500);
    digitalWrite(ledPins[x], LOW);
  }
} //POWERED BY OLIPLUSMZR