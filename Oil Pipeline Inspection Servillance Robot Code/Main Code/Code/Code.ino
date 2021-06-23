#include <SoftwareSerial.h>
#include <SimpleDHT.h>
SoftwareSerial Bluetooth(10, 9);    //  Tx , Rx
SimpleDHT11 dht11;

int pinDHT11 = A2;
int LDR_data;
long duration, distance;
int IR_data;
int trigPin = 11;
int echoPin = 12;

#define LM1 4
#define LM2 5
#define RM1 6
#define RM2 7

void Forward()
{
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  Serial.println("Forword");
}
void Backward()
{
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  Serial.println("Backword");
}
void Right()
{
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  Serial.println("Right");
}
void Left()
{
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  Serial.println("Left");
}
void Stop()
{
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  Serial.println("Stop");
}
char data;
void setup()
{
  Serial.begin(9600);
  Bluetooth.begin(9600);

  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pinDHT11, INPUT);

}

void loop()
{
  if (Bluetooth.available() > 0)
  {
    data = Bluetooth.read();
    Serial.print(data);

    if (data == '1')
    {
      Forward();
    }
    else if (data == '2')
    {
      Backward();
    }
    else if (data == '3')
    {
      Left();
    }
    else if (data == '4')
    {
      Right();
    }
    else if (data == '5')
    {
      Stop();
    }
  }

  LDR_data = analogRead(A1);
  

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;

  byte temperature = 0;
  byte humidity = 0;
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL))
  {
    delay(100);
    return;
  }

  Bluetooth.print("Temp (C): ");
  if ((int)temperature > 0)
  {
    Bluetooth.print((short int)temperature);
  }
  else {
    Bluetooth.print(" ");
  }

  Bluetooth.print("|");
  Bluetooth.print("humidity (%) : ");
  if ((int)humidity > 0)
  {
    Bluetooth.print((short int)humidity);
  }
  else {
    Bluetooth.print(" ");
  }

  Bluetooth.print("|");
  if (distance < 31)
  {
    Bluetooth.print("Obstacle Detected !");
    Stop();
  }
  else {
    Bluetooth.print(" ");
  }




  if (LDR_data > 200) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }


}

