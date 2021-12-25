#include <BluetoothSerial.h>
#include <Servo.h>
#include <Stepper.h> //匯入函式庫
Servo myservo;  // 建立伺服馬達控制
BluetoothSerial BT;
//int signalPin = 23; //用來trigger及接收echo
//long duration, cm, inches;

const int servoPin = 25;  //用常態變數設定pin腳位，與之前define方式差不多
int pos = 90; //角度初始在中間，設定為90度

const int stepsPerRevolution = 2048;  //此馬達轉一圈為2048步
const int RPM = 5; //馬達旋轉速度
//宣告Stepper物件，的步數和引腳
//引角依序對應驅動版的1N1、1N3、1N2、1N4
Stepper myStepper(stepsPerRevolution, 13, 14, 12, 27);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  BT.begin("HI-Bitch");//請改名

  myservo.attach(servoPin);  // 將伺服馬達連接的GPIO pin連接伺服物件
  myservo.write(180);  //角度初始在中間，設定為90度

  myStepper.setSpeed(RPM);  //設定馬達轉速

//  pinMode(32, OUTPUT);
//  pinMode(35, OUTPUT);
}

void loop() {
  //  pinMode(signalPin, OUTPUT); //發送超音波時切還為輸出
  //  digitalWrite(signalPin, LOW);
  //  delayMicroseconds(5);
  //  digitalWrite(signalPin, HIGH);  // 給 Trig 高電位，持續 10微秒
  //  delayMicroseconds(10);
  //  digitalWrite(signalPin, LOW);
  //
  //  //接收超音波
  //  pinMode(signalPin, INPUT);             // //讀取超音波時切還為輸入
  //  duration = pulseIn(signalPin, HIGH);   // 收到高電位時的時間
  //
  //  //將回傳時間換算成距離 cm 或 inch
  //  cm = (duration / 2) / 29.1;
  //  inches = (duration / 2) / 74;
  //  Serial.print("Distance : ");
  //
  //  Serial.print(cm);
  //  Serial.print("cm");
  //  Serial.println();
  //
  //  delay(250);
  //
  //  if (cm <= 15) {
  //    digitalWrite(32, HIGH);
  //    digitalWrite(35, HIGH);
  //  }
  //  else {
  //    digitalWrite(32, LOW);
  //    digitalWrite(35, LOW);
  //  }
  // put your main code here, to run repeatedly:

  while (BT.available()) {
    //讀取藍芽資料
    String BTdata = BT.readString();
    Serial.println(BTdata);
    if (BTdata == "OPEN THE DOOR") {
      myservo.write(130);
      delay(1000);

      myStepper.step(300);

    }
    else if (BTdata == "CLOSE THE DOOR") {

      myStepper.step(-32  0);

      delay(1000);
      myservo.write(180);
    }
  }

}
