#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal.h>
#include<String.h>
#define buzzer 10
#define echo 11
#define trigger 12
#define redLED 8
#define greenLED 9

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);  
  pinMode(redLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  digitalWrite(redLED,HIGH);
  digitalWrite(greenLED,HIGH);

  lcd.setCursor(0,0);
  lcd.print("  A Project By : ");
  lcd.setCursor(0,1);
  lcd.print("------TEAM------");
  
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("----------------");
  lcd.setCursor(0,1);
  lcd.print("Social Defenders");

  delay(2000);

  for(int r=1;r<=2;r++)
  {
    tone(buzzer,3125,100);
    delay(150);
  }

  delay(1000);
  
  digitalWrite(redLED,LOW);
  digitalWrite(greenLED,LOW);
  
  mlx.begin();  
  lcd.clear();
}
void loop() 
{

  long duration,centimeters,in;

  digitalWrite(trigger,HIGH);
  delayMicroseconds(5);
  digitalWrite(trigger,LOW);

  duration=pulseIn(echo,HIGH);
  centimeters=milliSecToCentimeter(duration);
  
  delay(495);
  if(centimeters <= 3 )
  {
    float temp;
    int length1;
    temp = mlx.readObjectTempF();
    temp += 5;
    
    lcd.clear();  
    lcd.setCursor(0,0);

    //lcd.print("Ambient="); lcd.print(mlx.readAmbientTempC()); lcd.print("*C");
    lcd.print("Body Temperature");
    
    
  
    digitalWrite(redLED,HIGH);
    digitalWrite(greenLED,LOW);
    lcd.setCursor(4,1);
    
    lcd.print(temp); lcd.print("*F");
    Serial.print(length1);
    //Serial.print(temp);
    
    
    if(temp>=99.00 or temp>=99 or temp>=99.0)
    {
      lcd.setCursor(0,0);
      lcd.print("    ALERT!!      ");
      digitalWrite(greenLED,LOW);
      for(int r=1;r<=60;r++)
      {
        tone(buzzer,3125,100);
        delay(130);
      }
    }
    else
    {
      tone(buzzer,3125,250);
    }
    delay(3000);
  }
  else
  {
    digitalWrite(greenLED,HIGH);
    digitalWrite(redLED,LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ambient="); lcd.print(mlx.readAmbientTempC()); lcd.print("*C");
    lcd.setCursor(0,1);
    lcd.print("  Not Detected  ");
  }
  Serial.println();
}
long milliSecToCentimeter(long m)
{
  return m/29/2;
}
