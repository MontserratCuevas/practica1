#include <Arduino.h>
#define LED_BUILTIN 23
#define DELAY 50


void setup() {
  
  Serial.begin(115200);
   pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("ON");
 delay(500);
 digitalWrite(LED_BUILTIN, LOW);
 Serial.println("OFF");
 delay(500);
}



