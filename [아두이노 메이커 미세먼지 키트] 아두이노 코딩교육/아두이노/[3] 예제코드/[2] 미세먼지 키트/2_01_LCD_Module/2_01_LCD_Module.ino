#include <Wire.h>                   // i2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C.h>      // LCD 1602 I2C용 라이브러리
LiquidCrystal_I2C lcd(0x27, 16, 2); // 접근주소: 0x3F or 0x27

void setup()
{
  lcd.init();                       // LCD 초기화
}

void loop()
{
  lcd.backlight();                  // 백라이트 켜기
  lcd.setCursor(0, 0);              // 0번째, 0라인
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);              // 1번째, 1라인
  lcd.print("Enjoy eduino!");
}

/*
 *  이 소스는 에듀이노(Eduino)에 의해서 번역, 수정, 작성되었고 소유권 또한 에듀이노의 것입니다. 
 *  소유권자의 허락을 받지 않고 무단으로 수정, 삭제하여 배포할 시 법적인 처벌을 받을 수 있습니다.   
 *  LCD 1602(I2C)를 이용한 문자출력 예제 입니다. 
 *  lcd.print(""); 부분이 문자 출력 구간이며, 
 *  문자를 수정하여 출력이 가능합니다.
 *  
 */