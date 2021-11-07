#define MAX7219_Data_IN 11
#define MAX7219_Chip_Select  9
#define MAX7219_Clock 13

const byte help[] = {
    B0110111,   //H
    B1001111,   //E
//  B0001110,   //L
    B1000110,   //Г
    B1100111    //P
};

const byte R[] = {
    B1111110,   //0
    B0110000,   //1
    B1101101,   //2
    B1111001,   //3
    B0110011,   //4
    B1011011,   //5
    B1011111,   //6
    B1110000,   //7
    B1111111,   //8
    B1111011    //9
  
};

int run_counter = 1;
int number_of_digit = 1;

void shift(byte send_to_address, byte send_this_data);
void init_max7219(void); 

void setup() 
{
    pinMode(MAX7219_Data_IN, OUTPUT);
    pinMode(MAX7219_Chip_Select, OUTPUT);
    pinMode(MAX7219_Clock, OUTPUT);
    digitalWrite(MAX7219_Clock, HIGH);
    delay(30);
    init_max7219();
}

void loop() 
{
    int arr_size = sizeof(help);
    static int my_step = -sizeof(help);

    if(run_counter > 9 && run_counter <= 99) number_of_digit = 2;
    if(run_counter > 99 && run_counter <= 999) number_of_digit = 3;
 
 

    for(int i = 0; i < arr_size + number_of_digit + 1; i++){
        if(((arr_size - i) + my_step <= 8) && ((arr_size - i) + my_step > 0) ){
            if(i < arr_size){
                shift((arr_size - i) + my_step , help[i]);
            }
      
            else if (i == arr_size && number_of_digit == 1 ) {
                shift((arr_size - i) + my_step, R[run_counter % 10]);
            }

            else if (number_of_digit == 2){
                if (i == arr_size) {
                    shift((arr_size - i) + my_step, R[run_counter / 10 % 10]);
                }
      
                if (i == arr_size + 1) {
                    shift((arr_size - i) + my_step, R[run_counter % 10]); 
                }
            }
  
            if( i == arr_size + number_of_digit) {
                shift((arr_size - i) + my_step, 0);
            }
        }
    }
  
    my_step++;
    if ((arr_size - 1) + my_step > 8 + sizeof(help)) my_step = -sizeof(help), run_counter++;

    delay(150);
    shift(8, 0);
}


void shift(byte send_to_address, byte send_this_data) 
{
  digitalWrite(MAX7219_Chip_Select, LOW);
  shiftOut(MAX7219_Data_IN, MAX7219_Clock, MSBFIRST, send_to_address);
  shiftOut(MAX7219_Data_IN, MAX7219_Clock, MSBFIRST, send_this_data);
  digitalWrite(MAX7219_Chip_Select, HIGH);
}
void init_max7219(void) //Setup of MAX7219 chip
{
  shift(0x0f, 0x00); //display test register - test mode off
  shift(0x0c, 0x01); //shutdown register - normal operation
  shift(0x0b, 0x07); //scan limit register - display digits 0 thru 7
  shift(0x0a, 0x0f); //intensity register - max brightness
  shift(0x09, 0x00); // 0xff); //decode mode register - No decode for digits
}
