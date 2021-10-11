#define MAX7219_Data_IN 11
#define MAX7219_Chip_Select  9
#define MAX7219_Clock 13

void shift(byte send_to_address, byte send_this_data);
void init_MAX7219(void); //Setup of MAX7219 chip

const byte str[] = {
    B00000101,  // r
    B00001111,  // t
    B01000111   // F
};

void setup() {

    pinMode(MAX7219_Data_IN, OUTPUT);
    pinMode(MAX7219_Chip_Select, OUTPUT);
    pinMode(MAX7219_Clock, OUTPUT);
    digitalWrite(MAX7219_Clock, HIGH);
    delay(50);

    init_MAX7219();  //Setup of MAX7219 chip

}

void loop() {
    for (int i = 1; i <= sizeof(str); i++) {
        shift(i, str[sizeof(str)-i]);
    }
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
    shift(0x09, 0x00); //decode mode register - decode off
}
