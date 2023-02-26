/*
지구의 CO2 농도는 언제나 일정하기 때문에 실외에서 CO2값이 400ppm이 되도록 RZERO 76.63 의 값을 수정하면 됩니다.
출처: https://analog2u.tistory.com/52 [사르륵:티스토리]
http://davidegironi.blogspot.com/2014/01/cheap-co2-meter-using-mq135-sensor-with.html#.Yw7sl9PP1D8


*/
///===============================================================
/// The load resistance on the board
#define RLOAD 10.0
/// Calibration resistance at atmospheric CO2 level
#define RZERO 76.63
/// Parameters for calculating ppm of CO2 from sensor resistance
#define PARA 116.6020682
#define PARB 2.769034857
void setup() 
 {
	Serial.begin(115200);
 }

void loop()
 {
int val = analogRead(7);
val = (1023./(float)val) * 5. - 1.* RLOAD;
float Resistance;
Resistance = val;
float PPM;
PPM = PARA * pow((Resistance/RZERO), -PARB);
Serial.println(PPM,1);
}
///===============================================================
