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
#define LED 23
#define LED_NUM 99

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

/*
void initLED();
void ledGraph(int percent);
*/

void setup()
{
  Serial.begin(115200);
  initAirSensor();
  initDuct();
}

void loop()
{
  char ch = '\0';
  if (Serial.available())
  {
    ch = Serial.read();
  }

  switch (ch)
  {
    case '0':
      Serial.println("OK");
      break;
    case '1':
      ductControl(DUCT_UP);
      delay(4000);
      ductControl(DUCT_STOP);
      break;
    case '2':
      ductControl(DUCT_DOWN);
      delay(4500);
      ductControl(DUCT_STOP);
      break;
    case '3':
      AIRSENSOR_DATA temp = getAirSensorData();
      Serial.println(temp.temp);
      Serial.println(temp.humidity);
      Serial.println(temp.pm1p0);
      Serial.println(temp.pm2p5);
      Serial.println(temp.pm10);
      Serial.println(temp.co2);
      break;
  }
}

void initAirSensor()
{
  air_sensor.begin();
}

AIRSENSOR_DATA getAirSensorData()
{
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
void ductControl(int flag)
{
  if (flag == DUCT_UP)
  {
    digitalWrite(M1_UP, HIGH);
    digitalWrite(M1_DOWN, LOW);
    digitalWrite(M2_UP, HIGH);
    digitalWrite(M2_DOWN, LOW);
  }
  else if (flag == DUCT_DOWN)
  {
    digitalWrite(M1_UP, LOW);
    digitalWrite(M1_DOWN, HIGH);
    digitalWrite(M2_UP, LOW);
    digitalWrite(M2_DOWN, HIGH);
  }
  else if (flag == DUCT_STOP)
  {
    digitalWrite(M1_UP, LOW);
    digitalWrite(M1_DOWN, LOW);
    digitalWrite(M2_UP, LOW);
    digitalWrite(M2_DOWN, LOW);
  }
}
