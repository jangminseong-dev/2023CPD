#include <esp_now.h>
#include <WiFi.h>

//CC:DB:A7:DB:AD:40

typedef struct WIRELESS_DATA
{
  char command[50];
} WIRELESS_DATA;

uint8_t address[] = {0xCC, 0xDB, 0xA7, 0xDB, 0xAD, 0x40};
esp_now_peer_info_t peerInfo;
WIRELESS_DATA data;

void onSend(const uint8_t *mac, esp_now_send_status_t status)
{
  Serial.print("Last Packet Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  if (esp_now_init() != ESP_OK)
    Serial.println("Error initializing ESP-NOW");
  esp_now_register_send_cb(onSend);

  memcpy(peerInfo.peer_addr, address, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
    Serial.println("Failed to add peer");
}

void loop()
{
  if (Serial.available())
  {
    String input = Serial.readStringUntil('\n');
    input = input += "\0";
    input.toCharArray(data.command, input.length());
    esp_err_t result = esp_now_send(address, (uint8_t *) &data, sizeof(data));
    if (result == ESP_OK)
    {
      Serial.print(data.command);
      Serial.println(": Sent with success");
    }
    else
      Serial.println("Error sending the data");
  }
}
