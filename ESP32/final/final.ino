#include <esp_now.h> //디버그용 무선통신을 위한 라이브러리
#include <WiFi.h> //디버그용 무선통신을 위한 라이브러리
#include <am1008w_k_i2c.h> //복합공기질센서 통신을 위한 라이브러리
#include <Adafruit_NeoPixel.h> //네오픽셀 LED를 제어하기 위한 라이브러리

//리니어 엑추에이터 컨트롤을 위한 GPIO
#define ACTUATOR1_UP 16
#define ACTUATOR2_UP 2
#define ACTUATOR1_DOWN 4
#define ACTUATOR2_DOWN 15
//복합공기질센서 통신 GPIO
#define AIRSENSOR_SCL 22
#define AIRSENSOR_SDA 21
//네오픽셀 LED GPIO
#define LED_DATA 23
#define LED_NUMS 28
#define LED_R 0 //LED 메인 컬러 RED
#define LED_G 192 //LED 메인 컬러 GREEN
#define LED_B 243 //LED 메인 컬러 BLUE
//강력 흡입 팬 GPIO
#define FAN 17

struct AIRSENSOR_DATA //복합공기질센서 데이터 구조체
{
    int co2;
    double humidity;
    double temp;
    int pm1p0;
    int pm2p5;
    int pm10;
}typedef AIRSENSOR_DATA;

struct WIRELESS_DATA //무선통신 데이터 구조체
{
  char command[50];
} typedef WIRELESS_DATA;

//전역변수
AM1008W_K_I2C air_sensor; //공기질 센서 객체
Adafruit_NeoPixel leds(LED_NUMS, LED_DATA, NEO_GRB + NEO_KHZ800); //네오픽셀 LED 객체
WIRELESS_DATA wl_data; //무선통신 데이터 변수
int graph_pointer = 0; //네오픽셀 LED 그래프 포인터

void onReceive(const uint8_t * mac, const uint8_t *incomingData, int len)
{
  memcpy(&wl_data, incomingData, sizeof(wl_data));
  Serial.print("Command received: ");
  Serial.println(wl_data.command);

  String str = wl_data.command, arg1 = "";
  int arg2 = -1, arg3 = -1, arg4 = -1;
  for (int i = 0; i < 4; i++)
  {
    int index = str.indexOf(' ');
    if (-1 != index)
    {
      if (i == 0)
        arg1 = str.substring(0, index);
      else if (i == 1)
        arg2 = str.substring(0, index).toInt();
      else if (i == 2)
        arg3 = str.substring(0, index).toInt();
      str = str.substring(index + 1);
    }
    else if (-1 == index && i == 0)
    {
      arg1 = str;
      break;
    }
    else if (-1 == index && i == 1)
    {
      arg2 = str.substring(0, index).toInt();
      break;
    }
    else if (-1 == index && i == 2)
    {
      arg3 = str.substring(0, index).toInt();
      break;
    }
    else
      arg4 = str.substring(0, index).toInt();
  }

  if (arg1 == "led")
  {
    if (arg2 == -1)
    {
      setLed(0, 0, 0, 255, 255, 255);
    }
    else if (arg2 == -2)
    {
      setLed(255, 255, 255, 0, 0, 0);
    }
    else
    {
      setLed(255, 255, 255, arg2, arg3, arg4);
    }
  }
  else if (arg1 == "blink")
  {
    setLedBlink(255, 72, 72, 2);
  }
  else if (arg1 == "graph")
  {
    setLedGraph(arg2);
  }
  else if (arg1 == "act")
  {
    actuatorControl(arg2, arg3);
  }
  else if (arg1 == "fan")
  {
    setFanSpeed(arg2);
  }
}

void initialize() //센서 및 장치 초기화
{
  Serial.println("\nCompoent Initialize Start");
  air_sensor.begin(); //복합공기질센서 초기화
  //액추에이터 관련 핀 초기화
  pinMode(ACTUATOR1_UP, OUTPUT);
  pinMode(ACTUATOR2_UP, OUTPUT);
  pinMode(ACTUATOR1_DOWN, OUTPUT);
  pinMode(ACTUATOR2_DOWN, OUTPUT);
  //모든 액추에이터 정지
  digitalWrite(ACTUATOR1_UP, LOW);
  digitalWrite(ACTUATOR2_UP, LOW);
  digitalWrite(ACTUATOR1_DOWN, LOW);
  digitalWrite(ACTUATOR2_DOWN, LOW);
  //네오픽셀 LED 초기화
  leds.begin();
  leds.setBrightness(255);
  leds.clear();
  leds.show();
  //흡입팬 초기화
  ledcSetup(0, 25000, 8); //흡입팬 설정 (채널: 0, 주파수: 25KHz, 분해능: (0~255))
  ledcAttachPin(FAN, 0);
  ledcWrite(0, 0); //흡입팬 정지
  Serial.println("Initialize Complate");
}

