#define SERVO_PIN 4

void servo(int pin, int angle);

void setup() 
{
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() 
{
  for (int i = 0; i <= 180; i++) {
    servo(SERVO_PIN, i);

    //blink LED to see 0, 45 ,90, 135, 180 angles signal trigger on the analyzer
    !(i % 45) ? digitalWrite(13, HIGH) : digitalWrite(13, LOW);
  }
  for (int i = 180; i >= 0; i--) {
    servo(SERVO_PIN, i);
  }
}

void servo(int pin, int angle)
{
    int pulseWidth = (angle * 11) + 500;
    digitalWrite(pin, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(pin, LOW);
    delay(20 - pulseWidth / 1000);
}

/**
 * 1. PWM/PDM - process of changing the pulse width at a constant frequency to change the RMS power.
 * 2. see code
 * 3. see screenshots
 */
