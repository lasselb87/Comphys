#include "Jacobi.h"


//==================================================================
double max_offdiag(mat &A,int &k,int &l,int n)
//------------------------------------------------------------------
// Function that finds the largest off-diagonal term of the given
// matrix A
//
// n - the matrix dimension
// k,l - indices of largest element
// max - maximum element
//------------------------------------------------------------------
{

  double max=0.0;
  for(int i=0;i<n;i++)
  {
    for(int j=i+1;j<n;j++)
    {
      if(abs(A(i,j))>max)
        {
          max=abs(A(i,j));
          k=i;
          l=j;
        }
    }
  }
  return max;
}


//==================================================================
void jacobis_method(mat &A, mat &R , int k, int l, int n)
//------------------------------------------------------------------
// Function that rotates the given matrix A and R
// A - matrix to be diagonalized
// R - matrix with eigenvectors as columns
// n - matrix dimension
// k,l - elements to be set to zero
//------------------------------------------------------------------
{

  //Let us begin by defining the new elements in A
  double a_kk, a_ll, a_kl, a_ik, a_il;
  a_kk=A(k,k), a_ll=A(l,l), a_kl=A(k,l);
  //Define variables used
  double s,c,t;
  double tau=(A(l,l)-A(k,k))/(2.0*A(k,l));
  //Make sure that when tau gets large we dont subtract to nearly equal numbers
  if(tau>0)
  {
    t=1.0/(tau+sqrt(1.0+tau*tau));
  }
  else
  {
    t=-1.0/(-tau+sqrt(1.0+tau*tau));
  }

  c=1.0/sqrt(1.0+t*t);
  s=t*c;

  for (int i=0; i<n; i++) {
				double a_ik = A(i, k);
				double a_il = A(i, l);
				A(k, i) = A(i, k) = c*a_ik - s*a_il;
				A(l, i) = A(i, l) = c*a_il + s*a_ik;

				double r_ik = R(i, k);
				double r_il = R(i, l);
				R(i,k) = c*r_ik - s*r_il;
				R(i,l) = c*r_il + s*r_ik;
		}

		A(k, k) = c*c*a_kk - 2.0*c*s*a_kl + s*s*a_ll;
		A(l, l) = s*s*a_kk + 2.0*c*s*a_kl + c*c*a_ll;
		A(k, l) = A(l, k) = 0.0;

		return;
}

//==================================================================
int jacobi_solver(mat A, vec &eigval, mat &eigvec, int n)
//------------------------------------------------------------------
// Function that solves using jacobi's method
// A - matrix to be diagonalized
// eigval - address to put eigenvalues
// eigvec - address to put eigenvectors
// n - matrix dimension
// return - number of transformations
//------------------------------------------------------------------
{
  mat R(n,n,fill::zeros);
  R.diag(0).fill(1.0);

  int k;
  int l;
  double max=1.0;
  int count=0;
  while (max>1e-10)
  {
    max=max_offdiag(A, k, l, n);
    jacobis_method(A, R, k, l, n);
    count++;
  }
  vec eig=A.diag(0); //unsorted eigenvalues
  eigval=sort(eig); //sorted eigenvalues
  eigvec.zeros(n,n);

  for(int i=0; i<n; i++)
  {
    for(int j=0;j<n;j++)
    {
      if(eig(j)==eigval(i))
      {
        eigvec.col(i)=R.col(j);
      }
    }
  }

  return count;
}
