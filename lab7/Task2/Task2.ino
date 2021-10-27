int arr[] = {0, 1, 2, 3};

void setup() {
    DDRD = 0b11111111; 
    PORTD = 0b00000000; 
}

void loop() {

    PORTB |= ~PORTB;
    PORTD = (1 << arr[0]) | (1 << arr[1]) | (1 << arr[2]) | (1 << arr[3]);

    delay(300);
    
    arr[3]++;
    if (arr[3] == 8)                                arr[2]++,                                           arr[3] = arr[2] + 1;
    if (arr[3] == 8 && arr[2] == 7)                 arr[1]++,                      arr[2] = arr[1] + 1, arr[3] = arr[2] + 1;
    if (arr[3] == 8 && arr[2] == 7 && arr[1] == 6)  arr[0]++, arr[1] = arr[0] + 1, arr[2] = arr[1] + 1, arr[3] = arr[2] + 1;
    if (arr[3] == 8 && arr[2] == 7 && arr[1] == 6 && arr[0] == 5)   arr[0] = 0, arr[1] = 1, arr[2] = 2, arr[3] = 3;
}
