#define FAN1 5

const int freq = 25000; //Fan PWM Frequency (25KHz)
const int channel = 0; //ESP32 PWM Channel
const int resolution = 8; //Input Resolution (0~255)

void setup()
{
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(FAN1, channel);
}

void loop()
{
  ledcWrite(channel, 255);
}
