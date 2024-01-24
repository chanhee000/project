#include "DHT.h"
#define DHTPIN A1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  int h = dht.readHumidity();
  int t = dht.readTemperature();

  Serial.print("humidity:");        // ‘시리얼 플로터’ 사용위해 이 부분 주석 필요
  Serial.println(h);                // 습도 값 출력
  Serial.print("temperature:");     // ‘시리얼 플로터’ 사용위해 이 부분 주석 필요
  Serial.println(t);                // 온도 값 출력
  delay(1000);
}
