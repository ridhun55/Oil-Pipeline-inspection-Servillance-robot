#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(10, 9);    //  Tx , Rx

#include <SimpleDHT.h>
SimpleDHT11 dht11;

#define LM1 4
#define LM2 5
#define RM1 6
#define RM2 7

int echoPin = 12;
int trigPin = 11;

int pinDHT11 = A0;
int LDR_PIN = A1;
int LED = 13;

char data;
long duration, distance;
byte temperature = 00;
byte humidity = 00;
int LDR_data;

void setup() {
  Bluetooth.begin(9600);
  Serial.begin(9600);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pinDHT11, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(LED, OUTPUT);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;

  if (dht11.read(pinDHT11, &temperature, &humidity, NULL))
    {
      delay(100);
      return;
    }
    
  if (distance < 31)
  {
    Bluetooth.print(temperature);
    Bluetooth.print("|");
    Bluetooth.print(humidity);
    Bluetooth.print("|");
    Bluetooth.print("Obstacle_Detected");
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
  }
  else {
    Bluetooth.print(temperature);
    Bluetooth.print("|");
    Bluetooth.print(humidity);
    Bluetooth.print("|");
    Bluetooth.print("_");
  }

  
  /* ==================================== */

  LDR_data = analogRead(LDR_PIN);
  if (LDR_data < 120) {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
  if (Bluetooth.available() > 0)
  {
    data = Bluetooth.read();
    if (data == '1')
    {
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
    }
    else if (data == '2')
    {
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
    }
    else if (data == '3')
    {
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
    }
    else if (data == '4')
    {
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
    }
    else if (data == '5')
    {
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
    }
  }
}
