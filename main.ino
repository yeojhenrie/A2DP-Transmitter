#include "FS.h"
#include "SD_MMC.h"
#include "BluetoothA2DPSource.h"
//#include <WiFi.h>
//#include <HTTPClient.h>
//const char* ht = "https://maker.ifttt.com/trigger/button/json/with/key/hJHTcywJ7iXc0wwdjlLyciX2eNoaSV01s2tH-S0GlM2";
uint32_t Freq = 0;
BluetoothA2DPSource a2dp_source;
File sound_file;
const int frame_size_bytes = sizeof(int16_t) * 2;
const char* file_namea = "/audio.raw";
const char* file_nameb = "/b.raw";

int32_t get_data_channels(Frame* frame, int32_t channel_len) {
  size_t result_len_bytes = sound_file.read((uint8_t*)frame, channel_len * frame_size_bytes );
  int32_t result_len = result_len_bytes / frame_size_bytes;
  ESP_LOGD("get_sound_data", "%d -> %d",len );
  return result_len;
}

#define ONE_BIT_MODE true

//led function
void led(){
  digitalWrite(18, HIGH);
  delay(200);
  digitalWrite(18, LOW);
  digitalWrite(19, HIGH);
  delay(200);
    digitalWrite(19, LOW);
  digitalWrite(21, HIGH);
  delay(200);
    digitalWrite(21, LOW);
  digitalWrite(22, HIGH);
  delay(200);
    digitalWrite(22, LOW);
  digitalWrite(23, HIGH);
  delay(200);
    digitalWrite(23, LOW);
  digitalWrite(25, HIGH);
  delay(200);
    digitalWrite(25, LOW);
  digitalWrite(26, HIGH);
  delay(200);
    digitalWrite(26, LOW);
  digitalWrite(27, HIGH);
  delay(200);
  digitalWrite(27,LOW);
}
const char* ssid = "GlobeAtHome_F8B16_2.4";
const char* password = "ynhXW79c";
void setup(){
    Serial.begin(115200);
//    WiFi.begin(ssid, password);
//    Serial.println(WiFi.localIP());
    pinMode(2, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);
    pinMode(15, INPUT_PULLUP);
    pinMode(16, INPUT_PULLUP);
    pinMode(17, INPUT_PULLUP);
    pinMode(18, OUTPUT);
    pinMode(19, OUTPUT);
    pinMode(21, OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(23, OUTPUT);
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);

    if(!SD_MMC.begin("/sdcard", ONE_BIT_MODE)){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD_MMC.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD_MMC card attached");
        return;
    }

    Serial.print("SD_MMC Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
    Serial.printf("SD_MMC Card Size: %lluMB\n", cardSize);

    Serial.println("starting A2DP...");
    a2dp_source.start("A-4080", get_data_channels);  
}

void loop(){
  while(digitalRead(16)==LOW){
//    HTTPClient http;
//    http.begin(ht);
    sound_file = SD_MMC.open(file_namea, FILE_READ);
    Serial.println("a");
    led();
//    http.end();
    }
  while(digitalRead(17)==LOW){
//    HTTPClient http;
//    http.begin(ht);
    sound_file = SD_MMC.open(file_nameb, FILE_READ);
    Serial.println("b");
    delay(2950);
    led();
//    http.end();
    }
}
