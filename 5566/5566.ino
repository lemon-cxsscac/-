// 牙刷互動音樂範例：4個按鈕模擬4個刷牙區域
// 按鈕接腳：2, 3, 4, 5
// 蜂鳴器接腳：8
// 每區刷30秒，刷過就不再發聲

const int buttonPins[4] = {2, 3, 4, 5}; // 4個區域按鈕
const int buzzerPin = 8;
const int zoneTime = 30; // 每區刷牙秒數

unsigned long zoneStartTime[4] = {0, 0, 0, 0};
bool zoneDone[4] = {false, false, false, false};

// 音階（C, D, E, F）
int tones[4] = {262, 294, 330, 349};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP); // 按鈕接地
  }
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    if (!zoneDone[i]) {
      if (digitalRead(buttonPins[i]) == LOW) { // 按下按鈕
        if (zoneStartTime[i] == 0) {
          zoneStartTime[i] = millis(); // 開始計時
        }
        // 尚未刷滿30秒，持續發聲
        if ((millis() - zoneStartTime[i]) < zoneTime * 1000) {
          tone(buzzerPin, tones[i]);
        } else {
          zoneDone[i] = true; // 該區已完成
          noTone(buzzerPin);
        }
      } else {
        noTone(buzzerPin); // 沒按不發聲
      }
    }
  }
  // 若全部刷完，蜂鳴器靜音
  if (zoneDone[0] && zoneDone[1] && zoneDone[2] && zoneDone[3]) {
    noTone(buzzerPin);
  }
}
