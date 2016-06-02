#include "mapping.h"
#include <iostream>

// initial amount of rotation for a rotor
static const int default_rot = 0;

// constructor for rotor, setup both forward and backward encoding
// offset mapping, initialise nextRotor to nullptr
rotor::rotor(std::vector<int>& encoding_) {
  using namespace std;
  int size = encoding_.size();
  if (size != no_of_alp) {
    cerr << "error: rotor configuration must have 26 letters" << endl;
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < size; ++i) {
    encoding.push_back(encoding_[i] - i);
    invEncoding.push_back(no_of_alp);
  }
  for (int  i = 0; i < size; ++i) {
    invEncoding[encoding_[i]] = i - encoding_[i];
  }
  rot = default_rot;
  nextRotor = nullptr;
}

// Pre: 0 <= i <= 25 Post: return forward encoding of i
int rotor::getEncoding(int i) {
  return (i + encoding[(i + rot) % no_of_alp] + no_of_alp) % no_of_alp;
}

// Pre: 0 <= i <= 25 Post: return inverse encoding of i
int rotor::getInvEncoding(int i) {
  return (i + invEncoding[(i + rot) % no_of_alp] + no_of_alp) % no_of_alp;
}

// rotate the rotor by specified amount of rotation, call next rotor to 
// rotate if rotation reach 26
void rotor::rotate(int r) {
  if ((rot + r >= no_of_alp) && (nextRotor != nullptr)) {
    nextRotor->rotate(default_rot_inc);
  }
  rot = (rot + r) % no_of_alp;
}

// setup pointer to the next rotot
void rotor::setNextRotor(rotor *r) {
  nextRotor = r;
}
