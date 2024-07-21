
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char buff[8] = "";
    char test[8] = "";
    char play[8] = "";
    char flag[8] = "";
    char one [20] = "";
    char two [15] = "";
    char three [15] = "";
    char four [15] = "";
    char five [10] = "";
    radio.read(&one, sizeof(one));
    radio.read(&buff, sizeof(buff));
    radio.read(&two, sizeof(two));
    radio.read(&test, sizeof(test));
    radio.read(&three, sizeof(three));
    radio.read(&play, sizeof(play));
    radio.read(&four, sizeof(four));
    radio.read(&flag, sizeof(flag));
    Serial.print(one);
    Serial.print(buff);

    Serial.print(two);
    Serial.print(test);

    Serial.print(three);
    Serial.print(play);

    Serial.print(four);
    Serial.print(flag);
    Serial.print(five);

    Serial.print("\n");

delay(2000);

  }
}
