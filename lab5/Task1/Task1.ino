#define MAX7219_Data_IN 11
#define MAX7219_Chip_Select  9
#define MAX7219_Clock 13

void shift(byte send_to_address, byte send_this_data);
void init_MAX7219(void);
void display(uint16_t val);

uint16_t pot_val; 

float k = 0.2;  

float expRunningAverage(float newVal) 
{
    static float filVal = 0;
    filVal += (newVal - filVal) * k;
    return filVal;
}



void setup() 
{

    pinMode(MAX7219_Data_IN, OUTPUT);
    pinMode(MAX7219_Chip_Select, OUTPUT);
    pinMode(MAX7219_Clock, OUTPUT);
    digitalWrite(MAX7219_Clock, HIGH);
    delay(50);

    init_MAX7219();
    for(int i = 1; i <= 8; i++) shift(i, 0x0f);
       
}

void loop() 
{
   
       int pot_val_prev = pot_val;
       if(abs(pot_val_prev - expRunningAverage(analogRead(A0))) > 3) pot_val = expRunningAverage(analogRead(A0));
       
       display(pot_val);
       delay(30);
}

void shift(byte send_to_address, byte send_this_data)
{
    digitalWrite(MAX7219_Chip_Select, LOW);
    shiftOut(MAX7219_Data_IN, MAX7219_Clock, MSBFIRST, send_to_address);
    shiftOut(MAX7219_Data_IN, MAX7219_Clock, MSBFIRST, send_this_data);
    digitalWrite(MAX7219_Chip_Select, HIGH);
    delay(5);
}

void init_MAX7219(void) //Setup of MAX7219 chip
{
    shift(0x0f, 0x00); //display test register - test mode off
    shift(0x0c, 0x01); //shutdown register - normal operation
    shift(0x0b, 0x07); //scan limit register - display digits 0 thru 7
    shift(0x0a, 0x0f); //intensity register - max brightness
    shift(0x09, 0xff); //decode mode register - CodeB decode all digits
    
}

void display(uint16_t val) 
{
    (pot_val > 999 ) ?  shift(0x04, val / 1000) : shift(0x04, 0x0f);
    (pot_val > 100 ) ?  shift(0x03, val / 100 % 10) : shift(0x03, 0x0f);
    (pot_val > 10 ) ?  shift(0x02, val / 10 % 10) : shift(0x02, 0x0f);
    (pot_val >= 0 ) ?  shift(0x01, val % 10) : shift(0x01, 0x0f); 
}
