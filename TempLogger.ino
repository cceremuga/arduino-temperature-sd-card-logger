#include <SD.h>

//analog sensor pin number
#define TEMPERTURE_PIN_NUM 0
//Arduino Ethernet shield: pin 4
//Adafruit SD shields and modules: pin 10
//Sparkfun SD shield: pin 8
#define SD_PIN_NUM 10
//serial baud rate
#define BAUD_RATE 9600
//how many milliseconds between readings
#define TEMPERTURE_READ_TIMER 5000
//On the Ethernet Shield, CS is pin 4. It's set as an output by default.
//Note that even if it's not used as the CS pin, the hardware SS pin 
//(10 on most Arduino boards, 53 on the Mega) must be left as an output 
//or the SD library functions will not work. 
#define PIN_MODE 10

void setup() {
  //initialize serial
  Serial.begin(BAUD_RATE);

  //initialize SD
  Serial.println("Initializing SD card.");

  pinMode(PIN_MODE, OUTPUT);

  if (!SD.begin(SD_PIN_NUM)) {
    Serial.println("SD Card initialization failed, or not present, cannot proceed.");
    return;
  }

  //good to go, being loop.
  Serial.println("Card initialized, let's roll.");
}

void loop() {
  float voltage, degreesC, degreesF;

  //get voltage
  voltage = getVoltage(TEMPERTURE_PIN_NUM);
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
  delay(TEMPERTURE_READ_TIMER);
}

float getVoltage(int pin) {
  //read voltage from analog pin
  return (analogRead(pin) * 0.004882814);
}



