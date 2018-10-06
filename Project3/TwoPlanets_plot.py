import numpy as np
import matplotlib.pyplot as plt

# Set fontsizes in figures
params = {'legend.fontsize': 'large',
          'axes.labelsize': 'large',
          'axes.titlesize': 'large',
          'xtick.labelsize': 'large',
          'ytick.labelsize': 'large'}
plt.rcParams.update(params)

data=("Data_Earth.txt")

x=np.loadtxt(data,usecols=0)
y=np.loadtxt(data,usecols=1)
#z=np.loadtxt(data,usecols=2)

plt.plot(x,y,'r')
plt.show()
