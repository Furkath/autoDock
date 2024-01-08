int redPin=11;
int greenPin=10;
int bluePin=6;
int s2=7;
int s3=8;
int outPin=4;
int rColorStrength;
int gColorStrength;
int bColorStrength;
unsigned int pulseWidth;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(redPin,OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(bluePin,OUTPUT);
pinMode(s2,OUTPUT);
pinMode(s3,OUTPUT);
pinMode(outPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(s2,LOW);
digitalWrite(s3,LOW);
pulseWidth=pulseIn(outPin,LOW);
rColorStrength=pulseWidth/10.;
rColorStrength=(255-rColorStrength);

digitalWrite(s2,HIGH);
digitalWrite(s3,HIGH);
pulseWidth=pulseIn(outPin,LOW);
gColorStrength=pulseWidth/10.;
gColorStrength=(255-gColorStrength);

digitalWrite(s2,LOW);
digitalWrite(s3,HIGH);
pulseWidth=pulseIn(outPin,LOW);
bColorStrength=pulseWidth/10.;
bColorStrength=(255-bColorStrength);

Serial.print(rColorStrength);
Serial.print(",");
Serial.print(gColorStrength);
Serial.print(",");
Serial.print(bColorStrength);
Serial.print("\n");

if(rColorStrength>gColorStrength && gColorStrength>bColorStrength){
  rColorStrength=255;
  gColorStrength=gColorStrength/2;
  bColorStrength=0;
}

if(rColorStrength>bColorStrength && bColorStrength>gColorStrength){
  rColorStrength=255;
  bColorStrength=bColorStrength/4;
  gColorStrength=0;
}

if(gColorStrength>rColorStrength && rColorStrength>bColorStrength){
  gColorStrength=255;
  rColorStrength=0;
  bColorStrength=0;
}

if(gColorStrength>bColorStrength && bColorStrength>rColorStrength){
  gColorStrength=255;
  bColorStrength=bColorStrength/10;
  rColorStrength=0;
}

if(bColorStrength>rColorStrength && rColorStrength>gColorStrength){
  bColorStrength=255;
  rColorStrength=rColorStrength/2;
  gColorStrength=0;
}

if(bColorStrength>gColorStrength && gColorStrength>rColorStrength){
  bColorStrength=255;
  gColorStrength=gColorStrength/2;
  rColorStrength=0;
}Serial.print(rColorStrength);
Serial.print(",");
Serial.print(gColorStrength);
Serial.print(",");
Serial.print(bColorStrength);
Serial.print("\n");
analogWrite(redPin,rColorStrength);
analogWrite(greenPin,gColorStrength);
analogWrite(bluePin,bColorStrength);
delay(250);
}
