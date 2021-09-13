void setup() {
  for (int i = 4; i <= 11; i++) {
    pinMode(i, OUTPUT);
  }
}
void loop() {
  int sensorReading = analogRead(A0);
  int t = map(sensorReading, 0, 1023, 1, 20);
  digitalWrite(11, HIGH); digitalWrite(9, LOW); delay(t);
  digitalWrite(10, HIGH); digitalWrite(8, LOW); delay(t);
  digitalWrite(9, HIGH); digitalWrite(11, LOW); delay(t);
  digitalWrite(8, HIGH); digitalWrite(10, LOW); delay(t);

  digitalWrite(4, HIGH); digitalWrite(6, LOW); delay(t);
  digitalWrite(5, HIGH); digitalWrite(7, LOW); delay(t);
  digitalWrite(6, HIGH); digitalWrite(4, LOW); delay(t);
  digitalWrite(7, HIGH); digitalWrite(5, LOW); delay(t);  
}
