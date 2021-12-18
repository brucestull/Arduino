void setup() {
  pinMode(0, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  digitalWrite(0, HIGH);
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(0, LOW);
  digitalWrite(4, LOW);
  delay(500);
}
