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

enum TNumber { TIMER_0, TIMER_1, TIMER_2 };

template <TNumber n>
class Timer {
  public:
    void begin();

    unsigned setValueA(const unsigned);
    unsigned setValueB(const unsigned);

    static const byte PIN_A;
    static const byte PIN_B;

  protected:
  private:
};

/* Timer_0 */

template <>
void Timer<TIMER_0>::begin() {
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  digitalWrite(PIN_A, LOW);
  digitalWrite(PIN_B, LOW);

  cli();
  TCCR0A = 0b10100001;
  TCCR0B = 0b00000001;
  TCNT0 = 0;
  OCR0A = 0;
  OCR0B = 0;
  TIMSK0 = 0b00000001;
  sei();
}

template <>
unsigned Timer<TIMER_0>::setValueA(const unsigned aValue) {
  return (OCR0A = aValue);
}
  
template <>
unsigned Timer<TIMER_0>::setValueB(const unsigned aValue) {
  return (OCR0B = aValue);
}
  
template <>
const byte Timer<TIMER_0>::PIN_A = 6; // OC0A = Arduino 6 = PD6

template <>
const byte Timer<TIMER_0>::PIN_B = 5; // OC0B = Ard. 5 = PD5

/* Timer_1 */

template <>
void Timer<TIMER_1>::begin() {
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  digitalWrite(PIN_A, LOW);
  digitalWrite(PIN_B, LOW);

  cli();
  TCCR1A = _BV(WGM11) /* | _BV(WGM10) */
         | _BV(COM1A1)/* | _BV(COM1A0) */
         | _BV(COM1B1)/* | _BV(COM1B0) */ ;
  TCCR1B = /* _BV(WGM13) | */ _BV(WGM12) |
           /* _BV(CS12) | _BV(CS11) | */ _BV(CS10) ;
  TCCR1C = 0b00000000;
  TCNT1 = 0;
  OCR1A = 0;
  OCR1B = 0;
  TIMSK1 = _BV(TOIE1);  // overflow intr
  sei();
}

template <>
unsigned Timer<TIMER_1>::setValueA(const unsigned aValue) {
  return (OCR1A = aValue);
}
  
template <>
unsigned Timer<TIMER_1>::setValueB(const unsigned aValue) {
  return (OCR1B = aValue);
}
  
template <>
const byte Timer<TIMER_1>::PIN_A = 9;  // OC1A = Arduino 9

template <>
const byte Timer<TIMER_1>::PIN_B = 10; // OC1B = Ard. 10
