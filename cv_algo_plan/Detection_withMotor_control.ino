int trigpinfront=13;
int echopinfront=A1;
int trigpinback=12;
int echopinback=A2;
int trigpinside1=8;
int echopinside1=A3;
int trigpinside2=7;
int echopinside2=A4;

float pintimefront;
float pintimeback;
float pintimeside1;
float pintimeside2;
float distance1;
float distance2;
float distance3;
float distance4;
float speedofsound=34000;
int In1=11;
int In2=10;
int left1=5;
int left2=3;
int right1=9;
int right2=6;
int direc;
int value;

int evidence=0;

void setup() {
  Serial.begin(9600);
  pinMode(In1,OUTPUT);
  pinMode(In2,OUTPUT);
  pinMode(left1,OUTPUT);
  pinMode(left2,OUTPUT);
  pinMode(right1,OUTPUT);
  pinMode(right2,OUTPUT);
    pinMode(trigpinfront,OUTPUT);
  pinMode(echopinfront,INPUT);
    pinMode(trigpinback,OUTPUT);
  pinMode(echopinback,INPUT);
    pinMode(trigpinside1,OUTPUT);
  pinMode(echopinside1,INPUT);
    pinMode(trigpinside2,OUTPUT);
  pinMode(echopinside2,INPUT);
  
  // put your setup code here, to run once:

}

