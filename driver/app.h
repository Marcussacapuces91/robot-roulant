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
 
#pragma once 

#include "timer.h"

class App {
public:

  void setup() {
    setupTimer();
// Moteur A (D13, D12 & *D10* = OCR1B)
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
// Moteur B (D11, D8 & *D9* = OCR1A)
    pinMode(11, OUTPUT);
    pinMode(8, OUTPUT);

    setupAngularSensor();
  }

  void loop() {
    static unsigned i = 0;
    
    if (!f) return;
    f = false;

    const int s = round(sin((i * 2 * PI) / 32768.0) * 512.0);

    Serial.print(i++);
    Serial.print(',');
    Serial.print(s);
    Serial.println();
        
    if (s > 0) {
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      timer.setValueB(s);  
    } else if (s < 0) {
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      timer.setValueB(-s);  
    } else {
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
    }
  }
  
  inline
  static void isrA() {
    static unsigned d = 0;
    if (d > 0) { 
      --d; 
    } else { 
      d = 62745/20; // 2 * 16000000 / 510 / 50
      f = true;
    };
  }

  inline
  static void isr() {
    static volatile unsigned d = 0;
    if (d > 0) { 
      --d;
    } else { 
      d = 31250; // 16000000 / (511+1) / 25; // 16000000 / (511+1) / 25 = 1250
      f = true;
    };
  }

  static volatile bool f;

protected:

  void setupTimer() {
    timer.setValueA(0);
    timer.setValueB(0);
    pinMode(timer.PIN_A, OUTPUT);
    pinMode(timer.PIN_B, OUTPUT);
  }

  void setupAngularSensor() {
    
  }
  
private:
//  static volatile bool f;
  Timer<TIMER_1> timer;
};


volatile bool App::f = false;

/*
ISR (TIMER0_COMPA_vect) {
  App::isrA();
}

ISR (TIMER0_COMPB_vect) {
  App::isrB();
}
*/

ISR(TIMER1_OVF_vect) {
  cli();
  App::isr();
  sei();
}
