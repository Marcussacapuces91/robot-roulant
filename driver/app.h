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
#include "pid.h"

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
    static int i = 0;
    static int p = 0;
    
    if (!f) return;
    f = false;

    const int steps = long(App::posA) - p;
    p = App::posA;

    const auto Kp = 10.0;
    const auto Ti = 0.0;
    const auto Td = 0.0;

    static PID<float> pidA(Kp, Ti, Td);
    static PID<float> pidB(Kp, Ti, Td);
    
    ++i;
    const auto consigne = round(sin((i * 2 * PI) / 512) * 100);
    const auto mesure = steps;
    const auto error = consigne - mesure;

    float output = pidA.run(error);
      
// Traitement de la zone morte
/*
    if ((output > 0) && (output < 200)) output = 200;
    if ((output < 0) && (output > -200)) output = -200;
*/
        
    setMotorA(output > 511 ? 511 : (output < -511 ? -511 : output));
//    setMotorB(s);

    Serial.print(consigne);
    Serial.print(',');
    Serial.print(mesure);
    Serial.print(',');
    Serial.print(output);
    Serial.println();
  }
  
  inline
  static void intTimer() {
    cli();
    static volatile uint16_t d = 0;
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
  static volatile uint16_t posA;
  static volatile uint16_t posB;

protected:

  void setupTimer() {
    timer.begin();
  }

  void setMotorA(const int s) {
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

  void setMotorB(const int s) {
    if (s > 0) {
      digitalWrite(8, LOW);
      digitalWrite(11, HIGH);
      timer.setValueA(s);  
    } else if (s < 0) {
      digitalWrite(8, HIGH);
      digitalWrite(11, LOW);
      timer.setValueA(-s);  
    } else {
      digitalWrite(8, LOW);
      digitalWrite(11, LOW);
    }
  }
  
private:
//  static volatile bool f;
  Timer<TIMER_1> timer;
};


volatile bool App::f = false;
volatile uint16_t App::posA = 0;
volatile uint16_t App::posB = 0;

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
