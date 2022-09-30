const int temp_trans_pin = A0;
const int heater_pin = 13;
const int fan_pin = 6;

float min_temp = 20, max_temp = 25;

#include <LiquidCrystal.h>
LiquidCrystal lcd(12 ,11 ,5 ,4 ,3 ,2 );

void setup(){
  lcd.begin(16,2);
  pinMode(heater_pin, OUTPUT);
  pinMode(fan_pin, OUTPUT);
  
  lcd.print("Room Temp{C):");
  lcd.setCursor(2,1);
  lcd.print(min_temp); lcd.print("-"); lcd.print(max_temp);
  delay(2000);
}

void loop(){
  float eqv_volt = analogRead(temp_trans_pin) * 5.0/1023;
  float Sensor_temp = eqv_volt*100.0 - 50.0;
  
  lcd.clear();
  lcd.print("Sensor Reading: ");
  lcd.setCursor(2,1);
  lcd.print(Sensor_temp); lcd.print(" C");
  delay(2000);
  
  if (Sensor_temp>max_temp){
    lcd.clear();
    lcd.print("Temp is High!");
    lcd.setCursor(0,1); lcd.print("Turning on Fan!");
    for(int i=0; i<=255; i++){
      analogWrite(fan_pin, i);
    }
    
    delay(2000);
    
    lcd.clear();
    lcd.print("Turning off fan");
    for(int i=255; i>=0; i--){
      analogWrite(fan_pin, i);
    }
    delay(2000);
  }
  else if (Sensor_temp<min_temp){
    lcd.clear();
    lcd.print("Temp is Low!");
    lcd.setCursor(0,1); lcd.print("Turning on Heater!");
    
    digitalWrite(heater_pin, HIGH);
    
    delay(3000);
    
    lcd.clear();
    lcd.print("Turning off Heater");
    
    digitalWrite(heater_pin, LOW);
    
    delay(1000);
  }
  else if(Sensor_temp>min_temp && Sensor_temp<max_temp){
    lcd.clear();
    lcd.print("Temp is normal!");
    lcd.setCursor(2,1);
    lcd.print("Turn of All!");
    delay(1000);
    lcd.clear();
  }
  else{
    lcd.clear();
    lcd.print("something went wrong");
    lcd.setCursor(2,1);
    lcd.print("in the circuit");
    delay(2000);
    lcd.clear();
  }  
  delay(1000);
}