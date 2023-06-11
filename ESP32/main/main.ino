#include <esp_now.h>
#include <WiFi.h>

//리니어 액추에이터 관련
#define M1_UP 16
#define M1_DOWN 4
#define M2_UP 2
#define M2_DOWN 15

#define DUCT_UP 0
#define DUCT_DOWN 1
#define DUCT_STOP 2

//복합공기센서 관련
#include <am1008w_k_i2c.h>
#define AIRSENSOR_SCL 22
#define AIRSENSOR_SDA 21

AM1008W_K_I2C air_sensor;

//네오픽셀 LED 관련
#include <Adafruit_NeoPixel.h>
#define LED_DATA 23
#define NUM_LEDS 28
#define LED_R 0
#define LED_G 192
#define LED_B 243
Adafruit_NeoPixel leds(NUM_LEDS, LED_DATA, NEO_GRB + NEO_KHZ800);
int previous_graph = 0;

//환기 팬 관련
#define IN_FAN 36
#define OUT_FAN 39

//존재감지센서 관련
#define HPS_SENSE 34

struct AIRSENSOR_DATA
{
    int co2;
    double humidity;
    double temp;
    int pm1p0;
    int pm2p5;
    int pm10;
}typedef AIRSENSOR_DATA;

void initDuct(); //
void ductControl(int flag);


void initAirSensor();
AIRSENSOR_DATA getAirSensorData();


void initLED();
void setLED(int r, int g, int b);
void ledGraph(int percent);

struct WIRELESS_DATA
{
  char command[50];
} typedef WIRELESS_DATA;

WIRELESS_DATA wl_data;

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

  if (arg1 == "duct")
  {
    if (arg2 == 0)
      ductControl(DUCT_STOP, 0);
    else if (arg2 == 1)
      ductControl(DUCT_DOWN, arg3);
    else if (arg2 == 2)
      ductControl(DUCT_UP, arg3);
  }
  else if (arg1 == "led")
  {
    testLED(arg2);
  }
  else if (arg1 == "graph")
  {
    ledGraph(arg2);
  }
}

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
    Serial.println("Error initializing ESP-NOW");
  esp_now_register_recv_cb(onReceive);

  initAirSensor();
  initDuct();
  initLED();
  Serial.println("Initializing compalte");
}

void loop()
{

}

void initAirSensor()
{
  air_sensor.begin();
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

void initDuct()
{
  pinMode(M1_UP, OUTPUT);
  pinMode(M1_DOWN, OUTPUT);
  pinMode(M2_UP, OUTPUT);
  pinMode(M2_DOWN, OUTPUT);

  digitalWrite(M1_UP, LOW);
  digitalWrite(M1_DOWN, LOW);
  digitalWrite(M2_UP, LOW);
  digitalWrite(M2_DOWN, LOW);
}

void ductControl(int flag, int ms)
{
  if (flag == DUCT_UP)
  {
    digitalWrite(M1_UP, HIGH);
    digitalWrite(M1_DOWN, LOW);
    digitalWrite(M2_UP, HIGH);
    digitalWrite(M2_DOWN, LOW);
    
    delay(ms);

    digitalWrite(M1_UP, LOW);
    digitalWrite(M1_DOWN, LOW);
    digitalWrite(M2_UP, LOW);
    digitalWrite(M2_DOWN, LOW);
  }
  else if (flag == DUCT_DOWN)
  {
    digitalWrite(M1_UP, LOW);
    digitalWrite(M1_DOWN, HIGH);
    digitalWrite(M2_UP, LOW);
    digitalWrite(M2_DOWN, HIGH);

    delay(ms);

    digitalWrite(M1_UP, LOW);
    digitalWrite(M1_DOWN, LOW);
    digitalWrite(M2_UP, LOW);
    digitalWrite(M2_DOWN, LOW);
  }
  else if (flag == DUCT_STOP)
  {
    digitalWrite(M1_UP, LOW);
    digitalWrite(M1_DOWN, LOW);
    digitalWrite(M2_UP, LOW);
    digitalWrite(M2_DOWN, LOW);
  }
}

void initLED()
{
  leds.begin();
  leds.setBrightness(255);
  leds.clear();
  leds.show();
}

void ledGraph(int percent)
{
  // 3.5에 한칸
  int pixel_num = percent / 3.5;
  int n = 200;
  Serial.print(pixel_num);
  Serial.print(", ");
  Serial.println(previous_graph);
  
  if (previous_graph < pixel_num)
  {
    for (int p = previous_graph - 1; p < pixel_num; p++)
    {
      for (int i = 1; i <= n; i++)
      {
        int r = (int)(((double)LED_R / n) * i);
        int g = (int)(((double)LED_G / n) * i);
        int b = (int)(((double)LED_B / n) * i);
        leds.setPixelColor(p, r, g, b);
        leds.show();
        delayMicroseconds(200);
      }
    }
  }
  else if (previous_graph > pixel_num)
  {
    for (int p = previous_graph - 1; p > pixel_num; p--)
    {
      for (int i = 1; i <= n; i++)
      {
        int r = (int)(((double)LED_R / n) * i);
        int g = (int)(((double)LED_G / n) * i);
        int b = (int)(((double)LED_B / n) * i);
        leds.setPixelColor(p, LED_R - r, LED_G - g, LED_B - b);
        leds.show();
        delayMicroseconds(200);
      }
    }
  }
  else if (percent == -1)
    previous_graph = 0;
  previous_graph = pixel_num;
}

void testLED(int flag)
{
  if (flag == 0)
  {
    for (int i = 255; i >= 0; i--)
    {
      leds.fill(leds.Color(i, i, i, i));
      leds.show();
      delay(1);
    }
  }
  else if (flag == 1)
  {
    for (int i = 0; i <= 255; i++)
    {
      leds.fill(leds.Color(i, i, i, i));
      leds.show();
      delay(1);
    }
  }
  else if (flag == 2)
  {
    leds.fill(leds.Color(0, 192, 243));
    leds.show();
  }
}