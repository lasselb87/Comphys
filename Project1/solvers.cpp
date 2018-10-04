#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <armadillo>
#include <stdlib.h>
#include <algorithm>

using namespace std;
using std::cout;
using std::endl;

//Function describing the source
inline double Sourceterm(double x)
{
    return 100*exp(-10*x);
}

//Exact solution
inline double Exactsolution(double x)
{
    return 1-(1-exp(-10))*x-exp(-10*x);
}

vec generalalgorithm(int n, vec a, vec b, vec c, vec f)
{
  vec v(n+2);
  //Forward substitution
  for (int i=2; i<n+2; i++)
  {
  b[i]=b[i]-a[i-1]*c[i-1]/b[i-1];
  f[i]=f[i]-a[i-1]*f[i-1]/b[i-1];
  }
  //Backward substitution
  v[n]=f[n];
  for (int i=n-1; i>=1; i--)
  {
  v[i]=(f[i]-v[i+1]*c[i])/b[i];
  }
  return v;
}

vec optimizedalgortihm(int n,vec b,vec f)
{
  vec v(n+2);
  //Forward substitution
  for (int i=2; i<n+2; i++)
  {
      b[i]=b[i]-1.0/b[i-1];
      f[i]=f[i]+f[i-1]/b[i-1];
  }
  //Backward substitution
  v[n]=f[n]/(b[n]);
  for (int i=n-1; i>=1; i--)
  {
      v[i]=(f[i]+v[i+1])/b[i];
  }
  return v;
}
