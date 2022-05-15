//kode untuk bagian controller + input target dan variabel kendali
//include library
#include <SoftwareSerial.h>
#include <math.h>

//deklarasi variabel

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

//inisialisasi Tx dan Rx yang baru
SoftwareSerial mySerial = SoftwareSerial(5, 6);

//setup baud rate
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  //baca output controller
  if (mySerial.available() > 0) {
    currentCtrl = mySerial.parseFloat(SKIP_ALL, '\n');
  }

  //rumus plant posisi
  //currentOutput = (2*powf(a,2)-20)/(powf(a,2)+7*a+10)*prevOutput - (powf(a,2)-7*a+10)/(powf(a,2)+7*a+10)*prev2Output + 0.75/(powf(a,2)+7*a+10)*currentCtrl + 1.5/(powf(a,2)+7*a+10)*prevCtrl + 0.75/(powf(a,2)+7*a+10)*prev2Ctrl;

  //rumus plant kecepatan
  currentOutput = (1.0/(5.0+a))*((0.9*currentCtrl) + (0.9*prevCtrl) - ((5.0-a)*prevOutput));

  //output sistem dikirim ke serial monitor dan controller
  Serial.println(currentOutput);
  mySerial.println(currentOutput);

  delay(T);
  
  //simpan iterasi sebelumnya
  prev2Ctrl = prevCtrl;
  prevCtrl = currentCtrl;
  prev2Output = prevOutput;
  prevOutput = currentOutput;
}
