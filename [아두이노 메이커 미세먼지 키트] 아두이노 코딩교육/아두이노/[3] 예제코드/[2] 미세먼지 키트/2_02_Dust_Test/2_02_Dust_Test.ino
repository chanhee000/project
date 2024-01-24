int dust_sensor = A0;                   // 미세먼지 핀 번호
float dust_value = 0;                   // 센서에서 입력받은 미세먼지 값
float dustDensityug=0;                  // ug/m^3 값을 계산

int sensor_led = 12;                    // 미세먼지 센서 안에 있는 적외선 led 핀 번호
int sampling = 280;                     // 적외선 led를 키고, 센서값을 읽어들여 미세먼지를 측정하는 샘플링 시간
int waiting = 40;     
float stop_time = 9680;                 // 센서를 구동하지 않는 시간

float dust_init = 0;
float dust_initial = 0;

void setup(){
  Serial.begin(9600);                   // 시리얼 모니터 시작, 속도는 9600
  pinMode(sensor_led,OUTPUT);           // 미세먼지 적외선 led를 출력으로 설정

  for(int i = 0 ; i < 5 ; i++){         //미세먼지 측정센서 초기 값 구하기 
  digitalWrite(sensor_led, LOW);        //미세먼지 측정 5번하기
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
  digitalWrite(sensor_led, LOW);        // LED 켜기
  delayMicroseconds(sampling);          // 샘플링해주는 시간. 
  dust_value = analogRead(dust_sensor); // 센서 값 읽어오기
  delayMicroseconds(waiting);           // 너무 많은 데이터 입력을 피해주기 위해 잠시 멈춰주는 시간. 
  digitalWrite(sensor_led, HIGH);       // LED 끄기
  delayMicroseconds(stop_time);         // LED 끄고 대기  

  dustDensityug = (((dust_value * (5.0 / 1024)) - dust_initial) /0.005);  // 미세먼지 값 계산
  Serial.print("Dust Density [ug/m^3]: ");  // 시리얼 모니터에 미세먼지 값 출력
  Serial.print(dustDensityug);

  if(dustDensityug <= 30.0){            // 대기 중 미세먼지가 좋음 일때 "Good" 출력
     Serial.print("   ");
     Serial.println("Good");
  }else if(30.0 < dustDensityug && dustDensityug <= 80.0){   // 대기 중 미세먼지가 보통 일때 "Normal" 출력
     Serial.print("   ");
     Serial.println("Normal");    
  }else if (80.0 < dustDensityug && dustDensityug <= 150.0){ // 대기 중 미세먼지가 나쁨 일때 "Bad" 출력
     Serial.print("   "); 
     Serial.println("Bad");        
  }else{                                 // 대기 중 미세먼지가 매우 나쁨 일때 "Warning" 출력
     Serial.print("   ");
     Serial.println("Warning");
  }

  delay(1000);
}

/*
 *  이 소스는 에듀이노(Eduino)에 의해서 번역, 수정, 작성되었고 소유권 또한 에듀이노의 것입니다. 
 *  소유권자의 허락을 받지 않고 무단으로 수정, 삭제하여 배포할 시 법적인 처벌을 받을 수 있습니다. 
 *  
 *  에듀이노 미세먼지 키트 기본예제 
 *  - 미세먼지 센서 사용예제 -    
 *  미세먼지 센서를 사용해서 시리얼 모니터로 확인하는 예제코드 입니다. 
 *   
 */
