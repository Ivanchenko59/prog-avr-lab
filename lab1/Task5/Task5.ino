#define BUZZ_PIN 8
#define MIN_FREQ 300
#define MAX_FREQ 900

int rand_val, set_led, curr_led = 0, curr_buzz = 300;

void setup() {
  for (int i = 0; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(BUZZ_PIN, OUTPUT);
}

void loop() {

  rand_val = random(MIN_FREQ, MAX_FREQ);
  set_led = map(rand_val, MIN_FREQ, MAX_FREQ, 1, 7);
  
  while (curr_led != set_led) {
    
    if (curr_led < set_led) {
      curr_led++;
      curr_buzz += 100;
    }
    else if (curr_led > set_led) {
      curr_led--;
      curr_buzz -= 100;
    }

    tone(BUZZ_PIN, curr_buzz);
    
    for (int i = 0; i <= curr_led; i++) {
      PORTD |= 1 << i;
    }
    for (int i = curr_led + 1; i <= 7; i++) {
      PORTD &= ~(1 << i);
    }
    delay(120);
  }
}
