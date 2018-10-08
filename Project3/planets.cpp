#include <iostream>
#include <iomanip>
#include <armadillo>
#include <fstream>
#include <vector>
using namespace std;
using namespace arma;

class planet
{
public:
  vec pos;
  vec vel;
  double M;
  planet(){}
  planet(vec pos, vec vel, double m)
  {
    pos=position;
    vel=velocity;
    M=m;

  }

};
