// Car_BT_Lamp_Bz_ok.ino    **藍牙小車程式開始**   renew 2018/4/6
const int IN1 =3;  // (pwm) D3  接到(L298N)  IN1 
const int IN2 =5;  // (pwm) D5  接到(L298N)  IN2 
const int IN3 =6;  // (pwm) D6  接到(L298N)  IN3 
const int IN4 =9;  // (pwm) D9  接到(L298N)  IN4 
                   // PWM 是模擬 類比電壓輸出(0~255= 0V~5V)
int lampFront = 7; //前車燈 紅線+ 接 D7，黑線接D2
int lampBack= 8;   //後車燈 紅線+ 接 D8，黑線接D4
int BuzzerPIN=11;  //有源蜂鳴器 +腳 插在D11， 另一腳插在GND上. 

byte speed = 255;  // change this (0-255) to control the speed of the motors. 可調此PWM 0~255, 控制馬達出力。
 char command; // 設command 為字串 ，之後用於讀取序列埠 資料。
void setup() {
  Serial.begin(9600);          // 起始 序列埠 9600 速率。TX/RX
  pinMode(IN1, OUTPUT);       // 設定此 PIN腳 輸出電壓。給馬達 IN1用。
  pinMode(IN2, OUTPUT);       // 設定此 PIN腳 輸出電壓。給馬達 IN2用。
  pinMode(IN3, OUTPUT);       // 設定此 PIN腳 輸出電壓。給馬達 IN3用。
  pinMode(IN4, OUTPUT);       // 設定此 PIN腳 輸出電壓。給馬達 IN4用。
  pinMode(BuzzerPIN, OUTPUT); // 設定此 PIN腳 輸出電壓。有源蜂鳴器
  pinMode(lampFront, OUTPUT); // 設定此 PIN腳 輸出電壓。前車燈
  pinMode(lampBack, OUTPUT);  // 設定此 PIN腳 輸出電壓。後車燈
  
  pinMode(2, OUTPUT);  // 設定此 PIN腳 輸出電壓0V。前車燈黑線接D2.當GND用。
  digitalWrite(2,0);    //設定此 PIN腳 輸出電壓0V。前車燈黑線接D2-當GND用。 
  pinMode(4, OUTPUT);  // 設定此 PIN腳 輸出電壓0V。後車燈黑線接D4.當GND用。
  digitalWrite(4,0);    //設定此 PIN腳 輸出電壓0V。後車燈黑線接D4-當GND用。  
}
 
void loop() {
   if(Serial.available() > 0){      //若序列埠 可用。
    command = Serial.read();        //取讀序列埠。
    Serial.println(command);      //可開啟序列埠視窗查看接收的字串，用於程式除錯。
    Stop(); //initialize with motors stoped  起始馬達停止動作。   
    //Change pin mode only if new command is different from previous.   
        
    switch(command){
    case 'F':      // 序列埠上有 "F" 字元時。由手機藍牙傳出 "F" 字元。(可開啟序列埠視窗查看) 
      Forward();   // 前進。執行 下方的 Forward() 函數。
      break;
    case 'B':  
       Back();// 後退。執行 下方的 Back() 函數。
      break;
    case 'L':  
      Left();// 左轉。執行 下方的 Left() 函數。
      break;
    case 'R':
      Right();// 右轉。執行 下方的 Right() 函數。
      break;
    }
  } 
  if(command=='W'){   
   digitalWrite(lampFront,HIGH);  //前車燈亮。
      }
  if (command=='w'){
  digitalWrite(lampFront,LOW);
   }
   if(command=='U'){   
     digitalWrite(lampBack,HIGH); //後車燈亮。
   }
  if (command=='u'){
     digitalWrite(lampBack,LOW);
  }
  if (command=='V'){    //蜂鳴器。
                 
         tone(BuzzerPIN, 3000, 100); //tone(pin, frequency, duration)
         delay(400);
         tone(BuzzerPIN, 3000, 100);
         delay(400); 
           //digitalWrite( BuzzerPIN , HIGH );    //占(發聲)
           //digitalWrite( BuzzerPIN , LOW );     //空(靜音)
              }
   if(command=='v'){   
           digitalWrite( BuzzerPIN , LOW );     //空(靜音)
          }         
   }

void Forward()      //設定 Forward()函數 的動作。
{ analogWrite(IN1, 0);
  analogWrite(IN2, speed);
  analogWrite(IN3, speed);
  analogWrite(IN4, 0);
}

void Back()          //設定 Back() 函數 的動作。
{ analogWrite(IN1, speed);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, speed);
}
 
void Left()          //設定  Left() 函數 的動作。
{ analogWrite(IN1, 0);
  analogWrite(IN2,speed);
  analogWrite(IN3, 0);
  analogWrite(IN4, speed);
 }
 
void Right()            //設定 Right() 函數 的動作。
{ analogWrite(IN1, speed);
  analogWrite(IN2, 0);
  analogWrite(IN3, speed);
  analogWrite(IN4, 0);
}

void Stop()               //設定 Stop() 函數 的動作。
{ analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}  
                             //**藍牙小車程式結束**

