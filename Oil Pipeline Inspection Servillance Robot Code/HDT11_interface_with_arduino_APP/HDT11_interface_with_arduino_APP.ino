
/* 
 *  http://thezhut.com/?page_id=395
*/

#include <SimpleDHT.h>
SimpleDHT11 dht11;

int pinDHT11 = 2;
int LDR;

void setup() {
  Serial.begin(9600);
}

void loop() {

  byte temperature = 0;
  byte humidity = 0;
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL))
  {
    return;
  }
  LDR = analogRead(A1);
  
  Serial.print((int)temperature);
  Serial.print("c");
  Serial.print("|");
  Serial.print((int)humidity);
  Serial.print("%");
  Serial.print("|");
  Serial.println(LDR);
  delay(1000);
}

