#include <SD.h>

//analog sensor pin number
#define TEMPERATURE_PIN_NUM 0
//Arduino Ethernet shield: pin 4
//Adafruit SD shields and modules: pin 10
//Sparkfun SD shield: pin 8
#define SD_PIN 10
//serial baud rate
#define BAUD_RATE 9600
//how many milliseconds between readings
#define TEMPERATURE_READ_TIMER 5000
//how many milliseconds on / off of LED
#define LED_LIGHT_TIME 500
//led pin number
#define LED_PIN 13

//initial setup / configuration
void setup() {
  //LED pin
  pinMode(LED_PIN, OUTPUT);

  //SD pin
  pinMode(SD_PIN, OUTPUT);

  if (!SD.begin(SD_PIN)) {
    if(Serial) {
      Serial.println("SD Card initialization failed, or not present, cannot proceed.");
    }

    return;
  }

  if(Serial) {
    //initialize serial
    Serial.begin(BAUD_RATE);

    //good to go, begin loop.
    Serial.println("Serial initialized!");
  }
}

//da loop
void loop() {
  activateLed();

  logTempToSd();

  delay(TEMPERATURE_READ_TIMER);
}

//logs the current temperature reading to the SD card
void logTempToSd() {
  float voltage, degreesC, degreesF;

  //get voltage
  voltage = getVoltage(TEMPERATURE_PIN_NUM);
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

    if(Serial) {
      //output to serial
      Serial.println(degreesF);
    }
  }
}

//light LED as activity indicator
void activateLed() {
  digitalWrite(LED_PIN, HIGH);
  delay(LED_LIGHT_TIME);

  digitalWrite(LED_PIN, LOW);
  delay(LED_LIGHT_TIME);
}

//read voltage from analog pin
float getVoltage(int pin) {
  return (analogRead(pin) * 0.004882814);
}