#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;
File myFile;
uint32_t new_time = 0;

void setup() {
    Serial.begin(9600);
    Serial.print("Initializing SD card...");
    if (!SD.begin(chipSelect)) {
        Serial.println("initialization failed!");
        while (1) { }
    }
    SD.remove("test.txt");
    Serial.println("initialization done.");
    myFile = SD.open("test.txt", FILE_WRITE);

    if (myFile) {   // if the file opened okay, write to it:
        Serial.print("Writing to test.txt...");
        myFile.println("testing 1, 2, 3.");
        // close the file:
        myFile.close();
        Serial.println("done.");
    } 
    else {
        Serial.println("error opening test.txt");
    }

}

void loop() {

    if (millis() - new_time > 1000) {
        int pot_val = analogRead(A0);
        myFile = SD.open("test.txt", FILE_WRITE);

        if (myFile) {
            myFile.print(millis());
            myFile.print(" ");
            myFile.println(pot_val);    
            myFile.close();// close the file:
        }
        else {
            Serial.println("error opening test.txt");
        }
        new_time = millis();
    }
}
