#include <iostream>
#include <iomanip>
#include <armadillo>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include "planets.h"
using namespace std;
using namespace arma;

//===================================================================
//-------------------------------------------------------------------
//  Making planet constructor
//-------------------------------------------------------------------
Planet::Planet(vec position, vec velocity, double m)
{
  pos=position;
  vel=velocity;
  M=m;
}
Planet::Planet()
{
  pos=zeros(3);
  vel=zeros(3);
  M=0;
}
//===================================================================
