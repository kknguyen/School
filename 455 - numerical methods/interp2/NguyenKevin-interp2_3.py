import numpy as np
import matplotlib.pyplot as plt

def gaussPivot(a,b,tol=1.0e-12):
    n = len(b)
    # Set up scale factors
    s = np.zeros(n)
    for i in range(n):
        s[i] = max(np.abs(a[i,:]))
    for k in range(0,n-1):
        # Elimination
        for i in range(k+1,n):
            if a[i,k] != 0.0:
                lam = a[i,k]/a[k,k]
                a[i,k+1:n] = a[i,k+1:n] - lam*a[k,k+1:n]
                b[i] = b[i] - lam*b[k]
    # Back substitution
    b[n-1] = b[n-1]/a[n-1,n-1]
    for k in range(n-2,-1,-1):
        b[k] = (b[k] - np.dot(a[k,k+1:n],b[k+1:n]))/a[k,k]
    return b
    
def polyFit(xData,yData,m):
    a = np.zeros((m+1,m+1))
    b = np.zeros(m+1)
    s = np.zeros(2*m+1)
    for i in range(len(xData)):
        temp = yData[i]
        for j in range(m+1):
            b[j] = b[j] + temp
            temp = temp*xData[i]
        temp = 1.0
        for j in range(2*m+1):
            s[j] = s[j] + temp
            temp = temp*xData[i]
    for i in range(m+1):
        for j in range(m+1):
            a[i,j] = s[i+j]
    return gaussPivot(a,b)
    
if __name__ == "__main__":
    xData = np.array([1.0, 2.5, 3.5, 4.0, 1.1, 1.8, 2.2, 3.7])
    yData = np.array([6.00, 15.722, 27.130, 33.772, 5.257, 9.549, 11.098, 28.828])
    
    lin = polyFit(xData,yData,1)
    quad = polyFit(xData, yData, 2)
    
    x = np.linspace(0, 5, 50)
    ylin = lin[1] * x + lin[0]
    yquad = quad[2] * x ** 2 + quad[1] * x + quad[0]
    
    plt.plot(x,ylin, x, yquad)
    plt.legend(("Linear","Quadratic"),loc = 6)
    plt.grid(True)
    plt.show()