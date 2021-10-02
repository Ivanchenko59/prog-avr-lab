#include "Wire.h"
#include "LiquidCrystal_I2C.h"

#define COLS 16
#define ROWS 2
#define SPEED 700

LiquidCrystal_I2C lcd(0x3F, COLS, ROWS);

uint8_t get_lenght(const char *str);
void moveString(uint8_t len);

const char *static_str = "RTF";
const char *run_str = "*.*";
const char *long_str = "Long text for testing ";

uint32_t time = 0;
uint8_t X = 0, Y = 0;
uint8_t x = COLS - 1, dx = 0;
uint8_t static_str_len, run_str_len, long_str_len;
bool flag = true;

void setup() {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(static_str);
    static_str_len = get_lenght(static_str);
    long_str_len = get_lenght(long_str);
    run_str_len = get_lenght(run_str);
    X = static_str_len;
}

void loop() {
    if (millis() - time > SPEED) {
        time = millis();
        moveString(run_str_len);
        lcd.setCursor(X, Y);
        lcd.print(run_str);
        
        if (x != 0) {
            lcd.setCursor(x, 1);
            for (int i = 0; i < COLS - x - dx; i++) {
                lcd.print(long_str[i]);
            }
            if (COLS - x >= long_str_len) dx++;
            x--;
        }
    
        else {
            lcd.setCursor(0, 1);
            static uint8_t k = 0;
            for (int i = k; i < long_str_len; i++) {
                lcd.print(long_str[i]);
            }
            k++;
            if (k == long_str_len) {
                k = 0;
                x = COLS - 1;
                dx = 0;
            }
        }
    }
}

void moveString(uint8_t len) {
  if (flag)
  {
    lcd.setCursor(X, Y);
    lcd.print(" ");
    X++;
    if (X == 16 - len) flag = !flag;
  }
  else
  {
    lcd.setCursor(X + len - 1, Y);
    lcd.print(" ");
    X--;
    if (X == run_str_len) flag = !flag;
  }
}

uint8_t get_lenght(const char *str)
{
    uint8_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;     
}
