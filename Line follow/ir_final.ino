#include<AFMotor.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h> 


AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

int l1=1;
int l=1;
int c=1;
int r=1;
int r1=1;
int n=1;

int ileftir=45;
int leftir=47;
int centerir=49;
int rightir=51;
int irightir=53;
int backir=43;
int bc,wc,rc,rwc=0;

int t=0;
int f=0;
int check=0;

int t1,t2,t3,nt;



LiquidCrystal_I2C lcd(0x27,16,2);


void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);

  //turn on the motors
  motor1.setSpeed(50);
  motor2.setSpeed(69);

  motor1.run(RELEASE);
  motor2.run(RELEASE);

  lcd.init();
lcd.backlight();


}

void loop() {
  // put your main code here, to run repeatedly:
l1=digitalRead(ileftir);
l=digitalRead(leftir);
c=digitalRead(centerir);
r=digitalRead(rightir);
r1=digitalRead(irightir);
n=digitalRead(backir);

if(l1==1 && l==0 && c==1 && r==0 && r1==1)
  {
    if(nt>0)
    {
      nt=0;
    }
    else
    {
    nt=1;
    }

   forward();
    delay(200);
   
    }
 
    
 if(nt==1)
 {

  if(l1==1 && l==1 && c==1 && r==1 && r1==1 && nt==1)
  { 
     t++;
    lcd.setCursor(6,0);
    lcd.print("TRUE NODE");
    Serial.print("TRUE NODE");

    t3=millis();

    
    t1=t2;
    t2=t3;

    forward();
    
    delay(200);

    
  }
  else if(l1==1 && l==1 && c==0 && r==1 && r1==1 && nt==1)
  { 
    f++;
    lcd.setCursor(6,0);
    lcd.print("FALSE NODE");
    Serial.print("FALSE NODE");

    forward();

    delay(200);

    
  }
 }
 else
  {
      if(l1==1 && l==1 && c==0 && r==1 && r1==1)
  {
     forward();
  }
  else if((l1==1 && l==1 && c==0 && r==0 && r1==0)|| (l1==1 && l==1 && c==1 && r==1 && r1==0))//sharp right 
  {
    sharpright();
    delay(200);
  }
  else if((l1==0 && l==0 && c==0 && r==1 && r1==1) || (l1==0 && l==1 && c==1 && r==1 && r1==1))// sharp left
  {
    sharpleft();
    delay(200);
  }
  else if((l1==1 && l==0 && c==0 && r==1 && r1==1)|| (l1==1 && l==0 && c==1 && r==1 && r1==1)|| (l1==0 && l==0 && c==1 && r==1 && r1==1))// slight left
  {
    slightleft();
  }
  else if((l1==1 && l==1 && c==0 && r==0 && r1==1)|| (l1==1 && l==1 && c==1 && r==0 && r1==1)|| (l1==1 && l==1 && c==1 && r==0 && r1==0)) // slight right
  {
    slightright();
  }
  else if(l1==1 && l==1 && c==0 && r==1 && r1==0)
  {
    sharpright();
    delay(400);
  }
  else if(l1==0 && l==0 && c==0 && r==0 && r1==0)
  {
      sharpleft();
      delay(200);
  }
  else if(l1==1 && l==1 && c==1 && r==1 && r1==1)
  {
      reverse();
  }
  
  
  
}

lcd.setCursor(1,1);
  lcd.print("TRUE=");



  
  lcd.setCursor(6,1);
  lcd.print(t);

  
  lcd.setCursor(8,1);
  lcd.print("FALSE=");

  
  lcd.setCursor(14,1);
  lcd.print(f);
}

void forward()
{  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  
        
  motor1.setSpeed(85);
  motor2.setSpeed(111);
  
}

void sharpleft()
{  
  
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
       
  motor1.setSpeed(98);
  motor2.setSpeed(120);

  
  
}


void slightleft()
{  
    motor1.run(FORWARD);
    motor2.run(FORWARD);

    motor1.setSpeed(70);
    motor2.setSpeed(110);
  
}


void sharpright()
{  
  
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
       
  motor1.setSpeed(105);
  motor2.setSpeed(120); 

  
  
}

void slightright()
{  
    motor1.run(FORWARD);
    motor2.run(FORWARD);

    motor1.setSpeed(100);
    motor2.setSpeed(100);
  
}

void reverse()
{
 
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
       
  motor1.setSpeed(80);
  motor2.setSpeed(100);

  
}
