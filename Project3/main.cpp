#include <iostream>
#include <armadillo>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <stdio.h>
#include <vector>
#include "solver.h"
#include "planets.h"
using namespace std;
using namespace arma;


double scale=4*M_PI*M_PI

//===================================================================
//Begin Newton force
//-------------------------------------------------------------------
// Function that defines the acceleration
// G - Gravitational constant
// M_sun - mass of the sun
// r_cube - length of the position vector cubed
// pos - position vector(matrix)
//-------------------------------------------------------------------
vec newtonForce(vec pos)
{
  double G=1.0;
  double M_sun=1.0;
  double r_cube=pow(norm(pos),3);
  return -scale*G*M_sun*(pos)/(r_cube);

}
//End Newton force




//===================================================================
//Begin main program
//-------------------------------------------------------------------
//
//
//-------------------------------------------------------------------
int main()
{

}
