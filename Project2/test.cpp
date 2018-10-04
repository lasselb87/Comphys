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

//Test for searching for the largest non-diagonal element

int main()
{
  int n=5;
  //Create matrix with known values
  mat A(n,n,fill::zeros);
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      A(i,j)=i+j;
    }
  }
  int k,l;
  double max=0.0;
  max_offdiag(A,k,l,max,n);
  if(k != 3 or l != 4)
  {
    cout<<"Maximum value function is wrong"<<endl;
  }
  else if(k == 3 && l == 4)
  {
    cout<<"k="<<k<<endl;
    cout<<"l="<<l<<endl;
  }
  cout<<A<<endl;
}
