void setup()
{
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop()
{
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  analogWrite(8, 127);
  delay(3000);
}
