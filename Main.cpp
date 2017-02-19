#include <stdexcept>
#include <iostream>
#include <fstream>
#include "enigmaMachine.h"

static const int A_ = 65;

// helper of main funciton extract plug and rotor setup storing them in vector
std::vector<int> extractSetup(char *setup) {
  using namespace std;
  ifstream input;
  input.open(setup);
  if (!input.good()) {
    input.close();
    cerr << "error: target " << string(setup) << " does not exits." << endl;
    exit(EXIT_FAILURE);
  }
  int value;
  vector<int> result;
  while (input >> value) {
    result.push_back(value);
  }
  input.close();
  return result;
}

// helper of main function checks for input file format
bool endwith(std::string full, std::string ending) {
  if (full.length() >= ending.length()) {
    return (0 == full.compare(full.length() 
            - ending.length(), ending.length(), ending));
  }
  return false;
}

// helper function maps A - Z to 0 - 25
int parseChar(char c) {
  return ((int) c) - A_;
}

// helper function maps 0 - 25 to A- Z
char getChar(int i) {
  return (char) (i + A_);
}

// main function handles creation of an enigma machine and setting up the
// configuration of the machine
// handles io operations
int main(int argc, char **argv) {
  using namespace std;
  if (argc <= 1) {
    cerr << "error: please configure the enigma machine." << endl;
    exit(EXIT_FAILURE);
  }
  string rot(".rot");
  string plug(".pb");
  enigmaMachine *em = new enigmaMachine();
  for (int i = 1; i < argc; ++i) {
    string filename = string(argv[i]);
    if (endwith(filename, rot)) {
      vector<int> encoding = extractSetup(argv[i]);
      em->addRotor(new rotor(encoding));
    } else if (endwith(filename, plug)) {
      vector<int> encoding = extractSetup(argv[i]);
      em->addPlug(new plugboard(encoding));
    } else {
      cerr << "error: unrecognised argument " << filename << endl;
      exit(EXIT_FAILURE);
    }
  }
  char c = 0;
  int value = 0;
  cin >> ws;
  while (cin >> c) {
    value = parseChar(c);
    if (value < 0 || value > 25) {
      cerr << "error: input must be high cap letters." << endl;
      exit(EXIT_FAILURE);
    }
    value = em->getEncoding(value);
    cout << getChar(value);
  }
  return 0;
}
