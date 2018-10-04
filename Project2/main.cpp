#include <iostream>
#include <armadillo>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <stdio.h>
#include "func.cpp"
using namespace std;
using namespace arma;




int main(int argc, char *argv[])
{
  int n;
  n=atoi(argv[1]); //Integration points as a command line argument

  //Define steplength and size of our harmonic oscillator
  double rho_min=0;
  double rho_max=5;
  double h=(rho_max-rho_min)/n;
  double hh=h*h;
  //Make memory for matrix elements
  vec e_i(n,fill::zeros);
  vec d_i(n,fill::zeros);
  vec rho_i(n,fill::zeros);
  vec V_i(n,fill::zeros);
  for(int i=0;i<n;i++)
  {
    e_i(i)=-1.0/hh;
    rho_i(i)=rho_min+(i+1)*h;
    V_i(i)=rho_i(i)*rho_i(i);
    d_i(i)=2.0/hh+V_i(i);
  }


  //Make the tridiagonal matrix with potential
  mat A(n,n,fill::zeros);
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      if(i==j)
      {
        A(i,j)=d_i(i);
      }
      if(i==j+1)
      {
        A(i,j)=e_i(i);
      }
      else if(i==j-1)
      {
        A(i,j)=e_i(i);
      }
    }
  }
  /*
  A.diag(0).fill(2);
  A.diag(-1).fill(-1);
  A.diag(1).fill(-1);
  */

  //Solve the equations using jacobis method
  int k;
  int l;
  double max=1.0;
  while (max>1e-10)
  {
    max_offdiag(A, k, l,max, n);
    jacobis_method(A, k, l, n);
  }
  vec eig(n,fill::zeros);
  for(int i=0;i<n;i++)
  {
    eig(i)=A(i,i);

  }
  eig=sort(eig);
  cout<<eig<<endl;

  /*
  //Analytical eigenvalues
  vec lambda(n,fill::zeros);
  int d=2;
  int a=-1;
  for(int i=1;i<n+1;i++)
  {
    lambda[i]=d+2*a*cos((M_PI*i)/(n+1));
    cout<<lambda[i]<<endl;
  }
  */
  /*
  //Using armadillo to find eigenvalues and eigenvectors
  vec eigval;
  mat eigvec;
  eig_sym(eigval,eigvec,A);
  cout<<eigval<<endl;
  cout<<eigvec<<endl;
  */

  return 0;

}
