
#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  Serial.begin(115200);
  SPI.setModule(0);
  Serial.print("Initializing SD card...");
  pinMode(PA_3, OUTPUT);

  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void loop() {
  Serial.println("Elija una opcion");
  Serial.println("1 = DIBUJAR");
  Serial.println("2 = ESCRIBIR");
  
  while (!Serial.available()); // Wait for user input
  int choice = Serial.read() - '0'; // Read serial

  switch (choice) {
    case 1:{        
      while (Serial.available()) {
      Serial.read();
      }
      myFile = SD.open("/");
      printDirectory(myFile, 0);
      printRead();
    }
      break;
    case 2:
      myFile = SD.open("/");
      printDirectory(myFile, 0);
      chooseWrite();
      break;
    default:
      Serial.println("Error elija opción 1 o 2");
  }

  while (Serial.available()) {
    Serial.read();
  }
}

void readFile(char* textName){  
  // re-open the file for reading:
  myFile = SD.open(formatFileName(textName));
  if (myFile) {
    Serial.println(textName);

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("Error opening file");
  }
}

void printDirectory(File dir, int numTabs) {
   dir.rewindDirectory();
   while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}


void printRead(){
    Serial.println("DIBUJAR");
    Serial.println("ESCRIBA EL NOMBRE DEL ARCHIVO QUE DESEE MOSTRAR");
    while (!Serial.available()); // Wait for user input
    String choiceRead = Serial.readString();
    char* choiceReadChar = strdup(choiceRead.c_str());
  
    // Close the file before calling readFile
    myFile.close();
  
    // Call readFile after the file is closed
    readFile(choiceReadChar);
    // Clean up allocated memory
    free(choiceReadChar);
    // Close the file before calling readFile
    myFile.close();
}

void chooseWrite(){
    while (Serial.available()) {
      Serial.read();
    }
    Serial.println("ESCRIBIR");
    Serial.println("ESCRIBA EL NOMBRE DEL ARCHIVO QUE DESEE CREAR");
    while (!Serial.available()); // Wait for user input
    String choiceTextName = Serial.readString();
    char* choiceTextNameChar = strdup(choiceTextName.c_str());

    while (Serial.available()) {
      Serial.read();
    }
    
    Serial.println("INGRESE SU NUEVO DIBUJO: ");
    while (!Serial.available()); // Wait for user input
    String choiceText = Serial.readString();
    char* choiceTextChar = strdup(choiceText.c_str());

}

void writeFile(char* fileName, char* text){

  myFile = SD.open(formatFileName(fileName), FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    myFile.println(trim(text));
    // close the file:
    myFile.close();
    Serial.println("NUEVO DIBUJO CREADO CON ÉXITO");
  } else {
    // if the file didn't open, print an error:
    Serial.println("Error Opening File");
  }

}
