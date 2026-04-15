
#include <LiquidCrystal.h>

#include <Servo.h>


int rs = 2;
int en =10;
int d4 =4;
int d5 = 5;
int d6 = 6;
int d7=7;
int greenpin = 11;
int redpin = 9;
int pospin = A2;
int speedpin  = 3  ;
int clockpin =8;
int latchpin = 12;
int buzzpin = A1;
int datapin = 13;
int potpin = A0;
int clutch = A5;
int butup = A3;
int butdown = A4;
int clutchval;
int butupval;
int butdownval;
int gear = 0;
int potval;
int throttle;
int count =0;
int rtm=0; 
int speed;
int servopos=0;
byte leds = 0x01;
enum LaunchState {IDLE,ARMED,LAUNCHING };
LaunchState launchState = IDLE;
int launchTimer = 0;
int previousMillisLCD = 0;
int previousMillisSerial = 0;

Servo myservo;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void setup() {
  lcd.begin(16,2);
  pinMode(A1,OUTPUT);
  myservo.attach(pospin);
  pinMode(clockpin,OUTPUT);
  pinMode(latchpin,OUTPUT);

  pinMode(datapin,OUTPUT);
  pinMode(potpin,INPUT);
  Serial.begin(9600);
  pinMode(clutch,INPUT);
  pinMode(butup,INPUT);
  pinMode(speedpin,OUTPUT);
  pinMode(butdown,INPUT);
  digitalWrite(clutch,HIGH);
  digitalWrite(butup,HIGH);
  digitalWrite(butdown,HIGH);
  myservo.write(servopos);
  randomSeed(analogRead(0));
}

void loop() {

 
 analogWrite(greenpin,255);
 analogWrite(redpin,0);

//REGISTERS AND LEDS
  digitalWrite(latchpin,LOW);
  shiftOut(datapin,clockpin,LSBFIRST,leds);
  digitalWrite(latchpin,HIGH);

//POTENTIOMETER
  potval = analogRead(potpin);
  throttle = (100.0/1023)*potval;

  rtm = throttle*gear*20+random(0,300);
  if(gear==0)
    rtm=0;
  speed = rtm/35;


//buttons
  clutchval = digitalRead(clutch);
  butupval = digitalRead(butup);
  butdownval = digitalRead(butdown);
  if(clutchval==0 && (butdownval==1 || butupval==1)){
    if(butdownval==0){
      if(gear!=1 && gear !=0){
      if(rtm>8500){
        lcd.clear();
        delay(5);
        lcd.print("REV MATCH DENIED");
        analogWrite(greenpin,0);
        analogWrite(redpin,255);
        delay(1000);
        lcd.clear();
        delay(5);
      }
      else{
      gear--;

      servopos-=20;
      myservo.write(servopos);
      analogWrite(redpin,255);
      analogWrite(greenpin,100);
      digitalWrite(buzzpin,HIGH);
      delay(100);
      digitalWrite(buzzpin,LOW);
      
      leds = leds /2;
      lcd.clear();
      delay(5);
      lcd.print("Shift Ok");
      delay(400);
      lcd.clear();
      delay(5);

      while(butdownval!=1){
        butdownval = digitalRead(butdown);
      }
      }
      }
    else if(gear==1){
      leds=0x01;
      gear--;
    }

    }
    
    else if(butupval==0){
      if(gear!=7){
      gear++;
      servopos+=20;
      myservo.write(servopos);
      analogWrite(redpin,255);
      analogWrite(greenpin,100);
      digitalWrite(buzzpin,HIGH);
      delay(60);
      digitalWrite(buzzpin,LOW);
       
      leds = leds*2;
      lcd.clear();
      delay(5);
      lcd.print("Shift Ok");
      delay(400);
      lcd.clear();
      delay(5);
      while(butupval!=1){
        butupval = digitalRead(butup);
      }
      } 
    }
  }
  else if(clutchval==1 && (butupval==0 || butdownval==0)){
    digitalWrite(buzzpin,HIGH);
    lcd.clear();
    delay(5);
    lcd.print("MISS SHIFT");
    delay(1000);
    lcd.clear();
    delay(5);
    digitalWrite(buzzpin,LOW);
  }
  else if(clutchval==0 && butupval==0 && butdownval==0){
    if(count==0)
      count =millis();
    if(millis()-count>=2100){
      launchState =ARMED;
      analogWrite(redpin,255);
      analogWrite(greenpin,0);
      digitalWrite(buzzpin,HIGH);
      lcd.clear();
      delay(5);
      lcd.print("LAUNCH ARMED");
      lcd.setCursor(0, 1);
      lcd.print("RTM:8000");
      delay(2000);
      lcd.clear();
      delay(5);
      digitalWrite(buzzpin,LOW);
      count=0;
  }}

  //Launch
    if(launchState == ARMED && clutchval==1){
      gear=1;
      servopos=20;
      myservo.write(20);
      leds=0x02;
      launchState=LAUNCHING;
      launchTimer = millis();
      digitalWrite(buzzpin,HIGH);
      delay(60);
      digitalWrite(buzzpin,LOW);
      lcd.clear();
      delay(5);
      lcd.print("Launching!");
      lcd.setCursor(0, 1);
      lcd.print("GOOO!!!");
      delay(800);
      lcd.clear();
      delay(5);
    }



//lcd
  if(millis()- previousMillisLCD >=200){
    previousMillisLCD = millis();
    lcd.setCursor(0, 0);
    lcd.print("Gear:");
    if(gear==0) lcd.print("N ");
    else lcd.print(gear);
    lcd.print(" RPM:");
    if(rtm<10000) lcd.print(" ");
    if(rtm<1000)  lcd.print(" ");
    if(rtm<100)   lcd.print(" ");
    if(rtm<10)    lcd.print(" ");
    lcd.print(rtm);
    lcd.setCursor(0,1);
    lcd.print("Thr: ");
    lcd.print(throttle);
    lcd.print("%");
    lcd.print(" Spd:");
    if(speed<100) lcd.print(" ");
    if(speed<10)  lcd.print(" ");
    lcd.print(speed);
       }
//dc motor dyno
  int dynospeed;
  if(launchState == LAUNCHING){
    float progress = (millis()-launchTimer) / 1500.0;
    if(progress>1.0){
      progress=1.0;
      launchState = IDLE;
    }
  dynospeed= 50 + (int)(205*progress);
  }
  else if(gear==0){
    dynospeed=0;
  }
  else{
    dynospeed =  50 + (rtm * 205.0) / 14000;;
  }
  if(dynospeed>255)
    dynospeed=255;
  analogWrite(speedpin,dynospeed);

//Serial
  if(millis()-previousMillisSerial>=300){
    previousMillisSerial=millis();
    Serial.print("Gear:");
    Serial.print(gear);
    Serial.print(" | RPM:");
    Serial.print(rtm);
    Serial.print(" | Speed:");
    Serial.print(speed);
    Serial.print(" | Throttle:");
    Serial.print(throttle);
    Serial.print(" | Launch:");
    Serial.print(launchState == IDLE ? "OFF" : "ON");
    Serial.print(" | Dynospeed:");
    Serial.println(dynospeed);
  }
}



