#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// Pins
#define MOTOR 5
#define SENSOR 2
#define SW1 3     
#define SW2 4     

#define motor1_frd 6
#define motor1_rev 7
#define PWM 9

int count = 0;
bool lastSensorState = HIGH;

void setup()
{
  pinMode(MOTOR, OUTPUT);
  pinMode(SENSOR, INPUT);

  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);

  digitalWrite(MOTOR, HIGH); 
  pinMode(MOTOR, OUTPUT);

  pinMode(motor1_frd, OUTPUT);
  pinMode(motor1_rev, OUTPUT);

  digitalWrite(motor1_frd,LOW);
  digitalWrite(motor1_rev,LOW);
  analogWrite(PWM,200);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("CLOTH CUTTER");
  lcd.setCursor(0,1);
  lcd.print("READY...");
  delay(2000);
  lcd.clear();
  updateLCD();
      
}

void loop()
{

  if(digitalRead(SW1) == LOW)
  {
    digitalWrite(MOTOR, HIGH);
    delay(250); 
  }


  if(digitalRead(SW2) == LOW)
  {
    digitalWrite(MOTOR, LOW);
    delay(250);
  }

  bool sensorState = digitalRead(SENSOR);

  if(lastSensorState == HIGH && sensorState == LOW)
  {
    count++;           
    updateLCD();
    delay(300);   
    if(count>=10)
    {
      count=0;digitalWrite(MOTOR, LOW);
      digitalWrite(motor1_frd,HIGH);
      digitalWrite(motor1_rev,LOW);delay(1000);
      digitalWrite(motor1_frd,LOW);
      digitalWrite(motor1_rev,LOW);delay(500);
      digitalWrite(motor1_frd,LOW);
      digitalWrite(motor1_rev,HIGH);delay(1000);
      digitalWrite(motor1_frd,LOW);
      digitalWrite(motor1_rev,LOW);delay(500);
      
      updateLCD();
    }
  }

  lastSensorState = sensorState;
}

void updateLCD()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CLOTH CUTTER");

  lcd.setCursor(0,1);
  lcd.print("COUNT:");
  lcd.print(count);
  lcd.print(" mts");
}
