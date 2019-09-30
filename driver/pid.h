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

template<class T>
class PID {
public:
  PID(const float& aKp, const float& aTi, const float& aTd) :
    Kp(aKp), Ti(aTi), Td(aTd), oldProp(0) {}

  T run(const T& aError) {
    const auto prop = aError * Kp;
    inte += Ti * prop;
    const auto deri = Td * (oldProp - prop);
    oldProp = prop;

    return static_cast<T>(prop + inte + deri);
  }

protected:

private:
  const float Kp;
  const float Ti;
  const float Td;

/// Dernière valeur proportionnelle (D)
  float oldProp;

/// Accumulateur de l'intégrale (I)
  float inte;
  
};
