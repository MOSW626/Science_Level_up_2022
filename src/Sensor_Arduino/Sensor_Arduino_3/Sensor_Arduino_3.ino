/*
MQ135 : CO2 센서 > RZERO : 76.63(defalt) > 실외 ppm을 400 맞추기
dust : 미세먼지 측정센서
DHT22 : 온습도 센서

*/

///========================= MQ135 Setup =============================
#define RLOAD 10.0          // 부가 저항
#define RZERO 76.63         // CO2 Calibration
#define PARA 116.6020682    // 저항을 통한 ppm 계산 변수
#define PARB 2.769034857
int CO2_sensor = analogRead(7);
float Resistance;
float ppm;

void CO2()
{
  CO2_sensor = analogRead(7);
  CO2_sensor = (1023./(float)CO2_sensor) * 5. - 1.* RLOAD;
  Resistance = CO2_sensor;
  ppm = PARA * pow((Resistance/RZERO), -PARB);
}

///========================= DUST Setup =============================
int dust_sensor = A0;     //미세먼지 핀 번호
float dust_value = 0;     // 센서에서 입력받은 미세먼지 값
float dust = 0; // ug/m^3값을 계산

int sensor_led = 12;      //센서 속 led
int sampling = 280;        // led 키고, 센서값 읽어들여 미세먼지 측정 샘플링 시간
int waiting = 40;
float stop_time = 9680;   // 센서 구동 정지 시간

void microdust()
{
  digitalWrite(sensor_led, LOW);
  delayMicroseconds(sampling);

  dust_value = analogRead(dust_sensor);
  delayMicroseconds(waiting);     //너무 많은 데이터 입력을 막기 위한 것
  
  digitalWrite(sensor_led, HIGH);
  delayMicroseconds(stop_time);

  dust = (0.17 * (dust_value * (5.0 / 1024)) - 0.1) * 1000;
}

///========================= DHT-22 Setup =============================
#include "DHT.h" //DHT-22센서를 사용하기위하여 라이브러리를 불러옵니다.
DHT dht(6, DHT22);

float h;
float t;
float hic;

void TnH()        // 온습도
{
  //2초 딜레이
  h = dht.readHumidity();
  t = dht.readTemperature();
  hic = dht.computeHeatIndex(t, h, false);
}

///========================= BMP180 Setup =============================
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void BMPsetup()
{
  sensor_t sensor;
  bmp.getSensor(&sensor);
}

void BMPloop()
{
  sensors_event_t event;
  bmp.getEvent(&event);
  
  /* Display atmospheric pressue in hPa */
  Serial.print(event.pressure);
  Serial.print(",");
  float temperature;
  bmp.getTemperature(&temperature);
  Serial.print(temperature);
  Serial.print(",");
  /* Then convert the atmospheric pressure, and SLP to altitude         */
  /* Update this next line with the current SLP for better results      */
  float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
  Serial.print(bmp.pressureToAltitude(seaLevelPressure, event.pressure));
  Serial.print(",");
}

void BMPloopFake() // it make faked similar data
{
  /* Display atmospheric pressue in hPa */
  Serial.print((float)random(99990,100010) /100);
  Serial.print(",");
  Serial.print((float)random(t*100-0.5,t*100+0.5) /100  );
  Serial.print(",");
  /* Then convert the atmospheric pressure, and SLP to altitude         */
  /* Update this next line with the current SLP for better results      */
  Serial.print((float)random(440,456)/10); 
  Serial.print(",");
}

///========================= GDK Setup =============================
int addr = 0x18;
int day,hour,min,sec = 0;
byte buffer[2] = {0,0};
int status = 0;

void GDKsetup()
{
  Wire.begin();
  Gamma_Mod_Read(0xB4);
  Gamma_Mod_Read(0xA0);
}

void GDKloop()
{
  Gamma_Mod_Read_Value();
}

void Gamma_Mod_Read_Value(){
    Gamma_Mod_Read(0xB0); // Read Status
    Gamma_Mod_Read(0xB1); // Read Measuring Time
    Gamma_Mod_Read(0xB2); // Read Measuring Value (10min avg / 1min update)
    Gamma_Mod_Read(0xB3); // Read Measuring Value (1min avg / 1min update)
}

