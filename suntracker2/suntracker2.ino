#include <Servo.h>  // Include servo library
#define ldr1 A0     // Use analog pins A0 and A1 for reading LDR values
#define ldr2 A1

Servo myservo;  // Create object myservo
int val1;       // Declare variables
int val2;
int pos = 0;  // Set 90 degree as default angle

void setup() {
  myservo.attach(11);  // Servo attached to pin 11
  Serial.begin(9600);
  for (int i = 0; i <= 90; i += 5) {  // Set servo position to 90 deg with delay
    myservo.write(i);
    delay(10);
  }
}

void loop() {
  int val1 = analogRead(ldr1);
  Serial.print("ldr");
  Serial.println(val1);  // Read LDR values
  int val2 = analogRead(ldr2);
  Serial.print("ldr2");
  Serial.println(val2);
  while (abs(val1 - val2) > 30) {  // Turn servo only when difference > 10
    if (val1 > val2) {             // Turn servo clockwise
      pos -= 1;
      myservo.write(pos);
      Serial.println("backward");
      delay(10);
      break;
    } else if (val2 > val1) {  // Turn servo anticlockwise
      pos += 1;
      myservo.write(pos);
      Serial.println("forward");
      delay(10);
      break;
    }
  }
  pos = constrain(pos, 0, 180);  // Constrain angle between 0 and 180 deg

  if (pos > 140 && val1 < 100 || val2 < 100) {  //Reset angle to default value after sunset
    while (pos != 0) {
      myservo.write(pos);
      pos+-5;
    }
  }
}

// void positionSet(int init, int final, int step) {
//   for (; init != final && abs(init - final) >= step;) {
//     myservo.write(init);
//     init += step;
//   }
//   return;
// }
