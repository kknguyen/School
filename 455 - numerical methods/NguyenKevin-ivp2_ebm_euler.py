import numpy as N
import matplotlib.pyplot as plt
    
def T(xinit, A, t):
    return (342.5*(1-A)-0.62*(5.67*10**-8)*(xinit**4))*t/(2.06*10**8)

if __name__ == "__main__":
    """
    Program to calculate and determine temperature based on the zero-dimensional
    energy balance model
    
    Uses function T(xinit, A, T) to calculate the change in temperature
    """
    dt = N.zeros(50, 'd')
    
    #- Array to hold data for 288 K initial temp
    dT288 = N.zeros(50, 'd')
    
    for i in xrange(50):
        dt[i] = i
        dT288[i] = T(288.0, 0.3, 345600000+i*(86400))
    
    #plt.title('288K Initial Temperature')    
    #plt.xlabel('Day')
    #plt.ylabel('Change in temperature (K)')
    #plt.plot(dt,dT288)
    #plt.show()
    
    #- Array to hold data for 286 K initial temp
    dT286 = N.zeros(50, 'd')
    
    for i in xrange(50):
        dT286[i] = T(286.0, 0.3, 345600000+i*(86400))
    
    plt.title('286K Initial Temperature')
    plt.xlabel('Day')
    plt.ylabel('Change in temperature (K)')
    plt.plot(dt,dT286)
    plt.show()
    
    