#define POT_PIN_1   A0
#define POT_PIN_2   A1
#define EN_PIN_M1   9
#define EN_PIN_M2   10
#define IN_A1       2
#define IN_A2       3
#define IN_B1       4
#define IN_B2       5

enum motor_dir {
    backward,
    forward,
    stoped
};

typedef struct {
    uint8_t enPin;
    uint8_t inA;
    uint8_t inB;
    uint8_t mSpeed;
    uint8_t mDirection;
} motor;

void motor_speed(motor m);
void motor_direction(motor m);
void check_direction(motor m, uint16_t pot_val);

int main(void) {
   
    motor m1, m2;
    
    m1.enPin = EN_PIN_M1;
    m1.inA = IN_A1;
    m1.inB = IN_A2;  
    m1.mSpeed = 0;
    m1.mDirection = forward;
    
    m2.enPin = EN_PIN_M2;
    m2.inA = IN_B1;
    m2.inB = IN_B2;
    m2.mSpeed = 0;
    m2.mDirection = forward;

    m2_dir_prev
    while(1) {

        uint16_t pot1_val = analogRead(POT_PIN_1);
        uint16_t pot2_val = analogRead(POT_PIN_2);

        check_direction(m1, pot1_val);       
        motor_direction(m1);
        motor_speed(m1);

        check_direction(m2, pot2_val);       
        motor_direction(m2);
        motor_speed(m2); 

        if (m1.mDirection != m1_dir_prev || m2.mDirection != m2_dir_prev) {
            
        }
    }   
}

void check_direction(motor m, uint16_t pot_val)
{
    if (pot_val < 400 || pot_val > 600) {
        m.mSpeed = 255;
        if (pot_val < 400) {
            m.mDirection = backward;
        }
        else {
            m.mDirection = forward;
        }
    }
    else {
        m.mDirection = stoped;
    }   
}

inline void motor_speed(motor m) {
    analogWrite(m.enPin, m.mSpeed);
}

inline void motor_direction(motor m){
    if (!m.mDirection) {
        digitalWrite(m.inA, HIGH);
        digitalWrite(m.inB, LOW);
    }
    else if (m.mDirection == 1) {
        digitalWrite(m.inA, LOW);
        digitalWrite(m.inB, HIGH);
    }
    else if (m.mDirection == 2) {
        m.mSpeed = 0;
    }
}
