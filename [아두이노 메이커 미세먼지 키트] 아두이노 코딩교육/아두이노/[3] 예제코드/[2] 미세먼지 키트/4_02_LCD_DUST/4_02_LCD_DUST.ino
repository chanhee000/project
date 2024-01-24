#include <Wire.h>                // i2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C.h>   // LCD 1602 I2C용 라이브러리

int dust_sensor = A0;            // 미세먼지 핀 설정

float dust_value = 0;            // 센서에서 입력받은 미세먼지 값
float dustDensityug = 0;         // ug/m^3 값을 계산

int sensor_led = 12;             // 미세먼지 센서 안에 있는 적외선 led 핀 번호
int sampling = 280;              // 적외선 led를 키고, 센서값을 읽어들여 미세먼지를 측정하는 샘플링 시간
int waiting = 40;    
float stop_time = 9680;          // 센서를 구동하지 않는 시간

double five_dust[5] = {0};
double recent_dust = 0 ;
double total_dust = 0;

float dust_init = 0;
float dust_initial = 0;

LiquidCrystal_I2C lcd(0x27,16,2); // 접근주소: 0x3F or 0x27 1602 Display

void setup(){
  lcd.init();                    // LCD 초기화
  lcd.backlight();               // 백라이트 켜기

  pinMode(sensor_led,OUTPUT);
  
  Serial.begin(9600);            // 시리얼 모니터 시작, 속도는 9600

  for(int i = 0 ; i < 5 ; i++){       //미세먼지 측정센서 초기 값 구하기 
  digitalWrite(sensor_led, LOW);      //미세먼지 측정 5번하기
  delayMicroseconds(sampling);
  dust_init += analogRead(dust_sensor);
  delayMicroseconds(waiting);
  digitalWrite(sensor_led, HIGH);
  delayMicroseconds(stop_time);
}
dust_initial = (((dust_init/5)*5.0)/1024.0);   //측정한 5번 미세먼지 값 평균 구하기
Serial.print("dust_initial : ");
Serial.println(dust_initial);
}

void loop(){
  digitalWrite(sensor_led, LOW);         // LED 켜기
  delayMicroseconds(sampling);           // 샘플링해주는 시간. 

  int count=0;
  dust_value = analogRead(dust_sensor);  // 센서 값 읽어오기
    
  delayMicroseconds(waiting);            // 너무 많은 데이터 입력을 피해주기 위해 잠시 멈춰주는 시간. 
  
  digitalWrite(sensor_led, HIGH);        // LED 끄기
  delayMicroseconds(stop_time);          // LED 끄고 대기 
   
  recent_dust = (((dust_value * (5.0 / 1024)) - dust_initial) /0.005);  // 미세먼지 값 계산
  five_dust[4] = recent_dust;            // 새로운 미세먼지 값 입력
  total_dust = five_dust[4];             // 5개의 미세먼지 값을 저장할 변수
  
  for(int i=0; i<4; i++)
  {
    total_dust += five_dust[i];
    five_dust[i] = five_dust[i+1];       // 0~4번째까지 미세먼지 값 저장을 위해 4번째 배열 비워주기
  }

  if(five_dust[0] != 0)
  {
    dustDensityug = total_dust / 5;
    Serial.print("Dust Density [ug/m^3]: "); // 시리얼 모니터에 미세먼지 값 출력    
    Serial.println(dustDensityug);
  }

  lcd.setCursor(0,1);         // 1번째, 2라인
  lcd.print("F.Dust");        // fine dust 글자 출력
  lcd.setCursor(7,1);         // 6번째, 2라인
  lcd.print(dustDensityug);   // 미세먼지 출력
  lcd.setCursor(11,1);
  lcd.print("ug/m3");

  delay(1000);
}

/*
 *  이 소스는 에듀이노(Eduino)에 의해서 번역, 수정, 작성되었고 소유권 또한 에듀이노의 것입니다. 
 *  소유권자의 허락을 받지 않고 무단으로 수정, 삭제하여 배포할 시 법적인 처벌을 받을 수 있습니다. 
 *  
 *  에듀이노 미세먼지 키트 기본예제 
 *  - 미세먼지 키트 활용예제 -
 *  미세먼지 측정 센서,온습도센서의 값을 LCD 1602(I2C)와 RGB LED 모듈로 출력하는 예제 코드입니다.
 *    
 */