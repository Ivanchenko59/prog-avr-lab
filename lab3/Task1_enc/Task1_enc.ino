#define C1 5    
#define C2 6
int stepEnc = 0;
byte buffEnc[2];
byte flagEnc = 0; // флаг изменения

void setup() {
  pinMode(C1, INPUT);
  pinMode(C2, INPUT);
  Serial.begin(9600);
}

void loop() {
  enc();                        // отслеживаем
  if (flagEnc) {                // если изменение было
    Serial.println(stepEnc);    // выводим состояние в порт
    flagEnc = 0;                // сбрасываем флаг
  }
}

void enc() {
  static uint32_t timer;
  if (timer + 5 > millis()) return;
  buffEnc[0] = buffEnc[1];
  buffEnc[1] = digitalRead(C1);
  if (buffEnc[0] != buffEnc[1]) {                       
    stepEnc += digitalRead(C2) == buffEnc[1] ? 1 : -1;
    flagEnc = 1;
  }
  timer = millis();
}
