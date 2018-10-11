#include <iostream>
#include <iomanip>
#include <armadillo>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include "solver.h"
using namespace std;
using namespace arma;

//===================================================================
//-------------------------------------------------------------------
// Making Solver member function totalAcceleration
//-------------------------------------------------------------------
void Solver::totalAcceleration(vec forceType(vec,vec), mat &totalAcc, int i)
{
  totalAcc=zeros(3,numPlanets);
  for(int j=0; j<numPlanets;j++)
  {
    totalAcc.col(j) += forceType(pos.slice(i).col(j),vel.slice(i).col(j));
    for(int k=j+1; k<numPlanets; k++)
    {
      mat temp=forceType(pos.slice(i).col(j)-pos.slice(i).col(k),vel.slice(i).col(k));
      totalAcc.col(j) += planets[k].M*temp;
      totalAcc.col(k) -= planets[j].M*temp;
    }
  }
}

//===================================================================
//-------------------------------------------------------------------
// Making Solver constructor
//-------------------------------------------------------------------
Solver::Solver(vector<Planet> p, int n)
{
  planets=p;
  numPlanets=n;
}
//===================================================================
//-------------------------------------------------------------------
// Making Solver member function verlet
//-------------------------------------------------------------------
void Solver::verlet(vec acceleration(vec,vec), double T, double dt)
{
  N = int(T/dt);
  pos = zeros(3, numPlanets, N);
  vel = zeros(3, numPlanets, N);
  for(int i=0; i<numPlanets;i++)
  {
    pos.slice(0).col(i) = planets[i].pos;
    vel.slice(0).col(i) = planets[i].vel;
  }
  mat totalAcc = zeros(3, numPlanets);
  mat prevAcc = zeros(3, numPlanets);
  totalAcceleration(acceleration, totalAcc, 0);
  for(int i=0; i<N-1; i++)
  {
    pos.slice(i+1) = pos.slice(i) + vel.slice(i)*dt + 0.5*totalAcc*dt*dt;
    prevAcc = totalAcc;
    totalAcceleration(acceleration, totalAcc, i+1);
    vel.slice(i+1) = vel.slice(i) + 0.5*(totalAcc+prevAcc)*dt;
  }
}
//===================================================================
//-------------------------------------------------------------------
// Making Solver member function writetofile
//-------------------------------------------------------------------
void Solver::writetofile(string filename)
{
  ofstream myfile;
  myfile.open(filename);
  for(int i=0;i<N;i++)
  {
    for(int j=0;j<numPlanets;j++)
    {
      myfile << pos.slice(i).col(j)(0) << " " " "
             << pos.slice(i).col(j)(1) << " " " "
             << pos.slice(i).col(j)(2) << " " " "

             << vel.slice(i).col(j)(0) << " " 
             << vel.slice(i).col(j)(1) << " "
             << vel.slice(i).col(j)(2) << " ";
    }
    myfile<<endl;
  }
  myfile.close();
}
