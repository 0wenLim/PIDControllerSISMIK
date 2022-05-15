#include <SoftwareSerial.h>
#include <math.h>

float input = 0;
String bacaan;

float Kp = 10;
float Kd = 0.1;
float Ki = 5;
float T = 0.02;
float a = 2/T;

float currentErr = 0;
float prevErr = 0;
float prev2Err = 0;

float currentCtrl = 0;
float prevCtrl = 0;
float prev2Ctrl = 0;

float currentOutput = 0;
float prevOutput = 0;
float prev2Output = 0;

SoftwareSerial mySerial = SoftwareSerial(5, 6);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.parseFloat(SKIP_ALL, '\n');
  }
  
  if (mySerial.available() > 0) {
    currentOutput = mySerial.parseFloat(SKIP_ALL, '\n');
  }
  
  currentErr = input - prevOutput;
  currentCtrl = (1.0/a)*((a*Kp+Ki+powf(a,2)*Kd)*currentErr + 2.0*(Ki-powf(a,2)*Kd)*prevErr + (powf(a,2)*Kd-a*Kp+Ki)*prev2Err + a*prev2Ctrl) ;
  
  Serial.println(input);
  mySerial.println(currentCtrl);
 
  delay(T);
  
  prev2Err = prevErr;
  prevErr = currentErr;

  prev2Ctrl = prevCtrl;
  prevCtrl = currentCtrl;

  prev2Output = prevOutput;
  prevOutput = currentOutput;

}
