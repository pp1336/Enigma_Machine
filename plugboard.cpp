#include "mapping.h"
#include <iostream>

// constructor for plugboard, setup for encoding on the plugboard
// checks for format error in plugboard encoding
plugboard::plugboard(std::vector<int>& encoding_) {
  using namespace std;
  if (encoding_.size() % 2 == 1) {
    cerr << "error: plugboard has odd number of index." << endl;
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < no_of_alp; ++i) {
    encoding.push_back(i);
  }
  int left = -1;
  int right = -1;
  for (unsigned int i = 0; i < encoding_.size(); i += 2) {
    left = encoding_[i];
    right = encoding_[i + 1];
    encoding[left] = right;
    encoding[right] = left;
  }
}

// Pre: 0 <= i <= 25 Post: return the encoding of i
int plugboard::getEncoding(int i) {
  return encoding[i];
}
