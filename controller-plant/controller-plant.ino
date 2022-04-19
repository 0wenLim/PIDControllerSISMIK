int input = 0;
int i = 0;

String bacaan;

float Kp = 157.32;
float Kd = 12;
float Ki = 10;
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

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    bacaan = Serial.readString();
    input = bacaan.toInt();
  }
  
  currentErr = (float)input - prevOutput;
  currentCtrl = (1/a)*((a*Kp+Ki+pow(a,2)*Kd)*currentErr + 2*(Ki-pow(a,2)*Kd)*prevErr + (pow(a,2)*Kd-a*Kp+Ki)*prev2Err + a*prev2Ctrl) ;
  
  //kendali posisi
  currentOutput = (2*pow(a,2)-20)/(pow(a,2)+7*a+10)*prevOutput - (pow(a,2)-7*a+10)/(pow(a,2)+7*a+10)*prev2Output + 0.75/(pow(a,2)+7*a+10)*currentCtrl + 1.5/(pow(a,2)+7*a+10)*prevCtrl + 0.75/(pow(a,2)+7*a+10)*prev2Ctrl;

  //kendali kecepatan
  //currentOutput = (1/(a+5))*(0.9*currentCtrl - 0.9*prevCtrl + (5-1)*prevOutput);

  Serial.print(input);
  Serial.print(" ");
  Serial.println(currentOutput);

  delay(T);
  
  prev2Err = prevErr;
  prevErr = currentErr;

  prev2Ctrl = prevCtrl;
  prevCtrl = currentCtrl;

  prev2Output = prevOutput;
  prevOutput = currentOutput;

}
