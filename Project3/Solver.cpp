#include <iostream>
#include <armadillo>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <stdio.h>
using namespace std;
using namespace arma;

vec acceleration(vec pos)
{
  double G=1.0;
  double M=1.0;
  double r_cube=pow(norm(pos),3);
  return G*M*(pos)/(r_cube);

}

void Euler_method(mat &pos,mat &vel,vec acc(vec),double T, double dt,int N)
{
  for(int i=0;i<N;i++)
  {
    vel.col(i+1)=vel.col(i)+acc(pos.col(i))*dt;
    pos.col(i+1)=pos.col(i)+vel.col(i)*dt;
  }
}

int main()
{
  int T=10;
  double dt= 0.01;
  int N= int(T/dt);

  mat pos(3,N,fill::zeros); pos.col(0) = vec({1,2,3});
  mat vel(3,N,fill::zeros); vel.col(0) = vec({1,2,3});

  return 0;
}
