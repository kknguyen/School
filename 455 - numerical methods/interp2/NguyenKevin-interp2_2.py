import numpy as np
import matplotlib.pyplot as plt

def LUdecomp3(c,d,e):
    n = len(d)
    for k in range(1,n):
        lam = c[k-1]/d[k-1]
        d[k] = d[k] - lam*e[k-1]
        c[k-1] = lam
    return c,d,e
def LUsolve3(c,d,e,b):
    n = len(d)
    for k in range(1,n):
        b[k] = b[k] - c[k-1]*b[k-1]
    b[n-1] = b[n-1]/d[n-1]
    for k in range(n-2,-1,-1):
        b[k] = (b[k] - e[k]*b[k+1])/d[k]
    return b

def curvatures(xData,yData):
    n = len(xData) - 1
    c = np.zeros(n)
    d = np.ones(n+1)
    e = np.zeros(n)
    k = np.zeros(n+1)
    c[0:n-1] = xData[0:n-1] - xData[1:n]
    d[1:n] = 2.0*(xData[0:n-1] - xData[2:n+1])
    e[1:n] = xData[1:n] - xData[2:n+1]
    k[1:n] =6.0*(yData[0:n-1] - yData[1:n]) \
                /(xData[0:n-1] - xData[1:n]) \
                -6.0*(yData[1:n] - yData[2:n+1]) \
                /(xData[1:n] - xData[2:n+1])
    LUdecomp3(c,d,e)
    LUsolve3(c,d,e,k)
    return k
    
def evalSpline(xData,yData,k,x):
    def findSegment(xData,x):
        iLeft = 0
        iRight = len(xData)- 1
        while 1:
            if (iRight-iLeft) <= 1: return iLeft
            i =(iLeft + iRight)/2
            if x < xData[i]: iRight = i
            else: iLeft = i
    i = findSegment(xData,x)
    h = xData[i] - xData[i+1]
    y = ((x - xData[i+1])**3/h - (x - xData[i+1])*h)*k[i]/6.0 \
        - ((x - xData[i])**3/h - (x - xData[i])*h)*k[i+1]/6.0 \
        + (yData[i]*(x - xData[i+1]) \
        - yData[i+1]*(x - xData[i]))/h
    return y
    
if __name__ == "__main__":
    xData = np.array([0.1, 0.2, 0.4, 0.5, 0.75, 1.0, 1.5])
    yData = np.array([0.56, 0.83, 1.05, 1.28, 1.55, 1.75, 2.22])
    yInterpolant = np.zeros(20)
    xInterpolant = np.zeros(20)
    k = curvatures(xData, yData)
    for i in xrange(20):
        yInterpolant[i] = evalSpline(xData, yData, k, i*0.1)
        xInterpolant[i] = i*0.1

    
    plt.plot(xInterpolant,yInterpolant)
    plt.title("Period (T) vs Mass (kg)")
    plt.grid(True)
    plt.show()