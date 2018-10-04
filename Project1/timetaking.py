from pylab import*
import numpy as np



print("Gen, n=10e1, time=", np.mean(np.array([1.1887e-5, 1.1367e-5, 1.1405e-5, 1.1486e-5,1.1574e-5])))
print("Opt, n=10e1, time=", np.mean(np.array([3.64e-7,3.82e-7,4.39e-7,3.85e-7, 3.71e-7])))
print("LUd, n=10e1, time=", np.mean(np.array([1.07288e-4,1.07193e-4,1.04877e-4,1.06845e-4,1.06282e-4])))
print("")
print("Gen, n=10e2, time=", np.mean(np.array([2.3978e-5,2.4017e-5,2.2044e-5,2.4282e-5,2.4132e-5])))
print("Opt, n=10e2, time=", np.mean(np.array([3.089e-6,3.177e-6,2.904e-6,3.119e-6,3.131e-6])))
print("LUd, n=10e2, time=", np.mean(np.array([1.05449e-3,1.07399e-3,1.00461e-3,1.07154e-3,1.05949e-3])))
print("")
print("Gen, n=10e3, time=", np.mean(np.array([6.665e-5,6.7136e-5,6.7594e-5,6.936e-5,6.8913e-5])))
print("Opt, n=10e3, time=", np.mean(np.array([2.6397e-5,2.6868e-5,2.6551e-5,2.712e-5,2.6752e-5])))
print("LUd, n=10e3, time=", np.mean(np.array([9.90859e-2,9.5715e-2,9.60053e-2,9.88432e-2,1.05186e-1])))
print("")
print("Gen, n=10e4, time=", np.mean(np.array([5.19208e-4,5.21486e-4,5.26264e-4,5.00258e-4,5.05821e-4])))
print("Opt, n=10e4, time=", np.mean(np.array([2.80609e-4,2.81583e-4,2.8333e-4,2.47253e-4,2.80837e-4])))
print("LUd, n=10e4, time=", np.mean(np.array([2.2798,2.31216,2.485,2.26689,2.27346])))
print("")
print("Gen, n=10e5, time=", np.mean(np.array([5.34878e-3,4.99248e-3,4.97204e-3,5.14921e-3,5.16681e-3])))
print("Opt, n=10e5, time=", np.mean(np.array([2.0745e-3,2.07173e-3,2.06066e-3,2.0541e-3,2.47636e-3])))
print("")
print("Gen, n=10e6, time=", np.mean(np.array([4.78849e-2,4.70058e-2,4.7658e-2,4.68383e-2,4.6578e-2])))
print("Opt, n=10e6, time=", np.mean(np.array([2.6004e-2,2.60386e-2,2.62916e-2,2.58869e-2,2.58023e-2])))
