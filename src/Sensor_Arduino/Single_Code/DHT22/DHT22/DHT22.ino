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
