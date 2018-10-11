import numpy as np
import matplotlib.pyplot as plt

# Set fontsizes in figures
params = {'legend.fontsize': 'large',
          'axes.labelsize': 'large',
          'axes.titlesize': 'large',
          'xtick.labelsize': 'large',
          'ytick.labelsize': 'large'}
plt.rcParams.update(params)

data=np.loadtxt("solarsystemData.txt")
x=data[:,0]
y=data[:,1]

x1=data[:,6]
y1=data[:,7]

x2=data[:,12]
y2=data[:,13]

plt.plot(x,y,'r')
plt.plot(x1,y1,'b')
plt.plot(x2,y2,'g')
plt.show()
