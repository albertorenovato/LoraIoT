#include "heltec.h"
#include "images.h"

#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6

String rssi = "RSSI --";
#define PIN_MQ  13

void logo()
{
  Heltec.display->clear();
  Heltec.display->drawXbm(0,5,logo_width,logo_height,logo_bits);
  Heltec.display->display();
}

void setup() {
  
  //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  logo();
  delay(1500);
  Heltec.display->clear();
  
  Heltec.display->drawString(0, 0, "Sensor de Alcohol Listo!");
  Heltec.display->display();
  delay(1000);
  
  pinMode(PIN_MQ,INPUT);
    digitalWrite(PIN_MQ,LOW);
    
  LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
  
}

void loop() {
  boolean mq_estado = digitalRead(PIN_MQ);//Leemos el sensor
  if(mq_estado) //si la salida del sensor es 1
  {
    LoRa.beginPacket();
    LoRa.print("OpenLED");
    LoRa.endPacket();                       
  }
   else //si la salida del sensor es 0
   {
    Serial.print("Sending packet: CloseLED\r\n");
    // send packet
    LoRa.beginPacket();
    LoRa.print("CloseLED");
    LoRa.endPacket();
  }
  delay(1000);  
}
