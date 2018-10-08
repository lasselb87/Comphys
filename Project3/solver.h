// Include guard
#ifndef solver_h
#define solver_h

// Included dependencies
#include <iostream>
#include <cmath>
#include <armadillo>


using namespace  std;
using namespace  arma;


//===================================================================
//-------------------------------------------------------------------
// Solver - Making a class that uses the Verlet method
// Void ..() is now member functions
// pos - position
// vel - velocity
// numPlanets - numer of planets
// N - total timesteps
// dt - size of one timestep
//-------------------------------------------------------------------
// Using cubic matrices to store the pos/vel coordinates for one planet
// in one column. There are then one planet in each column
//-------------------------------------------------------------------

class Solver()
{
private:
  vec t;
  cube pos;
  cube vel;
  vector<planet> planets;
  int numPlanets;
  int N;

  void totalAcceleration(vec forceType, mat &totAcc,int i)

public:
  Solver(vector<Planet> p, int n)
  void verlet(vec acceleration(vec), double T, double dt)
  void writetofile(string filename);
};


#endif // planet_h
