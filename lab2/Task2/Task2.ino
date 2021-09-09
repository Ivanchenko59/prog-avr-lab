#include <Servo.h>

#define SERVO_PIN 9
#define POT_PIN A1
#define BTN_PIN 4
#define DEBOUNCE_TIME 50
#define SERVO_SPEED 7

Servo servo_sg90;

int pot_val = 0, btn_state = 0, servo_pos = 0;
unsigned long new_time = 0, time_servo = 0;

enum {
  backward,
  forward,  
} servo_direction;

void setup() 
{
  servo_sg90.attach(SERVO_PIN, 500, 2500);
  pinMode(POT_PIN, INPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);

  servo_direction = forward;
}

void loop() 
{
  if (millis() - new_time > DEBOUNCE_TIME) {
    btn_state = digitalRead(BTN_PIN);  
    new_time = millis();
  }
  
  if (!btn_state) {
    if (millis() - time_servo > SERVO_SPEED) {
      (servo_direction == forward) ? servo_pos++ : servo_pos--;
      
      if (servo_pos >= 180)
        servo_direction = backward;
      else if (servo_pos <= 0) 
        servo_direction = forward;
      
      time_servo = millis();
    }
    servo_sg90.write(servo_pos);
  }
  else {
    servo_pos = 0;
    pot_val = analogRead(POT_PIN);
    servo_sg90.write(map(pot_val, 90, 980, 0, 180)); //bad potentiometer value :(
  }
}
