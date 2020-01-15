#include <NewPing.h>
#include<AFMotor.h>

#define trigpin3 25
#define echopin3 23
#define trigpin2 34
#define echopin2 23


#define SONAR_NUM 2     // Number of sensors.
#define MAX_DISTANCE 800 // Maximum distance (in cm) to ping.
int leftd,durleft,lus;
int frontd,durfront,fus;


AF_DCMotor motor1(1);
AF_DCMotor motor2(2);



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  motor1.run(RELEASE);
  motor2.run(RELEASE);

  //turn on the motors
  motor1.setSpeed(50);
  motor2.setSpeed(69);

  
  pinMode(trigpin3, OUTPUT);
  pinMode(echopin3, INPUT);
  pinMode(trigpin2, OUTPUT);
  pinMode(echopin2, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

lus=left();
fus=front();

 if(fus<20)
 {
  sharpright();
 }
 else if(lus>15 && lus<25)
 {
  forward();
 }
  
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

void forward()
{  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  
  //delay(1000);
       
  motor1.setSpeed(85);
  motor2.setSpeed(123);
  
}

void sharpright()
{  

  motor1.run(FORWARD);
  motor2.run(BACKWARD);
       
  motor1.setSpeed(130);
  motor2.setSpeed(90); 

  delay(250);

  
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
