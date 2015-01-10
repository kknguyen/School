import math

def exponential(x, tol=1e-8):
    
    """Calculates the exponential function
    
    Parameters:
        x: a scalar input used in the exponential function
        tol: the tolerance value used to determine if the series has converged
        enough (default set to 1e-8)
        
    Output:
        Returns the value of the expoential function based on input x and the
        tolerance
    """
    
    #- General variables initilized to calculate the series sum
    
    sum = 0.0
    n = 0
    tolerance = x
    
    #- Loops through to calculate sum while the ratio of calculated tolerance is
    #- greater than the tolerance set by the parameter
    
    while tolerance > tol:
        temp = sum + (x ** n / math.factorial(n))
        tolerance = (temp - sum) / x
        sum = temp
        n += 1
        
    return sum