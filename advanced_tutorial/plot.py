import numpy as np
import matplotlib.pyplot as plt
import sys
import os

filename_plot = sys.argv[1]
infilename = sys.argv[2]

def analytical(x):
    return 1 - (1-np.exp(-10))*x - np.exp(-10*x)

x = [0] #boundary conditions  x0 = 0
u = [0] #boundary condition u(0) = 0

with open(infilename, "r") as infile:
    lines = infile.readlines()
    for line in lines:
        vals = line.split()
        x.append(float(vals[0]))
        u.append(float(vals[1]))

x.append(1) #boundary condition xn+1 = 1
u.append(0) #boundary condition u(1) = 0
X = np.linspace(0,1,1001)
func_vals = analytical(X)
plt.plot(x,u, label = "Numerical solution")
plt.plot(X,func_vals, label = "analytical")
plt.xlabel("x")
plt.ylabel("u(x)")
plt.legend()
plt.savefig(filename_plot)
#plt.show()
