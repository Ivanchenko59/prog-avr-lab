#include <TFT.h> // библиотека для работы с TFT
#include <SPI.h>
#include <SD.h>

#define CS   10
#define DC   9
#define RESET  8  

const int chipSelect = 4;
File myFile;

TFT myScreen = TFT(CS, DC, RESET);

int progress = 0;
char printout[5];
uint32_t new_time = 0;

void setup() {
    SD.begin(chipSelect);
    myScreen.begin();  
    myScreen.background(0,0,0); 
    delay(200);
    myScreen.stroke(255, 0, 0);
    myScreen.setTextSize(3);
    myScreen.text("PI-91", 35, 10);

    SD.remove("test.txt");
}

void loop() {

    int pot_val = analogRead(A0);
    if (millis() - new_time > 600) {
        progress += 10; 
        if (progress == 170) {
            progress = 0;
            myScreen.fillRect(0, 100, 170, 20, 0);

            myFile = SD.open("test.txt", FILE_WRITE);
            myFile.println("Progress done!");  
            myFile.close();
        }
        myFile = SD.open("test.txt", FILE_WRITE);
        myFile.println(pot_val);    
        myFile.close();
        new_time = millis();
    }
    String str = String(pot_val);

    str.toCharArray(printout,5);
    myScreen.stroke(map(pot_val, 0, 1023, 0, 255),map(pot_val, 0, 1023, 255, 0),255);
    myScreen.text(printout, 50, 40);
    delay(100);
    myScreen.stroke(0, 0, 0);
    myScreen.text(printout, 50, 40);

    myScreen.fillRect(0, 100, progress, 20, 255);
}