void loop() {
if (evidence<4)
{
  digitalWrite(trigpinfront,LOW);
  delayMicroseconds(2000);
  digitalWrite(trigpinfront,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpinfront,LOW);
  delayMicroseconds(10);

  pintimefront=pulseIn(echopinfront,HIGH);
  pintimefront=pintimefront/1000000;
  distance1=speedofsound*pintimefront/2;

  Serial.print("The distance from the front to the obstacle: ");
  Serial.print(distance1);
  Serial.println("cm");
}
  if (evidence<2)
  {
  digitalWrite(left1,LOW);
  digitalWrite(left2,HIGH);
  digitalWrite(right1,LOW);
  digitalWrite(right2,HIGH);
  }
  
  if(evidence==0)
  {
    if(distance1<5.2)
    {
  digitalWrite(left1,LOW);
  digitalWrite(left2,LOW);
  digitalWrite(right1,LOW);
  digitalWrite(right2,LOW);
    
    digitalWrite(In1,LOW);
    digitalWrite(In2,HIGH);
    delay(4000);
    digitalWrite(In1,LOW);
    digitalWrite(In2,LOW);
    
  digitalWrite(left1,LOW);
  digitalWrite(left2,HIGH);
  digitalWrite(right1,LOW);
  digitalWrite(right2,HIGH);
  delay(1500);
    
    digitalWrite(In1,HIGH);
    digitalWrite(In2,LOW);
    delay(5000);
    digitalWrite(In1,LOW);
    digitalWrite(In2,LOW);
    evidence=1;
    }
  }
  if(evidence==1)
  {
  digitalWrite(trigpinback,LOW);
  delayMicroseconds(2000);
  digitalWrite(trigpinback,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpinback,LOW);
  delayMicroseconds(10);

  pintimeback=pulseIn(echopinback,HIGH);
  pintimeback=pintimeback/1000000;
  distance2=speedofsound*pintimeback/2;

  Serial.print("The distance from the back to the obstacle: ");
  Serial.print(distance2);
  Serial.println("cm");
  if(distance1<75 && distance1>30 && distance2<10)
  {
    Serial.println("now ready to adjust the direction and approach the turning position");
    evidence=2;
  }
  }

  if(evidence==2)
  {
  digitalWrite(trigpinside1,LOW);
  delayMicroseconds(2000);
  digitalWrite(trigpinside1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpinside1,LOW);
  delayMicroseconds(10);

  pintimeside1=pulseIn(echopinside1,HIGH);
  pintimeside1=pintimeside1/1000000;
  distance3=speedofsound*pintimeside1/2;

  Serial.print("The distance from the side1(front) to the side plate: ");
  Serial.print(distance3);
  Serial.println("cm");

  digitalWrite(trigpinside2,LOW);
  delayMicroseconds(2000);
  digitalWrite(trigpinside2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpinside2,LOW);
  delayMicroseconds(10);

  pintimeside2=pulseIn(echopinside2,HIGH);
  pintimeside2=pintimeside2/1000000;
  distance4=speedofsound*pintimeside2/2;

  Serial.print("The distance from the side2(back) to the side plate: ");
  Serial.print(distance4);
  Serial.println("cm");

  if(distance3-distance4>1)
  {
    Serial.println("The tank is towards left.");
    Serial.println("Now motors shoul do some right turning, but so far just type any to continue:");
   // while (Serial.available()==0){}
   // while(Serial.available()!=0)
   //  {
   //    int meiyongde=Serial.read();
   //  }
     digitalWrite(left1,LOW);
     digitalWrite(left2,HIGH);
     digitalWrite(right1,HIGH);
     digitalWrite(right2,LOW);  
     delay(100);
     
  }
   else if(distance3-distance4<-1)
  {
    Serial.println("The tank is towards right.");
    Serial.println("Now motors shoul do some left turning, but so far just type any to continue:");
    //while (Serial.available()==0){}
    //while(Serial.available()!=0)
    //{
    //  int meiyongde=Serial.read();
    //}
     digitalWrite(left1,HIGH);
     digitalWrite(left2,LOW);
     digitalWrite(right1,LOW);
     digitalWrite(right2,HIGH);
     delay(100);
  }
  else
  {
   Serial.println("The tank is at the right position.");
   Serial.println("Now motors shoul go ahead, but so far just type any to continue:");
   // while (Serial.available()==0){}
   // while(Serial.available()!=0)
   //{
   //   int meiyongde=Serial.read();
   //}
     digitalWrite(left1,LOW);
     digitalWrite(left2,HIGH);
     digitalWrite(right1,LOW);
     digitalWrite(right2,HIGH);
     delay(100);
   // before you advance further, check whether this is the turning position.
   
   
   
   if(distance1<26)
   {
   // Serial.println("It now should start turning and then go under through the 9cm cover!");
   // Serial.println("Now the process should be over, but you can type any going on to test before incline cases.");
   // while (Serial.available()==0){}
   // while(Serial.available()!=0)
   // {
   //  int meiyongde=Serial.read();
   //}
    evidence=3;
   }
  }
  }
  if(evidence==3)
  {
     digitalWrite(left1,HIGH);
     digitalWrite(left2,LOW);
     digitalWrite(right1,LOW);
     digitalWrite(right2,HIGH);
     delay(3200);
     evidence=4;
    //while (1)
    //{
    //this part now can be used to guid the tank to park
    //}
  }

  if(evidence==4)
  {
  digitalWrite(trigpinback,LOW);
  delayMicroseconds(2000);
  digitalWrite(trigpinback,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpinback,LOW);
  delayMicroseconds(10);

  pintimeback=pulseIn(echopinback,HIGH);
  pintimeback=pintimeback/1000000;
  distance2=speedofsound*pintimeback/2;

  digitalWrite(trigpinside1,LOW);
  delayMicroseconds(2000);
  digitalWrite(trigpinside1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpinside1,LOW);
  delayMicroseconds(10);

  pintimeside1=pulseIn(echopinside1,HIGH);
  pintimeside1=pintimeside1/1000000;
  distance3=speedofsound*pintimeside1/2;

 // Serial.print("The distance from the side1(front) to the side plate: ");
 //Serial.print(distance3);
 // Serial.println("cm");

  digitalWrite(trigpinside2,LOW);
  delayMicroseconds(2000);
  digitalWrite(trigpinside2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpinside2,LOW);
  delayMicroseconds(10);

  pintimeside2=pulseIn(echopinside2,HIGH);
  pintimeside2=pintimeside2/1000000;
  distance4=speedofsound*pintimeside2/2;

  //Serial.print("The distance from the side2(back) to the side plate: ");
  //Serial.print(distance4);
  //Serial.println("cm");


 if(distance2>70)
  {
    evidence=5;
  }
  else if(distance3-distance4>0.75)
  {
   //Serial.println("The tank is towards left.");
   //Serial.println("Now motors shoul do some right turning, but so far just type any to continue:");
   // while (Serial.available()==0){}
   // while(Serial.available()!=0)
   //  {
   //    int meiyongde=Serial.read();
   //  }
     digitalWrite(left1,LOW);
     digitalWrite(left2,HIGH);
     digitalWrite(right1,HIGH);
     digitalWrite(right2,LOW);  
     delay(100);
     
  }
   else if(distance3-distance4<-0.75)
  {
    //Serial.println("The tank is towards right.");
    //Serial.println("Now motors shoul do some left turning, but so far just type any to continue:");
    //while (Serial.available()==0){}
    //while(Serial.available()!=0)
    //{
    //  int meiyongde=Serial.read();
    //}
     digitalWrite(left1,HIGH);
     digitalWrite(left2,LOW);
     digitalWrite(right1,LOW);
     digitalWrite(right2,HIGH);
     delay(100);
  }
  else
  {
     digitalWrite(left1,LOW);
     digitalWrite(left2,HIGH);
     digitalWrite(right1,LOW);
     digitalWrite(right2,HIGH);
     delay(100);
  }
  }

  if (evidence==5)
  {
    
  digitalWrite(trigpinside2,LOW);
  delayMicroseconds(2000);
  digitalWrite(trigpinside2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpinside2,LOW);
  delayMicroseconds(10);

  pintimeside2=pulseIn(echopinside2,HIGH);
  pintimeside2=pintimeside2/1000000;
  distance4=speedofsound*pintimeside2/2;
    
      if(distance4>100)
     {
     digitalWrite(left1,LOW);
     digitalWrite(left2,HIGH);
     digitalWrite(right1,LOW);
     digitalWrite(right2,HIGH);
     delay(3200);
     digitalWrite(left1,HIGH);
     digitalWrite(left2,LOW);
     digitalWrite(right1,LOW);
     digitalWrite(right2,HIGH);
     delay(3300);
     digitalWrite(left1,LOW);
     digitalWrite(left2,HIGH);
     digitalWrite(right1,LOW);
     digitalWrite(right2,HIGH);
     delay(12000);
     
     digitalWrite(left1,LOW);
     digitalWrite(left2,LOW);
     digitalWrite(right1,LOW);
     digitalWrite(right2,LOW);
     while(1)
     {
      
     }
  }
  }
  
}