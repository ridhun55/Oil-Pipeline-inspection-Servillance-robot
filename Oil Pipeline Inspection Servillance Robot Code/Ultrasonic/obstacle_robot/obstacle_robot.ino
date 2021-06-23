int trigPin = 10;
int echoPin = 9;

int LM1 = 3;
int LM2 = 4;
int RM1 = 5;
int RM2 = 6;

long duration, distance;

void setup()
{
  delay(random(500, 2000));  
  Serial.begin(9600);
  pinMode(LM1, OUTPUT);     
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  pinMode(trigPin, OUTPUT);         
  pinMode(echoPin, INPUT);          
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);        
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);  
  distance = duration / 58.2;         
  delay(10);
  Serial.println(distance);
  
  if (distance > 31)
  {
    digitalWrite(RM2, HIGH);   // move forward
    digitalWrite(RM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(LM1, LOW);
  }

  if (distance < 30)
  {
    digitalWrite(RM2, LOW);    //Stop
    digitalWrite(RM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(LM1, LOW);
    delay(500);
    digitalWrite(RM2, LOW);    //movebackword
    digitalWrite(RM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(LM1, HIGH);
    delay(500);
    digitalWrite(RM2, LOW);    //Stop
    digitalWrite(RM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(LM1, LOW);
    delay(100);
    digitalWrite(RM2, HIGH);   //turn left
    digitalWrite(RM1, LOW);
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    delay(500);
  }
}

