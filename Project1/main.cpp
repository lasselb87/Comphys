#include <iostream>
#include <armadillo>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <chrono>
using namespace std;
using namespace arma;

//Functions used
vec v_opti(int n);
vec generalalgorithm(int n, vec a, vec b, vec c, vec f);
vec optimizedalgorithm(int n,vec b,vec f);
vec LUdecomposition(int n);
//Function describing the source
inline double Sourceterm(double x)
{
    return 100*exp(-10*x);
}

//Exact solution
inline double Analyticsolution(double x)
{
    return 1-(1-exp(-10))*x-exp(-10*x);
}


int main(int argc, char *argv[])
{
  int n;
  n=atoi(argv[1]); //Grid points
  //Allocate memory for solvers
  //n+2 to store the boundary conditions
  vec a(n+2,fill::zeros);
  vec b(n+2);
  vec c(n+2,fill::zeros);
  vec x(n+2);
  vec f(n+2);
  //Allocate memory for solutions to solvers
  vec v1(n+2); //Memory for generalalgorithm
  vec v2(n+2); //Memory for optimizedalgortihm
  vec v3(n+2); //Memory for LUdecomposition

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


  //Find maximum error
  int N=7;
  vec h_step(N);
  vec max_error(N);
  for(int i=0;i<N;i++)
  {
    int nn = (int)pow(10,1+i);
    vec v=v_opti(nn);
    h_step[i]=1/(double(nn)+1);
    max_error[i]=0;
    for(int j=nn/10;j<9*nn/10;j++)
    {
      double u=Analyticsolution(j*h_step[i]);
      double error=fabs((v[j]-u)/u);
      if(error>max_error[i])
      {
        max_error[i]=error;
      }
    }
  }

  //Time the different solvers
  auto start1 = std::chrono::high_resolution_clock::now();
  v1=generalalgorithm(n,a,b,c,f);
  auto finish1 = std::chrono::high_resolution_clock::now();

  auto start2 = std::chrono::high_resolution_clock::now();
  v2=optimizedalgorithm(n,b,f);
  auto finish2 = std::chrono::high_resolution_clock::now();

  auto start3 = std::chrono::high_resolution_clock::now();
  v3=LUdecomposition(n);
  auto finish3 = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> elapsed1 = finish1 - start1;
  std::chrono::duration<double> elapsed2 = finish2 - start2;
  std::chrono::duration<double> elapsed3 = finish3 - start3;


  cout<<"General Algorithm with n="<<n<<
              "Elapsed time:"<<elapsed1.count()<<endl;
  cout<<"Optimized Algorithm with n="<<n<<
              "Elapsed time:"<<elapsed2.count()<<endl;
  cout<<"LUdecomposition with n="<<n<<
              "Elapsed time:"<<elapsed3.count()<<endl;


  //Write solutions to file
  ofstream myfile1;
  myfile1.open("results.txt");
  myfile1 << setiosflags(ios::showpoint | ios::uppercase);
  myfile1 << "            x:           v1:          v2;        v3;" << endl;
  v3[0]=v3[n+1]=0;
  for (int i=0;i<n+2;i++)
  {
    myfile1 << setw(15) << setprecision(8) << x[i];
    myfile1 << setw(15) << setprecision(8) << v1[i];
    myfile1 << setw(15) << setprecision(8) << v2[i];
    myfile1 << setw(15) << setprecision(8) << v3[i]<<endl;
  }
  myfile1.close();

  //Write Error and stepsize to file
  ofstream myfile2;
  myfile2.open("error_results.txt");
  myfile2 << setiosflags(ios::showpoint | ios::uppercase);
  myfile2 << "       error;      h_step" << endl;
  for (int i=0;i<N;i++)
  {
    myfile2 << setw(15) << setprecision(8) << log10(max_error[i]);
    myfile2 << setw(15) << setprecision(8) << log10(h_step[i])<<endl;
  }
  myfile2.close();

  return 0;

}

//Solver for the general algorithm(Exercise b)
vec generalalgorithm(int n, vec a, vec b, vec c, vec f)
{
  vec v(n+2);
  //BC and IC
  v[0]=v[n+1]=0.0;
  //Forward substitution
  for (int i=2; i<n+1; i++)
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

//Solver for the optimized algorithm(Exercise c)
vec optimizedalgorithm(int n,vec b,vec f)
{
  vec v(n+2);
  //BC and IC
  v[0]=v[n+1]=0.0;
  //Forward substitution
  for (int i=2; i<n+1; i++)
  {
      b[i]=b[i]-1.0/b[i-1];
      f[i]=f[i]+f[i-1]/b[i-1];
  }
  //Backward substitution
  v[n]=f[n]/b[n];
  for (int i=n-1; i>=1; i--)
  {
      v[i]=(f[i]+v[i+1])/b[i];
  }
  return v;
}

//Have to make a new calculation to find the error
//Got a problem with using the optimized solver when I was to find the error
vec v_opti(int n)
{
    //Stepsize
    double h=1.0/(double(n)+1.0);
    //Let us allocate memory
    //Source term
    vec f(n+2);
    //grid points
    vec x(n+2);
    //We only need b vector after using that a = c = -1
    vec b(n+2);
    //Solution after forward and backward
    vec v(n+2);
    //Let us create elements in allocated memory
    //Fill the diagonal matrix vectors and create grid
    for (int i=0; i<n+2; i++)
    {
        b[i]=2.0;
        x[i]=i*h;
    }
    //Fill the source vector and the exact solution vector
    for (int i=0; i<n+2; i++)
    {
        f[i]=h*h*Sourceterm(x[i]);
    }
    //Forward substitution
    for (int i=2; i<n+2; i++)
    {
        b[i]=b[i]-1.0/b[i-1];
        f[i]=f[i]+f[i-1]/b[i-1];
    }
    //Backward substitution
    v[n]=f[n];
    for (int i=n-1; i>=1; i--)
    {
        v[i]=(f[i]+v[i+1])/b[i];
    }
    return v;
}


vec LUdecomposition(int n)
{
  mat A(n+2,n+2,fill::zeros);
  vec v(n+2,fill::zeros);
  vec x(n+2);
  vec f(n+2);
  v[0]=v[n+2]=0;
  double h = 1.0/(double(n-1.0));
  A.diag(0).fill(2);
  A.diag(-1).fill(-1);
  A.diag(1).fill(-1);
  for (int i=0; i<n+2; i++)
  {
    x[i] = i*h; //linspace
    f[i] = h*h*Sourceterm(x[i]);
  }
// solve Av = f
  v = solve(A,f);
  return v;
}
