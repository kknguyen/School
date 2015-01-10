# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

def integrate(F,x,y,xStop,h):

    def run_kut4(F,x,y,h):
        K0 = h*F(x,y)
        K1 = h*F(x + h/2.0, y + K0/2.0)
        K2 = h*F(x + h/2.0, y + K1/2.0)
        K3 = h*F(x + h, y + K2)
        return (K0 + 2.0*K1 + 2.0*K2 + K3)/6.0
    
    X = []
    Y = []
    X.append(x)
    Y.append(y)
    while x < xStop:
        h = min(h,xStop - x)
        y = y + run_kut4(F,x,y,h)
        x = x + h
        X.append(x)
        Y.append(y)
    return np.array(X),np.array(Y)

def initCond(u): # Init. values of [y,y’]; use ’u’ if unknown
    return np.array([0.0, u])
    
def r(u): # Boundary condition residual--see Eq. (8.3)
    X,Y = integrate(F,xStart,initCond(u),xStop,h)
    y = Y[len(Y) - 1]
    r = y[1] + 1.0
    return r
    
def F(x,y): # First-order differential equations
    F = np.zeros(2)
    F[0] = y[1]
    F[1] = -y[0]-y[1]/x
    return F

def linInterp(f,x1,x2):
    f1 = f(x1)
    f2 = f(x2)
    return x2 - f2*(x2 - x1)/(f2 - f1)
    
if __name__ == "__main__":
    xStart = 0.1         # Start of integration
    xStop = 2.0          # End of integration
    u1 = 1.0             # 1st trial value of unknown init. cond.
    u2 = 0.0             # 2nd trial value of unknown init. cond.
    h = 0.1              # Step size
    u = linInterp(r,u1,u2)
    X,Y = integrate(F,xStart,initCond(u),xStop,h)
    print(X)
    print(Y)

    plt.plot(X,Y)
    plt.legend(("y","dy/dx"),loc = 3)
    plt.grid(True)
    plt.show()