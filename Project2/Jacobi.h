// Include guard
#ifndef __JACOBI_H_INCLUDED__
#define __JACOBI_H_INCLUDED__

// Included dependencies
#include <iostream>
#include <cmath>
#include <armadillo>

using namespace  std;
using namespace  arma;

//Functions
double max_offdiag(mat &A,int &k,int &l,int n);
void jacobis_method(mat &A, mat &R, int k, int l, int n);
int jacobi_solver(mat A, vec &eigval, mat &eigvec, int n);

#endif // __JACOBI_H_INCLUDED__
