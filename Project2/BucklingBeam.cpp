//Included dependencies
#include <iostream>
#include <cmath>
#include <armadillo>
#include <fstream>
#include <chrono>
#include "Jacobi.h"

using namespace  std;
using namespace  arma;

//Functions to be used
//==================================================================
vec analyticaleigval(double d, double a, int n);
mat makematrix(double d, double a, int n);
//Main program
//==================================================================
int main(int argc, char *argv[])
//------------------------------------------------------------------
// Function that solves the Buckling beam problem with Jacobis method
// n - number of mesh points as a cmd line argument
{
  int n=100;
  //n=atoi(argv[1]);
  double rho_min=0;
  double rho_max=1;
  double h=(rho_max-rho_min)/(n+1);
  double hh=h*h;
  double d=2.0/(hh);
  double a=-1.0/(hh);

  vec eigval;
  vec eigvec;
  mat A=makematrix(d,a,n);
  vec lambda=analyticaleigval(d,a,n);

  auto start = chrono::high_resolution_clock::now();
	int count = jacobi_solver(A, eigval, eigvec, n);
	auto finish = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = finish - start;

  cout << "Number of mesh points: " << n << endl;
	cout << "Number of similarity transformations: " << count << endl;
	cout << "Elapsed time (s): " << elapsed.count() << endl;
	cout << "Eigenvalues:" << endl;
	cout << "Numerical" << " " << "Analytical" << endl;
	cout << eigval(0) << " " << lambda(0) << endl;
	cout << eigval(1) << " " << lambda(1) << endl;
	cout << eigval(2) << " " << lambda(2) << endl;

	return 0;
}


//Make matrix
//==================================================================
mat makematrix(double d, double a, int n)
//------------------------------------------------------------------
// d - diagonal elements
// a - off-diagonal elements
// n - matrix dimension
{
  mat A(n,n,fill::zeros);
  A.diag(0).fill(d);
  A.diag(-1).fill(a);
  A.diag(1).fill(a);
  return A;
}

//Analytical eigenvalues
//==================================================================
vec analyticaleigval(double d, double a, int n)
//------------------------------------------------------------------
// d - diagonal elements
// a - off-diagonal elements
// n - number of mesh points
{
  vec lambda(n,fill::zeros);
  for(int i=1;i<n+1;i++)
  {
    lambda[i-1]=d+2*a*cos((M_PI*i)/(n+1));
  }
  return lambda;
}
