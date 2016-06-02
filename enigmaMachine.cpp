#include "enigmaMachine.h"
#include <iostream>
#include <stdlib.h>
#include <assert.h>

// default offset for the reflector
static const int reflection_offset = 13;

enigmaMachine::enigmaMachine() {
  plug = nullptr;
}

enigmaMachine::~enigmaMachine() {
  if (plug) {
    delete plug;
  }
  for (unsigned int i = 0; i < rotors.size(); ++i) {
    delete (rotors[i]);
  }
}

// method representing the reflector shifts i by reflection_offset
// result is wrapped around by % 26
int enigmaMachine::reflector(int i) {
  return (i + reflection_offset) % no_of_alp;
}

// add a rotor to the current rotor configuration
void enigmaMachine::addRotor(rotor *r) {
  if (rotors.size() > 0) {
    (rotors[rotors.size() - 1])->setNextRotor(r);
  }
  rotors.push_back(r);
}

// update plugboard setting
void enigmaMachine::addPlug(plugboard *p) {
  plug = p;
}

// Pre: 0 <= i <= 25 Post: return encoding of i for the entire machine
// triggers rotation of first rotor
int enigmaMachine::getEncoding(int i) {
  using namespace std;
  int result = i;
  if (plug != nullptr) {
    result = plug->getEncoding(i);
  }
  for (unsigned int j = 0; j < rotors.size(); ++j) {
    result = (rotors[j])->getEncoding(result);
  }
  result = reflector(result);
  for (unsigned int j = 0; j < rotors.size(); ++j) {
    result = (rotors[rotors.size() - j - 1])->getInvEncoding(result);
  }
  if (plug != nullptr) {
    result = plug->getEncoding(result);
  }
  if (rotors.size() > 0) {
    (rotors[0])->rotate(default_rot_inc);
  }
  return result;
}
