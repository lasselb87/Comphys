// Include guard
#ifndef planet_h
#define planet_h

// Included dependencies
#include <iostream>
#include <cmath>
#include <armadillo>
#include <iterator>
#include <string>
#include <vector>

using namespace  std;
using namespace  arma;

class Planet
{
public:
  vec pos;
  vec vel;
  double M;
  Planet();
  Planet(vec position, vec velocity, double m);
};

#endif // planet_h
