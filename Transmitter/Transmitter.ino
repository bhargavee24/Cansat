#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <SFE_BMP180.h>
#include "DHT.h"
#define DHTPIN A0

#define DHTTYPE DHT11


RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
SFE_BMP180 bmp180;
float Po = 1013.0;

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();

  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
  bmp180.begin();

  bool success = bmp180.begin();

  if (success) {
    Serial.println("BMP180 init success");
  }
}


void loop() {
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  char status;
  double T, P, alt;
  bool success = false;

  status = bmp180.startTemperature();

  if (status != 0) {
    //    delay(1000);
    status = bmp180.getTemperature(T);

    if (status != 0) {
      status = bmp180.startPressure(3);

      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T);

        if (status != 0) {
          alt = bmp180.altitude(P, Po) / 100;
        }
      }
    }
  }
  char temp[20], pressure[20], alti[20], humidity[20];
  float  temp_float = float(T);
  float alti_float = float(alt);
  float  pressure_float = float(P);
  float humidity_float = float(h);
  char buff[8];
  char test[8];
  char play[8];
  char flag[8];
  char one[20] = "Temperature(℃)=";
  char two[15] = "Altitude(m)=";
  char three[15] = "Pressure(Pa)=";
  char four[15] = "Humidity(%)=";
  char five[10] = "-------";
  String A = dtostrf(T, 2, 3, buff);
  String B = dtostrf(alt, 2, 3, test);
  String C = dtostrf(P, 2, 3, play);
  String D = dtostrf(h, 2, 3, flag);
  // sprintf(buff,"T=%d, A=%d, P=%d, H=%d",temp_float,alti_float,pressure_float,humidity_float);
  Serial.print("Temperaure=");
  Serial.print(A);
  Serial.print("   Altitude=");
  Serial.print(B);
  Serial.print("   Pressure=");
  Serial.print(C);
  Serial.print("   Humidity=");
  Serial.print(D);
  Serial.println("");
  //Serial.print(test);
  //Serial.print(play);
  //Serial.print(flag);
  //Serial.print("\n\n");
  radio.write(&one, sizeof(one));
  radio.write(&buff, sizeof(buff));
  radio.write(&two, sizeof(two));
  radio.write(&test, sizeof(test));
  radio.write(&three, sizeof(three));
  radio.write(&play, sizeof(play));
  radio.write(&four, sizeof(four));
  radio.write(&flag, sizeof(flag));
  radio.write(&five, sizeof(five));
  delay(2000);

}
