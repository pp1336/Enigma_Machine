#ifndef mapping_h
#define mapping_h

#include<vector>

static const int no_of_alp = 26;
// default number of rotation per input
static const int default_rot_inc = 1;

using namespace std;

// base class representing a mapping from [0, 25] to [0, 25]
class mapping {
public:
  virtual int getEncoding(int i) =0;
protected:
  vector<int> encoding;
};

// class representing a rotor
class rotor : public mapping {
public:
  rotor(vector<int>& encoding_);
  int getEncoding(int i);
  int getInvEncoding(int i);
  void rotate(int r);
  void setNextRotor(rotor *r);

private:
  vector<int> invEncoding;
  rotor *nextRotor;
  int rot;
};

// class representing a plugboard
class plugboard : public mapping {
public:
  plugboard(vector<int>& encoding_);
  int getEncoding(int i);
};

#endif
