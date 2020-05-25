#include <Arduino.h>
#include <PWSKlib.h>

#define pinRX 2

PWSKlib rx;

void callback()
{
  rx.handle();
}

void setup()
{
  Serial.begin(9600);
  rx.begin(2, callback);
  // put your setup code here, to run once:
}

void loop()
{
  delay(1000);
  String r = rx.get();
  for (int i = 0; i < r.length(); i++)
  {
    char c = r[i];
    for (int j = 7; j >= 0; j--)
    {
      Serial.print((c & (1 << j)) > 0);
    }
    Serial.print(" ");
    Serial.print(c);
    Serial.print(" | ");
  }
  Serial.println();
  // put your main code here, to run repeatedly:
}