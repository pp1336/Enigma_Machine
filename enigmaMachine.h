#ifndef enigmaMachine_h
#define enigmaMachine_h

#include <vector>
#include "mapping.h"

// class representing the enigma machine
class enigmaMachine {
public:
  enigmaMachine();
  ~enigmaMachine();
  void addRotor(rotor *r);
  void addPlug(plugboard *p);
  int reflector(int i);
  int getEncoding(int i);

private:
  std::vector<rotor *> rotors;
  plugboard *plug;
}; 
#endif