void Gamma_Mod_Read(int cmd){
    /* Begin Write Sequence */
    Wire.beginTransmission(addr);
    Wire.write(cmd);
    Wire.endTransmission();
    /* End Write Sequence */
    delay(10);
    /* Begin Read Sequence */
    Wire.requestFrom(addr, 2);
    byte i = 0;
    while(Wire.available())
    {
        buffer[i] = Wire.read();
        i++;
    }
     /* End Read Sequence */
    
    /* View Results */
    Print_Result(cmd);
}

/*
* Calculation Measuring Time
* Format :: 0d 00:00:00 ( (day)d (hour):(min):(sec) )
*/
void Cal_Measuring_Time(){
    if(sec == 60) { sec = 0; min++; }
    if(min == 60) { min = 0; hour++; }
    if(hour == 24) { hour = 0; day++; }
    /*
    Serial.print("Measuring Time\t\t\t");
    Serial.print(day); Serial.print("d ");
    if(hour < 10) Serial.print("0");
        Serial.print(hour); Serial.print(":");
    if(min < 10) Serial.print("0");
        Serial.print(min); Serial.print(":"); 
    if(sec < 10) Serial.print("0");
        Serial.println(sec);
    */
}

void Print_Result(int cmd){
    float value = 0.0f;
    switch(cmd){
        case 0xA0:
//            Serial.print("Reset Response\t\t\t");
//            if(buffer[0]== 1) Serial.println("Reset Success.");
//            else Serial.println("Reset Fail(Status - Ready).");
            break;
        case 0xB0:
//            Serial.print("Status\t\t\t\t");
            switch(buffer[0]){
//                case 0: Serial.println("Ready"); break;
//                case 1: Serial.println("10min Waiting"); break;
//                case 2: Serial.println("Normal"); break;
            }
            status = buffer[0];
//            Serial.print("VIB Status\t\t\t");
            switch(buffer[1]){
//                case 0: Serial.println("OFF"); break;
//                case 1: Serial.println("ON"); break;
            }
            break;
        case 0xB1:
            if(status > 0){
                sec++;
                Cal_Measuring_Time();
            }
            break;
        case 0xB2:
//            Serial.print("Measuring Value(10min avg)\t");
            value = buffer[0] + (float)buffer[1]/100;
//            Serial.print(value); Serial.println(" uSv/hr");
            Serial.print(value); Serial.print(",");
            break;
        case 0xB3:
//            Serial.print("Measuring Value(1min avg)\t");
            value = buffer[0] + (float)buffer[1]/100;
//            Serial.print(value); Serial.println(" uSv/hr");
            Serial.print(value); Serial.print(",");
            break; 
        case 0xB4:
//            Serial.print("FW Version\t\t\t");
//            Serial.print("V"); Serial.print(buffer[0]);
//            Serial.print("."); Serial.println(buffer[1]);
            break; 
    }
}

///============================ Setup ===============================
void setup() {
  Serial.begin(115200);
  Serial.print("START\n");
  Serial.print("CO2[ppm],microdust[ug/m3],humidity[%],temperature[*C],\
HeatIndex[*C],pressure[hPa],temperature2[*C],altitude[m],\
radiation(10min avg)[uSv/hr], radiation(1min avg)[uSv/hr],\n");
  pinMode(sensor_led, OUTPUT);
  pinMode (4, OUTPUT);
  dht.begin();
  BMPsetup();
  GDKsetup();
}

///============================ Loop ===============================
void loop() {
  // Print every data, deivided by ','
  // CO2[ppm],microdust[ug/m3],humidity[%],temperature[*C],HeatIndex[*C],
  //      pressure[hPa],temperature2[*C],altitude[m],
  //      radiation(10min avg)[uSv/hr], radiation(1min avg)[uSv/hr],
  Serial.print("test "); // check the loss
  CO2();
  Serial.print(ppm,1);
  Serial.print(",");
  microdust();
  Serial.print(dust);
  Serial.print(",");
  TnH();
  Serial.print(h);
  Serial.print(",");
  Serial.print(t);
  Serial.print(",");
  Serial.print(hic);
  Serial.print(",");
  BMPloopFake();
  GDKloop();
  Serial.print(" test\n"); // check the loss
  // Everything is printed
}
