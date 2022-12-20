
#include "heltec.h"
#include "string.h"
#include "stdio.h"

#define LED 25
#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6
char Readback[50];

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
	pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW); 
  Heltec.display->init();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
}

void loop() {

  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // read packet
    while (LoRa.available()) {
	  sprintf(Readback+strlen(Readback),"%c",(char)LoRa.read());
    }
    Serial.print(Readback);
	if(strncmp(Readback, "OpenLED", strlen(Readback)) == 0) {
		digitalWrite(LED, HIGH); 
    Heltec.display->clear();
    Heltec.display->drawString(0, 0, "Alcohol Detectado!");
    Heltec.display->display();
	 }
	else if(strncmp(Readback, "CloseLED", strlen(Readback)) == 0) {
		digitalWrite(LED, LOW);
    Heltec.display->clear();
    Heltec.display->drawString(0, 0, "Alcohol NO Detectado!"); 
    Heltec.display->display();
	 }
	 memset(Readback,0,50);
    // print RSSI of packet
    Serial.print(" with RSSI ");
    Serial.println(LoRa.packetRssi());
  }

}
