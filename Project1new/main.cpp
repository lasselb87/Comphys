#include <iostream>
#include <armadillo>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <chrono>
using namespace std;
using namespace arma;

//Functions used
vec generalalgorithm(int n, vec a, vec b, vec c, vec f);
vec optimizedalgorithm(int n,vec b,vec f);

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


int main(int argc, char *argv[])
{
  int n;
  n=atoi(argv[1]); //Read in n as argument in command line

  //Allocate memory for solvers
  //n+2 to store the boundary conditions
  vec a(n+2);
  vec b(n+2);
  vec c(n+2);
  vec f(n+2);
  vec x(n+2);

  //Allocate memory for solutions to solvers
  vec v1(n+2); //Memory for generalalgorithm
  vec v2(n+2); //Memory for optimizedalgortihm
  //vec v3(n+2); //Memory for LUdecomposition

  //stepsize
  double h=1/(double(n+1));
  //Fill the diagonal vectors
  a.fill(-1);
  b.fill(2);
  c.fill(-1);
  for(int i=0;i<n+2;i++)
  {
    x[i]=i*h;
    f[i]=h*h*Sourceterm(x[i]);
  }

  //Time the different solvers
  auto start1 = std::chrono::high_resolution_clock::now();
  v1=generalalgorithm(n,a,b,c,f);
  auto finish1 = std::chrono::high_resolution_clock::now();

  auto start2 = std::chrono::high_resolution_clock::now();
  v2=optimizedalgorithm(n,b,f);
  auto finish2 = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> elapsed1 = finish1 - start1;
  std::chrono::duration<double> elapsed2 = finish2 - start2;

  cout<<"General Algorithm with n="<<n<<
              "Elapsed time:"<<elapsed1.count()<<endl;
  cout<<"Optimized Algorithm with n="<<n<<
              "Elapsed time:"<<elapsed2.count()<<endl;

  //Write to file
  ofstream myfile;
  myfile.open("results.txt");
  myfile << setiosflags(ios::showpoint | ios::uppercase);
  myfile << "            x:                v1:               v2; " << endl;
  for (int i=0;i<n+2;i++)
  {
    myfile << setw(15) << setprecision(8) << x[i];
    myfile << setw(15) << setprecision(8) << v1[i];
    myfile << setw(15) << setprecision(8) << v2[i] <<endl;
  }
  myfile.close();



  return 0;
  //Write to file
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
  v[n]=f[n]/b[n];
  for (int i=n-1; i>=1; i--)
  {
  v[i]=(f[i]-v[i+1]*c[i])/b[i];
  }
  return v;
}

vec optimizedalgorithm(int n,vec b,vec f)
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
