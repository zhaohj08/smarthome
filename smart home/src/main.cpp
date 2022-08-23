#define BLINKER_WIFI            // Blinker全局配置 _WIFI
#define BLINKER_ALIGENIE_OUTLET //天猫精灵设备配置 _OUTLET
#define BLINKER_MIOT_OUTLET     //小爱同学设备配置 _OUTLET

#include <Arduino.h>
#include <Blinker.h> //Blinker库// https://diandeng.tech/
#include <FastLED.h> //FastLED库// https://blog.csdn.net/acktomas/article/details/114634985

#define BLINKER_PRINT Serial
#define NUM_LEDS 16         // LED灯珠数量
#define LED_DT 5           // LED输出控制信号引脚
#define LED_TYPE WS2812     // LED灯带型号
#define COLOR_ORDER GRB     // RGB灯珠中红色、绿色、蓝色LED的排列顺序
#define twinkleInterval 100 // 闪烁间隔时间 (毫秒)
#define twinkleChance 110   // 闪烁数量，数值越大闪烁越多（0-255）
#define LD 225              // LED亮度控制变量，可使用数值为 0 ～ 255， 数值越大则光带亮度越高
#define YZ 10               // 阈值

int servopin = 13; //定义数字接口13 连接伺服舵机信号线
int myangle;       //定义角度变量0-180
int pulsewidth;    //定义脉宽变量
int SD;

char auth[] = "31f753c6ead2"; // Your Device Secret Key
char ssid[] = "Linksys03489"; // Your WiFi network SSID or name
char pswd[] = "zxs123456";    // Your WiFi network WPA password or WEP key

uint8_t max_bright = LD;          // LED亮度控制变量，可使用数值为 0 ～ 255， 数值越大则光带亮度越高
CRGB leds[NUM_LEDS];              // 建立光带leds
BlinkerButton Button1("btn-abc"); // 新建组件对象

