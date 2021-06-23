#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(10, 9);    //  Tx , Rx
#include "DHT.h"
DHT dht;

void setup()
{
  Serial.begin(9600);
  Bluetooth.begin(9600);
  dht.setup(2);   /* set pin for data communication */
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());  /* Delay of amount equal to sampling period */

  float humidity = dht.getHumidity();     /* Get humidity value */
  float temperature = dht.getTemperature(); /* Get temperature value */

  Bluetooth.print(humidity, 1);
  Bluetooth.print("|");
  Bluetooth.print(temperature, 1);
  Bluetooth.print("|");
  Bluetooth.print("Object Detected");
  Bluetooth.print("|");
  Bluetooth.print("Crack Detected");
  Bluetooth.print("|");
}
