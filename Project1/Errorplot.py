import matplotlib.pyplot as plt
import numpy as np
from numpy import exp,log10


"Analytical solution"
def u(x):
    return 1-(1-exp(-10))*x-exp(-10*x);

#Load solution data
data1=np.loadtxt("results.txt",skiprows=1)
#Load error data
data2=np.loadtxt("error_results.txt",skiprows=1)

#Function to plot the results
def plotter_results(n,x_numerical,v_numerical,title):
    x_analytical=np.linspace(0,1,10000)
    plt.plot(x_analytical,u(x_analytical),'r',label='Analytic')
    plt.plot(x_numerical,v_numerical,'b',label='Numerical')
    plt.grid()
    plt.gca().set_xlabel('$x$')
    plt.gca().set_ylabel('$u(x)$')
    plt.gca().set_title(title)
    plt.legend(loc='best')
    plt.savefig("Solution_n100.png")
    plt.show()

def plotter_error(n,h_step,error,title):
    plt.plot(h_step,error,'k',label='Error')
    plt.grid()
    plt.gca().set_xlabel('$\\log_{h}$')
    plt.gca().set_ylabel('$log{\epsilon}$')
    plt.gca().set_title(title)
    plt.legend(loc='best')
    plt.savefig("Errorplot.png")
    plt.show()


#Define variables for solution
x_numerical=(data1[:,0])
v1=(data1[:,1])
v2=(data1[:,2])
v3=(data1[:,3])

#Define error variables
error=(data2[:,0])
h_step=(data2[:,1])

n=10

#plotter_results(n,x_numerical,v1,'General Algorithm')
plotter_results(n,x_numerical,v2,'Optimized Algorithm')
#plotter_results(n,x_numerical,v3,'LU Decomposition')

#plotter_error(n,h_step,error,'loglog plot of relative error as a function of stepsize')
