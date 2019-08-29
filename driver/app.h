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

static const auto ECH = 50;

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
    
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    PCICR |= _BV(PCIE1);  // Pin Change Interrupt Enable 1
    PCMSK1 |= _BV(PCINT9) | _BV(PCINT8);  // enable PC1 & PC0    
  }

  void loop() {
    static unsigned i = 0;
    static unsigned p = 0;
    
    if (!f) return;
    f = false;

    const int s = round(sin((i * 2 * PI) / 512.0) * 300);
    const int steps = long(App::posA) - p;
    p = App::posA;

    Serial.print(++i);
    Serial.print(',');
    Serial.print(s);
    Serial.print(',');
    Serial.print( steps );
    Serial.print(',');
    Serial.print(App::posB);

    
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
  static void intTimer() {
    cli();
    static volatile unsigned d = 0;
    if (d > 0) {
      --d;
    } else {
      d = 16000000 / (511+1) / ECH;
      f = true;
    };
    sei();
  }

  static void intPortC() {
    static byte pC;

    cli();
    const auto c = PINC;
    const auto dif = pC ^ c;

    if (dif & _BV(0)) {
      if (bool(c & _BV(0)) == bool(c & _BV(1))) ++posA; else --posA;
    }
    if (dif & _BV(1)) {
      if (bool(c & _BV(0)) == bool(c & _BV(1))) --posA; else ++posA;
    }

    pC = c;
    sei();
  }

  static volatile bool f;
  static volatile unsigned posA;
  static volatile unsigned posB;

protected:

  void setupTimer() {
    timer.begin();
  }

  
private:
//  static volatile bool f;
  Timer<TIMER_1> timer;
};


volatile bool App::f = false;
volatile unsigned App::posA = 0;
volatile unsigned App::posB = 0;

/*
ISR (TIMER0_COMPA_vect) {
  App::isrA();
}

ISR (TIMER0_COMPB_vect) {
  App::isrB();
}
*/

ISR(TIMER1_OVF_vect) {
  App::intTimer();
}

ISR(PCINT1_vect) {
  App::intPortC();
}
