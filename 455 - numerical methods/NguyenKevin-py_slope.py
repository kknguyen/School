import numpy as N

def slope(x, y):
    
    """Calculates slope of two arrays
    
    Parameters:
        x: array of x values; can be irregularly spaced, but need to be in
        ascending order
        
        y:array of y values, should contain the equal number of elements as x
        
    Output:
        Returns the slope at each x value in a new array
    """
    
    #- Create a new array and store the size in a variable
    
    slope_arr = N.zeros(N.size(x))
    size = N.size(y)
    
    #- Compute first edge case; use forward differencing
    
    slope_arr[0] = (y[1] - y[0]) / (x[1] - x[0])

    #- Loop through array (minus first and last element) and use central
    #- differencing to compute slope
    
    for i in range(1, size-1):
        slope_arr[i] = (y[i+1] - y[i-1]) / (x[i+1] - x[i-1])
        
    #- Compute last edge case; use backward differencing
    slope_arr[size-1] = (y[size-1] - y[size-2]) / (x[size-1] - x[size-2])
    
    return slope_arr
    
if __name__ == "__main__":
    
    dist = 500.0
    
    alpha1 = N.radians(54.80)
    alpha2 = N.radians(54.06)
    alpha3 = N.radians(53.34)
    
    beta1 = N.radians(65.59)
    beta2 = N.radians(64.59)
    beta3 = N.radians(63.62)
    
    x1 = dist * N.tan(beta1) / (N.tan(beta1) - N.tan(alpha1))
    x2 = dist * N.tan(beta2) / (N.tan(beta2) - N.tan(alpha2))
    x3 = dist * N.tan(beta3) / (N.tan(beta3) - N.tan(alpha3)) 
    
    y1 = dist * (N.tan(alpha1) * N.tan(beta1)) / (N.tan(beta1) - N.tan(alpha1))
    y2 = dist * (N.tan(alpha2) * N.tan(beta2)) / (N.tan(beta2) - N.tan(alpha2))
    y3 = dist * (N.tan(alpha3) * N.tan(beta3)) / (N.tan(beta3) - N.tan(alpha3))
    
    xVal = N.array([x1, x2, x3])
    yVal = N.array([y1, y2, y3])
    
    slopes = slope(xVal, yVal)

    print(xVal)
    print(yVal)
    print(slopes[1])
 