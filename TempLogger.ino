#include <SD.h>

const int temperaturePin = 0;
const int chipSelect = 10;
const int serialBaudRate = 9600;
const int tempTimer = 5000;
const int pinModeNum = 10;

void setup() {
  //initialize serial
  Serial.begin(serialBaudRate);

  //initialize SD
  Serial.println("Initializing SD card.");

  pinMode(10, OUTPUT);

  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card initialization failed, or not present, cannot proceed.");
    return;
  }

  //good to go, being loop.
  Serial.println("Card initialized, let's roll.");
}

void loop() {
  float voltage, degreesC, degreesF;

  //get voltage
  voltage = getVoltage(temperaturePin);
  //find celcius
  degreesC = (voltage - 0.5) * 100.0;
  //fins fahrenheit
  degreesF = degreesC * (9.0/5.0) + 32.0;

  //open file
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  //output to file if opened
  if (dataFile) {
    dataFile.println(degreesF);
    dataFile.close();

    //output to serial
    Serial.println(degreesF);
  } 
  else {
    Serial.println("Error opening file.");
  }

  //delay by timer in milliseconds
  delay(tempTimer);
}

float getVoltage(int pin) {
  //read voltage from analog pin
  return (analogRead(pin) * 0.004882814);
}



