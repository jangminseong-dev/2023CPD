#define AB 18
#define AA 19

void setup()
{
  pinMode(AA, OUTPUT);
  pinMode(AB, OUTPUT);
}

void loop()
{
  digitalWrite(AA, HIGH);
  digitalWrite(AB, LOW);
  delay(2500);
  digitalWrite(AA, LOW);
  digitalWrite(AB, LOW);
  delay(2500);
  digitalWrite(AA, LOW);
  digitalWrite(AB, HIGH);
  delay(2500);
  digitalWrite(AA, LOW);
  digitalWrite(AB, LOW);
  delay(2500);
}