void servopulse(int servopin, int myangle) //定义一个脉冲函数 https://blog.csdn.net/sss_369/article/details/52894347
{
  pulsewidth = (myangle * 11) + 500; //将角度转化为500-2480 的脉宽值

  digitalWrite(servopin, HIGH); //将舵机接口电平至高

  delayMicroseconds(pulsewidth); //延时脉宽值的微秒数

  digitalWrite(servopin, LOW); //将舵机接口电平至低

  delay(20 - pulsewidth / 1000);
}
//天猫精灵控制 环境变量=data1
void aligeniePowerStatedata1(const String &data1)
{ //电源操作回调函数
  if (data1 == BLINKER_CMD_ON)
  {
    digitalWrite(2, HIGH);        // GPIO contral
    for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
    {
      servopulse(servopin, 110); //引用脉冲函数
    }
    for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
    {
      servopulse(servopin, 90); //引用脉冲函数
    }
    BlinkerAliGenie.powerState("on"); //天猫精灵控制返回
    BlinkerAliGenie.print();
  }
  else if (data1 == BLINKER_CMD_OFF)
  {
    digitalWrite(2, LOW);         // GPIO contral
    for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
    {
      servopulse(servopin, 70); //引用脉冲函数
    }
    for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
    {
      servopulse(servopin, 90); //引用脉冲函数
    }
    BlinkerAliGenie.powerState("off"); //天猫精灵控制返回
    BlinkerAliGenie.print();
  }
}
//小爱同学控制 环境变量=data
void miotPowerStatedata(const String &data)
{ //电源操作回调函数
  if (data == BLINKER_CMD_ON)
  {
    digitalWrite(2, HIGH);        // GPIO contral
    for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
    {
      servopulse(servopin, 110); //引用脉冲函数
    }
    for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
    {
      servopulse(servopin, 90); //引用脉冲函数
    }
    BlinkerMIOT.powerState("on"); //小爱同学控制返回
    BlinkerMIOT.print();
  }
  else if (data == BLINKER_CMD_OFF)
  {
    digitalWrite(2, LOW);         // GPIO contral
    for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
    {
      servopulse(servopin, 70); //引用脉冲函数
    }
    for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
    {
      servopulse(servopin, 90); //引用脉冲函数
    }
    BlinkerMIOT.powerState("off"); //小爱同学控制返回
    BlinkerMIOT.print();
  }
}
//注册组件回调
void Button1_callback(const String &state)
{
  if (state == "on")
  {
    digitalWrite(2, HIGH);
    for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
    {
      servopulse(servopin, 110); //引用脉冲函数
    }
    for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
    {
      servopulse(servopin, 90); //引用脉冲函数
    }
    Button1.color("#33cc00");
    Button1.text("灯开了");
    Button1.print("on");
  }
  else if (state == "off")
  {
    digitalWrite(2, LOW);
    for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
    {
      servopulse(servopin, 70); //引用脉冲函数
    }
    for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
    {
      servopulse(servopin, 90); //引用脉冲函数
    }
    Button1.color("#ff0000");
    Button1.text("灯关了");
    Button1.print("off");
  }
}
void Touch()
{
  if (touchRead(T0) <= YZ)
  { //阈值=YZ
    if ((digitalRead(2) == HIGH))
    { //判断取反
      digitalWrite(2, LOW);
      for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
      {
        servopulse(servopin, 70); //引用脉冲函数
      }
      for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
      {
        servopulse(servopin, 90); //引用脉冲函数
      }
      Serial.println("Tc");
    }
    else if ((digitalRead(2) == LOW))
    { // 判断取反
      digitalWrite(2, HIGH);
      for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
      {
        servopulse(servopin, 110); //引用脉冲函数
      }
      for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
      {
        servopulse(servopin, 90); //引用脉冲函数
      }
      Serial.println("Tc");
    }
  }
}
void LED()
{
  if ((digitalRead(2) == HIGH))
  { //判断取反
    int pos = random8(NUM_LEDS);
    EVERY_N_MILLISECONDS(twinkleInterval)
    {
      if (random8() < twinkleChance)
      {
        leds[pos] = ColorFromPalette(PartyColors_p, random8(255), 128, LINEARBLEND);
      }
    }
    EVERY_N_MILLISECONDS(20)
    {
      fadeToBlackBy(leds, NUM_LEDS, 10);
    }
  }
  else if ((digitalRead(2) == LOW))
  { // 判断取反
    fadeToBlackBy(leds, 16, 255);
  }
}
void Serial2sy()
{
  if (Serial2.available() > 0) //判读是否串口有数据
  {
    String comdata = "";            //缓存清零
    while (Serial2.available() > 0) //循环串口是否有数据
    {
      comdata += char(Serial2.read()); //叠加数据到comdata
      delay(2);                        //延时等待响应
    }
    if (comdata.length() > 0) //如果comdata有数据
    {
      SD = comdata.toInt(); //字符串转整型
      Serial.print("TWN-ONE:");
      Serial.println(SD);
      if (SD == 1)
      {
        for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
        {
          servopulse(servopin, 110); //引用脉冲函数
        }
        for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
        {
          servopulse(servopin, 90); //引用脉冲函数
        }
      }
      if (SD == 0)
      {
        for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
        {
          servopulse(servopin, 70); //引用脉冲函数
        }
        for (int i = 0; i <= 25; i++) //给予舵机足够的时间让它转到指定角度
        {
          servopulse(servopin, 90); //引用脉冲函数
        }
      }
    }
  }
}
/*
//电容触碰中断处理
void gotTouch(){
  delay(10);
  Serial.println("ESP32 Touch Interrupt ");
  //LOOP: // touchAttachInterrupt(T0, gotTouch, 40);//电容触碰中断//config其中40为阈值，当通道T0上的值<40时，会触发中断
}
*/
//初始化
void setup()
{
  Serial.begin(115200); //初始化串口
  Serial2.begin(115200);
  BLINKER_DEBUG.stream(Serial);    //开启调试信息
  BLINKER_DEBUG.debugAll();        //详细
  Blinker.begin(auth, ssid, pswd); //初始化Blinker
  pinMode(2, OUTPUT);              // GPIO config
  pinMode(LED_DT, OUTPUT);         // GPIO config
  pinMode(servopin, OUTPUT);       //设定舵机接口为输出接口
  BlinkerAliGenie.attachPowerState(aligeniePowerStatedata1);
  BlinkerMIOT.attachPowerState(miotPowerStatedata);
  Button1.attach(Button1_callback);
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS); // 初始化光带
  FastLED.setBrightness(max_bright);                           // 设置光带亮度
  for (int i = 0; i <= 50; i++)                                //给予舵机足够的时间让它转到指定角度
  {
    servopulse(servopin, 90); //引用脉冲函数
  }
  for (int i = 0; i <= 15; i++)
  {
    digitalWrite(2, HIGH);
    delay(25);
    digitalWrite(2, LOW);
    delay(25);
  }
}
//
void loop()
{
  Blinker.run();  // start Blinker
  FastLED.show(); // start FastLED
  Serial2sy();
  Touch();
  LED();
}