void actuatorControl(int direction, int time)
{
  if (direction == 1) // DOWN
  {
    digitalWrite(ACTUATOR1_UP, LOW);
    digitalWrite(ACTUATOR2_UP, LOW);
    digitalWrite(ACTUATOR1_DOWN, HIGH);
    digitalWrite(ACTUATOR2_DOWN, HIGH);
    delay(time);
  }
  else if (direction == 2) //UP
  {
    digitalWrite(ACTUATOR1_UP, HIGH);
    digitalWrite(ACTUATOR2_UP, HIGH);
    digitalWrite(ACTUATOR1_DOWN, LOW);
    digitalWrite(ACTUATOR2_DOWN, LOW);
    delay(time);
  }

  digitalWrite(ACTUATOR1_UP, LOW);
  digitalWrite(ACTUATOR2_UP, LOW);
  digitalWrite(ACTUATOR1_DOWN, LOW);
  digitalWrite(ACTUATOR2_DOWN, LOW);
}

void setLed(int rStart, int gStart, int bStart, int rEnd, int gEnd, int bEnd)
{
  int n = 200;
  for (int i = 1; i <= n; i++)
  {
    int r = (int)((((double)rStart - rEnd) / n) * i);
    int g = (int)((((double)gStart - gEnd) / n) * i);
    int b = (int)((((double)bStart - bEnd) / n) * i);

    leds.fill(leds.Color(rStart - r, gStart - g, bStart - b));
    leds.show();
  }
}

void setLedBlink(int red, int green, int blue, int times)
{
  int n = 200;
  for (int c = 0; c < times; c++)
  {
    for (int i = 1; i <= n; i++)
    {
      //메인컬러 -> BLINK 컬러
      int r1 = (int)((((double)LED_R - red) / n) * i);
      int g1 = (int)((((double)LED_G - green) / n) * i);
      int b1 = (int)((((double)LED_B - blue) / n) * i);

      //흰색 -> BLINK 컬러
      int r2 = (int)((((double)255 - red) / n) * i);
      int g2 = (int)((((double)255 - green) / n) * i);
      int b2 = (int)((((double)255 - blue) / n) * i);

      if (graph_pointer != 0)
        leds.fill(leds.Color(LED_R - r1, LED_G - g1, LED_B - b1), 0, graph_pointer); //메인컬러 -> BLINK 컬러
      leds.fill(leds.Color(255 - r2, 255 - g2, 255 - b2), graph_pointer); //흰색 -> BLINK 컬러
      leds.show();
    }
    delay(500);
    for (int i = 1; i <= n; i++)
    {
      //메인컬러 -> BLINK 컬러
      int r1 = (int)((((double)red - LED_R) / n) * i);
      int g1 = (int)((((double)green - LED_G) / n) * i);
      int b1 = (int)((((double)blue - LED_B) / n) * i);

      //흰색 -> BLINK 컬러
      int r2 = (int)((((double)red - 255) / n) * i);
      int g2 = (int)((((double)green - 255) / n) * i);
      int b2 = (int)((((double)blue - 255) / n) * i);

      if (graph_pointer != 0)
        leds.fill(leds.Color(red - r1, green - g1, blue - b1), 0, graph_pointer); //메인컬러 -> BLINK 컬러
      leds.fill(leds.Color(red - r2, green - g2, blue - b2), graph_pointer); //흰색 -> BLINK 컬러
      leds.show();
    }
    delay(500);
  }
}

void setLedGraph(int count)
{
  if (count == -1)
  {
    graph_pointer = 0;
    return;
  }
  int move = count - graph_pointer;
  int n = 200;
  if (move > 0)
  {
    for (int p = 0; p < move; p++)
    {
      for (int i = 1; i <= n; i++)
      {
        int r = (int)((((double)LED_R - 255.0) / n) * i);
        int g = (int)((((double)LED_G - 255.0) / n) * i);
        int b = (int)((((double)LED_B - 255.0) / n) * i);
        leds.setPixelColor(graph_pointer, 255 + r, 255 + g, 255 + b);
        leds.show();
      }
      graph_pointer++;
    }
  }
  else if (move < 0)
  {
    for (int p = 0; p < (-1 * move); p++)
    {
      for (int i = 1; i <= n; i++)
      {
        int r = (int)(((255.0 - LED_R) / n) * i);
        int g = (int)(((255.0 - LED_G) / n) * i);
        int b = (int)(((255.0 - LED_B) / n) * i);
        leds.setPixelColor(graph_pointer - 1, LED_R + r, LED_G + g, LED_B + b);
        leds.show();
      }
      graph_pointer--;
    }
  }
}

void setFanSpeed(int speed)
{
  if (speed >= 0 && speed <= 255)
    ledcWrite(0, speed);
}

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
    Serial.println("Error initializing ESP-NOW");
  esp_now_register_recv_cb(onReceive);

  initialize();
}

AIRSENSOR_DATA getAirSensorData()
{
  //***Example***
  // AIRSENSOR_DATA temp = getAirSensorData();
  // Serial.println(temp.temp);
  // Serial.println(temp.humidity);
  // Serial.println(temp.pm1p0);
  // Serial.println(temp.pm2p5);
  // Serial.println(temp.pm10);
  // Serial.println(temp.co2);

  air_sensor.read_data_command();
  air_sensor.get_pm_operation_mode();
  AIRSENSOR_DATA data;
  data.co2 = air_sensor.get_co2();
  data.pm1p0 = air_sensor.get_pm1p0();
  data.pm2p5 = air_sensor.get_pm2p5();
  data.pm10 = air_sensor.get_pm10();
  data.temp = air_sensor.get_temperature();
  data.humidity = air_sensor.get_humidity();
  return data;
}

void loop()
{

}
