// 牙刷互動音樂+網頁通訊+超音波感測器（HC-SR04）
// TRIG: 2, ECHO: 3, 蜂鳴器: 8
// 當牙刷進入指定距離（如10公分內），蜂鳴器播放小星星，並Serial傳送ON給網頁

const int trigPin = 2;
const int echoPin = 3;
const int buzzerPin = 8;

// 小星星旋律
int melody[] = {262, 262, 392, 392, 440, 440, 392, 0, 349, 349, 330, 330, 294, 294, 262};
int noteDurations[] = {4,4,4,4,4,4,2,4,4,4,4,4,4,2,2}; // 4=四分音符, 2=二分音符

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000); // 最多等30ms
  long distance = duration * 0.034 / 2; // cm
  return distance;
}

void playMelody() {
  for (int i = 0; i < 15; i++) {
    int noteDuration = 1000 / noteDurations[i];
    if (melody[i] > 0) {
      tone(buzzerPin, melody[i], noteDuration * 0.9);
    }
    delay(noteDuration);
    noTone(buzzerPin);
  }
}

void loop() {
  long distance = getDistance();
  if (distance > 0 && distance < 10) { // 10公分內視為偵測到牙刷
    Serial.println("ON");
    playMelody();
    delay(1000); // 防止重複觸發
  } else {
    Serial.println("OFF");
  }
  delay(100);
}
