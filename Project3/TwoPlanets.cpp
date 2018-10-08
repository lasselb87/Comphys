#include <iostream>
#include <armadillo>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <stdio.h>
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
vec acceleration(vec pos)
{
  double G=1.0;
  double M_sun=1.0;
  double r_cube=pow(norm(pos),3);
  return -scale*G*M_sun*(pos)/(r_cube);

}
//End Newton force


//===================================================================
//-------------------------------------------------------------------
// Function that uses the forward euler-method
// pos - address to put the position
// vel - address to put the velocity
// acc - call on acceleration function
// dt - stepsize(time)
// N - number of timesteps
//-------------------------------------------------------------------
void Euler_method(mat &pos, mat &vel, vec acc(vec), double dt, int N)
{
  for(int i=0;i<N-1;i++)
  {
    vel.col(i+1)=vel.col(i)+acc(pos.col(i))*dt;
    pos.col(i+1)=pos.col(i)+vel.col(i)*dt;
  }
}


//===================================================================
//Begin velocity verlet
//-------------------------------------------------------------------
// Function that uses the velocity verlet-method
// pos - address to put the position
// vel - address to put the velocity
// acc - call on acceleration function
// dt - stepsize(time)
// N - number of timesteps
//-------------------------------------------------------------------

void velverlet_method(mat &pos, mat &vel, vec acc(vec), double dt, int N)
{
  for(int i=0;i<N-1;i++)
  {
    pos.col(i+1)=pos.col(i)+vel.col(i)*dt+0.5*acc(pos.col(i))*dt*dt;
    vel.col(i+1)=vel.col(i)+0.5*(acc(pos.col(i+1))+acc(pos.col(i)))*dt;
  }
}

//End velocity verlet


//Begin main program
//===================================================================
//-------------------------------------------------------------------
// Run the two different algorithms and write to file
// N-number of timesteps
// T-endtime
// dt-stepsize(time)
//-------------------------------------------------------------------
int main(int argc, char *argv[])
{
  double T = atof(argv[1]);
  double dt = atof(argv[2]);
  int N= int(T/dt);

  mat pos(3,N,fill::zeros);
  mat vel(3,N,fill::zeros);
  pos(0)=1.0; pos(1)=0.0; pos(2)=0.0;
  vel(0)=0.0; vel(1)=2*M_PI; vel(2)=0.0;
  //Euler_method(pos,vel,acceleration,dt,N);
  velverlet_method(pos,vel,acceleration,dt,N);


  //Write to file
  ofstream myfile;
  myfile.open("Data_Earth.txt");
  myfile << setiosflags(ios::showpoint | ios::uppercase);
  //myfile << "x_pos;  y_pos;  z_pos;  x_vel;  y_vel;  z_vel;"<< endl;
  for (int i=0;i<N;i++)
  {
    myfile << pos.col(i)(0)<< " " << pos.col(i)(1)<< " "  << pos.col(i)(2)<<" ";
    myfile << vel.col(i)(0)<< " " << vel.col(i)(1)<< " "  << vel.col(i)(2);
    myfile << endl;
  }

  myfile.close();

  return 0;
}
//End main program
