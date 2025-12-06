
#include <Servo.h>  //引入舵机库

Servo myServo1;      //创建舵机对象
Servo myServo2;
Servo myServo3;
Servo myServo4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);     //串口初始化，波特率115200
  //S0
  pinMode(14,OUTPUT);
  //S1
  pinMode(15,OUTPUT);
  //S2
  pinMode(16,OUTPUT);
  //LED
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);

  //OAK
  myServo4.attach(7);
  //投掷仓舵机
  myServo1.attach(4);
  myServo2.attach(5);
  myServo3.attach(6);

  myServo1.write(90);
  myServo2.write(90);
  myServo3.write(100);
  myServo4.write(100);

  //激光笔
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}
struct Link{

}link;

unsigned char ID=0,IDD,rc_step1,rc_step2,sum,sum_check;
#define reset_SDI_RC ( rc_step1 = rc_step2 = sum = 0 )
void loop() {
  while(1)
	{
		if( Serial.available() > 0 )
		{
      unsigned char rdata = Serial.read();
			switch( rc_step1 )
			{
				case 0 :
					if( rc_step2 == 0 )
					{
						if( rdata == 0xFE )
							rc_step2 = 1;
					}
					else
					{
						if( rdata == 0xFD )
						{
							rc_step1 = 1;
							rc_step2 = 0;
						}
						else
							rc_step2 = 0;
					}
					
					break;
					
				case 1:
					sum = 0;
					IDD = rdata;
					sum += rdata;
					rc_step1 = 2;
					rc_step2 = 0;
					
					break;
					
				case 2:
					//接收校验位
					sum_check = (uint8_t)(sum%256)%2;
					if(sum_check == rdata){
						ID = IDD;
            reset_SDI_RC;
					}
					else{
						reset_SDI_RC;
					}
      }
    }

    switch(ID){
      case 0:
        break;

      case 1:
        digitalWrite(14,HIGH);
        delay(2000);
        digitalWrite(14,LOW);
        ID = 0;
        break;
      case 2:
        digitalWrite(15,HIGH);
        delay(2000);
        digitalWrite(15,LOW);
        ID = 0;
        break;
      case 3:
        digitalWrite(16,HIGH);
        delay(2000);
        digitalWrite(16,LOW);
        ID = 0;
        break;
      case 4:
        digitalWrite(2,HIGH);
        delay(2000);
        digitalWrite(2,LOW);
        ID = 0;
        break;
      case 5:
        digitalWrite(2,HIGH);
        ID = 0;
        break;
      case 6:
        digitalWrite(2,LOW);
        ID = 0;
        break;
      case 7:
        digitalWrite(2,LOW);
        digitalWrite(10,LOW);
        digitalWrite(2,HIGH);
        digitalWrite(10,HIGH);
        delay(500);
        digitalWrite(2,LOW);
        digitalWrite(10,LOW);
        ID = 0;
        break;
      case 8:
        digitalWrite(2,LOW);
        digitalWrite(10,LOW);
        digitalWrite(2,HIGH);
        digitalWrite(10,HIGH);
        delay(1000);
        digitalWrite(2,LOW);
        digitalWrite(10,LOW);
        ID = 0;
        break;
      case 9:              //oak前视

        myServo4.write(100);
        myServo4.write(0);
        ID=0;
        break;
      case 10:              //oak下视
        myServo4.write(0);
        myServo4.write(100);
        ID=0;
        break;  
      case 11:
      //从0度旋转到180度
        
        myServo1.write(270);
        delay(1000);
      // 从180度旋转回0度
        myServo1.write(90);
        ID=0;
        break;
      case 12:
      //从0度旋转到180度
        
        myServo2.write(270);
        delay(1000);
      // 从180度旋转回0度
        myServo2.write(90);
        
        ID=0;
        break;
      case 13:
      //从0度旋转到180度
        
        myServo3.write(280);
        delay(1000);
      // 从180度旋转回0度
        myServo3.write(100);
        
        ID=0;
        break;  

    }
  }
}