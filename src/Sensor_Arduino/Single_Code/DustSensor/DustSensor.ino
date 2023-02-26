int dust_sensor = A0;     //미세먼지 핀 번호
float dust_value = 0;     // 센서에서 입력받은 미세먼지 값
float dust = 0; // ug/m^3값을 계산

int sensor_led = 12;      //센서 속 led
int sampling = 280;        // led 키고, 센서값 읽어들여 미세먼지 측정 샘플링 시간
int waiting = 40;
float stop_time = 9680;   // 센서 구동 정지 시간

void setup()
{
  Serial.begin(9600);
  pinMode(sensor_led, OUTPUT);
  pinMode (4, OUTPUT);
}

void loop()
{
  digitalWrite(sensor_led, LOW);
  delayMicroseconds(sampling);

  dust_value = analogRead(dust_sensor);
  delayMicroseconds(waiting);     //너무 많은 데이터 입력을 막기 위한 것
  
  digitalWrite(sensor_led, HIGH);
  delayMicroseconds(stop_time);

  dust = (0.17 * (dust_value * (5.0 / 1024)) - 0.1) * 1000;
  Serial.print("Dust Density [ug/m3] : ");
  Serial.print(dust);
  Serial.print("\t");

  if(dust <= 30)
  {
    Serial.println("good");
  }
  else if(30<dust && dust <= 80)
  {
    Serial.println("nomal");
  }
  else if(80<dust && dust <= 150)
  {
    Serial.println("Bad");
  }
  else
  {
    Serial.println("RUN!!!!!");
  }

  delay(2000);
}
