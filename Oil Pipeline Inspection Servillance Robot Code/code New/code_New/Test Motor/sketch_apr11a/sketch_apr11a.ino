#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(10, 9);    //  Tx , Rx

#include <SimpleDHT.h>
SimpleDHT11 dht11;

#define LM1 4
#define LM2 5
#define RM1 6
#define RM2 7
int trigPin = 11;
int echoPin = 12;

int pinDHT11 = A0;
int LDR_PIN = A1;
int LED = 13;

char data;
long duration, distance;
byte temperature = 0;
byte humidity = 0;
int LDR_data = 0;

void Forward()
{
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}
void Backward()
{
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}
void Right()
{
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}
void Left ()
{
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
}
void Stop()
{
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
}
char x;
void setup()
{
  Serial.begin(9600);
  Bluetooth.begin(9600);
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
  if (Bluetooth.available())
  {
    x = Bluetooth.read();

    switch (x)
    {
      case '1':  Forward();   break;
      case '2':  Backward();  break;
      case '3':  Left();      break;
      case '4':  Right();     break;
      case '5':  Stop();      break;
    }
  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
  if (x == '1')
  {
    if (distance <= 31)
    {
      Stop();
    }
  }
  LDR_data = digitalRead(LDR_PIN);
  Serial.println(LDR_data);
  if (LDR_data == LOW)
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }  
  
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
  }
  else
  {
    Bluetooth.print(temperature);
    Bluetooth.print("|");
    Bluetooth.print(humidity);
    Bluetooth.print("|");
    Bluetooth.print("_");
  }
  
}

