#include <iostream>
#include <armadillo>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include "solver.h"
#include "planets.h"
using namespace std;
using namespace arma;

//===================================================================
//Begin Newton force
//-------------------------------------------------------------------
// Function that defines the acceleration
// G - Gravitational constant
// M_sun - mass of the sun
// r_cube - length of the position vector cubed
// pos - position vector(matrix)
//-------------------------------------------------------------------
vec newtonForce(vec pos, vec vel)
{
  double G=1.0;
  double scale=4*M_PI*M_PI;
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
vec myVec(double x, double y, double z)
{
  vec my_Vec(3,fill::zeros);
  my_Vec(0)=x;
  my_Vec(1)=y;
  my_Vec(2)=z;
  return my_Vec;
}


int main()
{
  Planet Earth(myVec(1,0,0),myVec(0,2*M_PI,0),1./333000);
  Planet Jupiter(myVec(3,0,0),myVec(0,M_PI,0),0.09543);
  Planet Saturn(myVec(5,0,0),myVec(0,0.5*M_PI,0),0.009543);

  vector<Planet> solarsystem;

  solarsystem.push_back(Earth);
  solarsystem.push_back(Jupiter);
  solarsystem.push_back(Saturn);


  Solver solver(solarsystem, 3);
  solver.verlet(newtonForce,1,0.000001);
  solver.writetofile("solarsystemData.txt");

  return 0;
}
