int Relay= 3;

void setup()
{
    pinMode(Relay, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    int light = analogRead(A0);
    Serial.println(light);
    if(light < 180)
    {
        digitalWrite(Relay, HIGH);
        delay(500);
    }
    else{
        digitalWrite(Relay, LOW);
        delay(500);
    }
}
