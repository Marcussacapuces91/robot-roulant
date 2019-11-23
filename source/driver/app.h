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
    setupSensors();

    setupTimer();

    timer.setValueA(511);  
    timer.setValueB(511);  
    
    pinMode( 8, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    
    digitalWrite(8, HIGH);
    delay(5000);
    digitalWrite(8, LOW);
    digitalWrite(11, HIGH);
    delay(5000);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    delay(5000);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    delay(5000);
    digitalWrite(13, LOW);

/*    


    pinMode( 8, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);

    digitalWrite(13, HIGH);
    delay(5000);
    digitalWrite(13, LOW);
*/



/*
// Moteur A (D13, D12 & *D10* = OCR1B)
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
// Moteur B (D11, D12 & *D9* = OCR1A)
    pinMode(11, OUTPUT);
    pinMode(8, OUTPUT);

    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
*/
  }

  void loop() {
    static unsigned long d1[4];
    static unsigned long d2[4];
    static unsigned long d3[4];

    d1[0] = d1[1];
    d1[1] = d1[2];
    d1[2] = d1[3];
    d1[3] = App::d1;

    d2[0] = d2[1];
    d2[1] = d2[2];
    d2[2] = d2[3];
    d2[2] = App::d2;

    d3[0] = d3[1];
    d3[1] = d3[2];
    d3[2] = d3[3];
    d3[2] = App::d3;
          
    Serial.print(((d1[0] + d1[1] + d1[2] + d1[3]) * 87) / 2048);
    Serial.print(',');
    Serial.print(((d2[0] + d2[1] + d2[2] + d2[3]) * 87) / 2048);
    Serial.print(',');
    Serial.print(((d3[0] + d3[1] + d3[2] + d3[3]) * 87) / 2048);
    Serial.println();

    digitalWrite(A0, HIGH);
    delayMicroseconds(10);    
    digitalWrite(A0, LOW);
    delay(5);
  }
  
  void kk() {
    
    const auto Kp = 20.0;
    const auto Ti = 0.0;
    const auto Td = 0.0;

    static PID<float> pidA(Kp, Ti, Td);
    static PID<float> pidB(Kp, Ti, Td);

    static int i = 0;
    static int pA = 0;
    static int pB = 0;
    
    if (!f) return;
    f = false;

    const int stepsA = long(App::posA) - pA;
    pA = App::posA;
    
    const int stepsB = long(App::posB) - pB;
    pB = App::posB;
    
    ++i;
    const auto consigne = round(sin((i * 2 * PI) / 512) * 100);

    float outputA = pidA.run(consigne - stepsA);
    float outputB = pidB.run(consigne - stepsB);
      
// Traitement de la zone morte
/*
    if ((output > 0) && (output < 200)) output = 200;
    if ((output < 0) && (output > -200)) output = -200;
*/
        
    setMotorA(outputA > 511 ? 511 : (outputA < -511 ? -511 : outputA));
    setMotorB(outputB > 511 ? 511 : (outputB < -511 ? -511 : outputB));

    Serial.print(consigne);
    Serial.print(',');
    Serial.print(consigne - stepsA);
    Serial.print(',');
    Serial.print(consigne - stepsB);
    Serial.print(',');
    Serial.print(outputA);
    Serial.print(',');
    Serial.print(outputB);
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
    const auto c = PINC;
    const auto dif = pC ^ c;

    if (dif & _BV(1)) { // changement de ADC1
      if (c & _BV(1)) { // HIGH
        t1 = micros();
      } else {          // LOW
        d1 = micros() - t1;        
      }
    }

    if (dif & _BV(2)) { // changement de ADC2
      if (c & _BV(2)) { // HIGH
        t2 = micros();
      } else {          // LOW
        d2 = micros() - t2;        
      }
    }

    if (dif & _BV(3)) { // changement de ADC3
      if (c & _BV(3)) { // HIGH
        t3 = micros();
      } else {          // LOW
        d3 = micros() - t3;        
      }
    }

    
    pC = c;
  }


/*
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
    if (dif & _BV(2)) {
      if (bool(c & _BV(2)) == bool(c & _BV(3))) ++posB; else --posB;
    }
    if (dif & _BV(3)) {
      if (bool(c & _BV(2)) == bool(c & _BV(3))) --posB; else ++posB;
    }

    pC = c;
    sei();
  }
*/

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
      timer.setValueB(s);  
    } else if (s < 0) {
      digitalWrite(8, HIGH);
      digitalWrite(11, LOW);
      timer.setValueB(-s);  
    } else {
      digitalWrite(8, LOW);
      digitalWrite(11, LOW);
    }
  }

  void setupSensors() {
    pinMode(A0, OUTPUT);
    pinMode(A1, INPUT_PULLUP);
    pinMode(A2, INPUT_PULLUP);
    pinMode(A3, INPUT_PULLUP);

    PCICR |= _BV(PCIE1);  // Pin Change Interrupt Enable 1
    PCMSK1 |= _BV(PCINT9) | _BV(PCINT9) | _BV(PCINT10) | _BV(PCINT11) ;
  }
  
private:
//  static volatile bool f;
  Timer<TIMER_1> timer;

  static volatile uint32_t t1;
  static volatile uint32_t d1;
  static volatile uint32_t t2;
  static volatile uint32_t d2;
  static volatile uint32_t t3;
  static volatile uint32_t d3;
};


volatile bool App::f = false;
volatile uint16_t App::posA = 0;
volatile uint16_t App::posB = 0;

volatile uint32_t App::t1;
volatile uint32_t App::d1 = 0;
volatile uint32_t App::t2;
volatile uint32_t App::d2 = 0;
volatile uint32_t App::t3;
volatile uint32_t App::d3 = 0;

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
