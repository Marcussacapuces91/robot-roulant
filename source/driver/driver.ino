/**
 * Copyright 2019 Marc SIBERT
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "timer.h"
Timer<TIMER_1> timer;

ISR(TIMER1_OVF_vect) {
//  App::intTimer();
}



// App app;


void setup() {
  Serial.begin(115200);
  while (!Serial) ;

  Serial.print(F("Hello! ")); Serial.print(__FILE__); Serial.println(F(" up!"));
  Serial.print(F("Copyright 2019 M. SIBERT - "));
  Serial.println(__DATE__);


  timer.begin();
  pinMode( 8, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);


/*
// Avant gauche
  digitalWrite(8, HIGH);
  delay(5000);
  digitalWrite(8, LOW);

// Arrière gauche  
  digitalWrite(13, HIGH);
  delay(5000);
  digitalWrite(13, LOW);

// Avant droit
  digitalWrite(11, HIGH);
  delay(5000);
  digitalWrite(11, LOW);

// Arrière droit
  digitalWrite(12, HIGH);
  delay(5000);
  digitalWrite(12, LOW);
*/


}

void avancer(const unsigned d) {
  timer.setValueA(450);  
  timer.setValueB(400);  

  digitalWrite(8, HIGH);
  digitalWrite(11, HIGH);
  delay(d);
  digitalWrite(8, LOW);
  digitalWrite(11, LOW);
}

void reculer(const unsigned d) {
  timer.setValueA(450);  
  timer.setValueB(400);  

  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  delay(d);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
}

void tourner(const float& a) {
  if (a > 0) {
    timer.setValueA(300);  
    timer.setValueB(300);  
  
    digitalWrite(12, HIGH);
    digitalWrite(8, HIGH);
    delay(a);
    digitalWrite(12, LOW);
    digitalWrite(8, LOW);
  } else if (a < 0) {
    timer.setValueA(300);  
    timer.setValueB(300);  
  
    digitalWrite(13, HIGH);
    digitalWrite(11, HIGH);
    delay(-a);
    digitalWrite(13, LOW);
    digitalWrite(11, LOW);
  }
  
}

void loop() {
  String s;
  while (true) {
    if (Serial.available()) {
      const char c = Serial.read();
      if (c == '\r') {} 
      else if (c == '\n') break;
      else s += c;
    }
  }
  Serial.println(">" + s + "<");

  const byte espace = s.indexOf(' ');
  const String cmd = (espace > -1) ? s.substring(0, espace) : s;
  const String param = (espace > -1) ? s.substring(espace + 1) : "";

  Serial.print("Cmd:");
  Serial.print(cmd);
  Serial.print(", Param:");
  Serial.println(param);

  if (cmd.equalsIgnoreCase(F("A"))) {
    const int dist = param.toInt();
    if (dist > 0) avancer(dist);
    if (dist < 0) reculer(-dist);
    Serial.println(F("OK"));
  } else if (cmd.equalsIgnoreCase(F("R"))) {
    const float angle = param.toFloat();
    tourner(angle);
    Serial.println(F("OK"));
  }
  
}
