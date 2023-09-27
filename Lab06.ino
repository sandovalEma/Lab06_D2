#include <SPI.h>
#include <SD.h>

File myFile;
String inByte;
String WRITE;
char x;
const int SS = PA_3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.setModule(0);

  Serial.print("Initializing SD card...");
  pinMode(SS, OUTPUT);

  if (!SD.begin(SS)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
  Serial.println("opcion 1: Persona");
  Serial.println("opcion 2: Love");
  Serial.println("opcion 3: Zelda");
  Serial.println("opcion 4: Crear Archivo");
}

void loop() {
  // put your main code here, to run repeatedly: 
  while(Serial.available()>0){
    char c = Serial.read();
    inByte += c;
    delay(100);
  }
  if(inByte == "1\n"){
      Serial.println("Persona");
      myFile = SD.open("Persona.txt");
      while(myFile.available()){
        Serial.write(myFile.read());
      }
      myFile.close();
      Serial.println("File closed");
      
    }else if(inByte == "2\n"){
      
      Serial.println("Love");
      myFile = SD.open("love.txt");
      while(myFile.available()){
        Serial.write(myFile.read());
      }
      myFile.close();
      Serial.println("File closed");
      
    }else if(inByte == "3\n"){
      Serial.println("Zelda");
      myFile = SD.open("zelda.txt");
      while(myFile.available()){
        Serial.write(myFile.read());
      }
      myFile.close();
      Serial.println("File closed");
      
    }else if(inByte == "4\n"){
      Serial.println("ESCRIBIR ALGO");
      myFile = SD.open("test.txt", FILE_WRITE);

      while(x != 'M'){
        if(Serial.available()>0){
          x = Serial.read();
          //Serial.println(x);
          if(x == 'M'){
            Serial.println("Writing Stopped");
          }else{
            WRITE += x;
            delay(100);
          }
        }
      }
      myFile.println(WRITE);
      myFile.close();
      Serial.println("File closed");
    }
    inByte = "";
}
