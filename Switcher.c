#include <Servo.h>
// create servo object to control a servo
Servo servo1;
Servo servo2;
Servo servo3;
// Time condition of switch in miliseconds
int timec = 2000;
// Time setting
unsigned long previousMillis=0;
// Receiver Outputs to Servos
int Rc1 = 2; // switch signal
int Rc2 = 3; // RPM (9)
int Rc3 = 4; // Horizontal Servo (10)
int Rc4 = 5; // Tlt motor (11)
//SoftwareSerial mySerial(7, 8); // RX, TX
void setup()
{
Serial.begin(115200);
// Servos Outputs
servo1.attach(9);
servo2.attach(10);
servo3.attach(11);
// Setting the Input and Output in the ports
pinMode(Rc1, INPUT);
pinMode(Rc2, INPUT);
pinMode(Rc3, INPUT);
pinMode(Rc4, INPUT);
// Now set up two tasks to run independently.
}
// Case value
int a;
volatile int s1 ;
volatile int s2 ;
volatile int s3 ;
volatile int s4 ;
int data[15];
int k1;
int k2;
int k3;
int k4;
int r1;
int r2;
int r3;
int r4;
int i;
void loop(){
volatile int currentMillis= millis();
s1 = pulseIn(Rc1,HIGH); // switch 1100<s1<900
s2 = pulseIn(Rc2,HIGH); // switch 1100<s1<900
s3 = pulseIn(Rc3,HIGH); // switch 1100<s1<900
s4 = pulseIn(Rc4,HIGH); // switch 1100<s1<900
if (s1<=1200){
if ((currentMillis - previousMillis) >= timec) {
// Reset timing
a=1;
}}
else if (s1>=1800){
if ((currentMillis - previousMillis) >= timec) {
a=2;
}}
else { Serial.println(a); previousMillis=currentMillis;}
switch (a) {
//Remote controller
case 1:
Serial.print("principal motor power "); Serial.print(( s2-1000)*.1);
Serial.print(" %, Servo Angle "); Serial.print( (s3-1000)*.1); Serial.print("
% , Lateral motor power "); Serial.print((s4-1000)*.1); Serial.print(" % ");
servo1.write(s2); // micros for rpm 1000-2000
servo2.write(s3*2-1500); // micros for rpm 1000-2000
servo3.write(s4); // milli for servo 0-180 (1000-2000)
break;
//Workstation, another controller
case 2:
if (Serial.available() > 3)
{
for (int i=0; i < 9 ; i++)
{
data[i] = Serial.read();
}
Serial.flush();
}
String string1= String(data[0]-48);
String string2= String(data[1]-48);
String string3;
String string4= String(data[3]-48);
String string5= String(data[4]-48);
String string6;
String string7= String(data[6]-48);
String string8= String(data[7]-48);
String string9;
string3=string1+string2;
string6=string4+string5;
string9=string7+string8;
r1= string3.toInt();
r2= string6.toInt();
r3= string9.toInt();
if (r1>=0 ){
k1= r1;}
if( r2>=0){
k2= r2;}
if( r3>=0){
k3= r3;}
Serial.print(k1); Serial.print("% "); Serial.print(k2); Serial.print("% ");
Serial.print(k3); Serial.print("% ");
servo1.write(1000*k1/100+1000); // micros for rpm 1000-2000
servo2.write(1000*k2/100+1000); // micros for rpm 1000-2000
servo3.write(1000*k3/100+1000); // milli for servo 1000-2000
}}