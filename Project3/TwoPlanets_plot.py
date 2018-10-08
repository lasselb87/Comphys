import numpy as np
import matplotlib.pyplot as plt

# Set fontsizes in figures
params = {'legend.fontsize': 'large',
          'axes.labelsize': 'large',
          'axes.titlesize': 'large',
          'xtick.labelsize': 'large',
          'ytick.labelsize': 'large'}
plt.rcParams.update(params)

data=np.loadtxt("Data_Earth.txt")
x=data[:,0]
y=data[:,1]

plt.plot(x,y,'r')
plt.show()
