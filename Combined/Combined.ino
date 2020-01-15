#include<AFMotor.h>
#include <NewPing.h>

#define trigpin1 33
#define trigpin2 34
#define trigpin3 31
#define echopin1 32
#define echopin2 35
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

#define echopin3 30
#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 800 // Maximum distance (in cm) to ping.


LiquidCrystal_I2C lcd(0x27,16,2);

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


int t=0;
int f=0;
int check=0;

int frontd,durfront;
int leftd,durleft;
int rightd,durright;

int t1,t2,t3;

int dist,v;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //turn on the motors
  motor1.setSpeed(50);
  motor2.setSpeed(69);

  motor1.run(RELEASE);
  motor2.run(RELEASE);

  pinMode(trigpin1, OUTPUT);
  pinMode(trigpin2, OUTPUT);
  pinMode(trigpin3, OUTPUT);
  pinMode(echopin1, INPUT);
  pinMode(echopin2, INPUT);
  pinMode(echopin3, INPUT);
  

 
 lcd.init();
 lcd.backlight();

}

void loop() 
{
  // put your main code here, to run repeatedly:
l1=digitalRead(ileftir);
l=digitalRead(leftir);
c=digitalRead(centerir);
r=digitalRead(rightir);
r1=digitalRead(irightir);
n=digitalRead(backir);

  if(l1==0 && l==0 && c==0 && r==0 && r1==0 && n==0)
  {   
       if(l1==0 && l==0 && c==0 && r==0 && r1==0 && n==0)
       {
        forward();
        delay(500);  
       }
       else
       {
    check++;
     }
  }

if(check==0)
{
  forward();

    delay(2000);
}

if(check==5)
{
   t=(t2-t1);
  dist=v*t;
  
    lcd.setCursor(0,0);
    lcd.print("FINISH ");

    lcd.setCursor(8,0);
    lcd.print("NODES=");

    lcd.setCursor(14,0);
    lcd.print(t);

    lcd.setCursor(0,1);
    lcd.print("DISTANCE=");

    lcd.setCursor(10,0);
    lcd.print(dist);
     
  exit(0);
}
  
  if(check==3)
  {
  if(l1==1 && l==1 && c==0 && r==1 && r1==1)
  {
     forward();
  }
  else if((l1==1 && l==1 && c==0 && r==0 && r1==0)|| (l1==1 && l==1 && c==1 && r==1 && r1==0))//sharp right 
  {
    sharpright();
  }
  else if((l1==0 && l==0 && c==0 && r==1 && r1==1)|| (l1==0 && l==1 && c==1 && r==1 && r1==1))// sharp left
  {
    sharpleft();
  }
  else if((l1==1 && l==0 && c==0 && r==1 && r1==1)|| (l1==1 && l==0 && c==1 && r==1 && r1==1)|| (l1==0 && l==0 && c==1 && r==1 && r1==1))// slight left
  {
    slightleft();
  }
  else if((l1==1 && l==1 && c==0 && r==0 && r1==1)|| (l1==1 && l==1 && c==1 && r==0 && r1==1)|| (l1==1 && l==1 && c==1 && r==0 && r1==0)) // slight right
  {
    slightright();
  }
  else if(l1==1 && l==1 && c==1 && r==1 && r1==1)
  {
      reverse();
  }
  else if(l1==1 && l==0 && c==1 && r==0 && r1==1)
  {
    node();
  }
  

 if(check==1 || check==2)
  {
   int fus,rus,lus;
    fus=front();
    rus=right();
    lus=left();

    if(lus==0 && rus<20 && fus>20)
    {
      forward();
    }
    else if(lus==0 && rus>20)
    {
      sharpright();
    }
    else if( rus<20 && fus<20)
    {
      sharpleft();
    }
    else if( lus==0 && fus==0)
    {
      sharpright();
    }
    else if( rus==0 && fus==0)
    {
      sharpleft();
    }
    else if( rus==0 && fus<20)
    {
      sharpleft();
    }
    else if( lus==0 && fus<20)
    {
      sharpleft();
    }
    else if( lus<20 && fus<20)
    {
      sharpright();
    }
    else if( rus==0 && lus>20)
    {
      sharpleft();
    }
    else if( lus<20 && rus==0 && fus>20)
    {
      forward();
    }
    else if( rus==0 && lus==0)  //at the end    
    {
      forward();
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
}

void forward()
{  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  
  //delay(1000);
       
  motor1.setSpeed(85);
  motor2.setSpeed(123);
  
}

void sharpleft()
{  
  
  //delay(1000);

  motor1.run(BACKWARD);
  motor2.run(FORWARD);
       
  motor1.setSpeed(50);
  motor2.setSpeed(130);

  //delay(400);
  
}


void slightleft()
{  
    motor1.run(FORWARD);
    motor2.run(FORWARD);

    motor1.setSpeed(65);
    motor2.setSpeed(120);
  
}


void sharpright()
{  
  

  motor1.run(FORWARD);
  motor2.run(BACKWARD);
       
  motor1.setSpeed(130);
  motor2.setSpeed(90); 

  //delay(250);

  
}

void slightright()
{  
    motor1.run(FORWARD);
    motor2.run(FORWARD);

    motor1.setSpeed(120);
    motor2.setSpeed(80);
  
}

void reverse()
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);

  motor1.setSpeed(0);
  motor2.setSpeed(0);
  
 // delay(1000);

  motor1.run(BACKWARD);
  motor2.run(FORWARD);
       
  motor1.setSpeed(110);
  motor2.setSpeed(140);

// delay(600);
  
}

void node()
{
  if(l1==1 && l==1 && c==1 && r==1 && r1==1)
  {
    t++;
    lcd.setCursor(6,0);
    lcd.print("TRUE NODE");

    t3=millis();

    
    t1=t2;
    t2=t3;
    
    
  }

  if(l1==1 && l==1 && c==0 && r==1 && r1==1)
  {
    f++;
    lcd.setCursor(6,0);
    lcd.print("FALSE NODE");
  }

  if(l1==1 && l==0 && c==1 && r==0 && r1==1)
  {
     forward();
  }
}

int front()
{
  digitalWrite(trigpin1,LOW);
  delay(20);
  digitalWrite(trigpin1,HIGH);
  delay(100);
  digitalWrite(trigpin1,LOW);
  durfront=pulseIn(echopin1,HIGH);
  frontd=(durfront/2)/29.1;
    Serial.print("front:");
  Serial.println(frontd);
  return frontd;
}

int right()
{
  delay(20);
  digitalWrite(trigpin2,HIGH);
  delay(100);
  digitalWrite(trigpin2,LOW);
  durright=pulseIn(echopin2,HIGH);
  rightd=(durright/2)/29.1;
    Serial.print("right:");
  Serial.println(rightd);
  return rightd;
}
int left()
{
  delay(20);
  digitalWrite(trigpin3,HIGH);
  delay(100);
  digitalWrite(trigpin3,LOW);
  durleft=pulseIn(echopin3,HIGH);
  leftd=(durleft/2)/29.1;
  Serial.print("left:");
  Serial.println(leftd);
  return leftd;
}
