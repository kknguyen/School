import numpy as N
import numpy.ma as MA
import matplotlib.pyplot as plt

if __name__ == "__main__":
    
    """
    A program created to read temperature data from the Surface Heat Budget
    of the Arctic (SHEBA) experiment Atmospheric Surface Flux Group (ASFG) 
    meteorological sensor tower (SHEBA was a project in the late 1990's to 
    measure climate-related variables in the Arctic Ocean)
    and store the data as a 1-D masked array, with missing values 
    masked as appropriate.
    """

    #- Open file named 'data.txt'
    fileobj = open('data.txt', 'r')
    
    #- Read in first three lines of non relevant data
    for i in range(3):
        non_relevant = fileobj.readline()
        
    #- Store the rest of the data in a list and close file
    data_str = fileobj.readlines()
    fileobj.close()
    
    #- Initialize 1-D arrays to store day and temperature data  
    days = N.zeros(len(data_str), 'd')
    temps = N.zeros(len(data_str),'d')
    
    #- Loop through and handle one line of data at a time
    for i in xrange(len(data_str)):
        data_str[i] = data_str[i].replace('\n', '\t')
        split_str = data_str[i].split('\t')
        
        #- Special case: if nothing but day in the line of data, append 3
        #-               "columns" to the line
        if len(split_str) == 2:
            split_str.append('')
            split_str.append('')
            split_str.append('')
            
        #- Convert the list to an array and replace all blank values
        #- with -9999. Then convert data type to double
        filled = N.array(split_str)
        filled[N.where(filled=='')] = '-9999'
        filled = N.array(filled).astype('d')
        
        #- Store data from column 0 into days and column 3 into temperatures
        days[i] = filled[0]
        temps[i] = filled[3]
        
    #- Mask all invalid numbers
    masked_temps = MA.masked_less(temps, -9990)
    
    #- Beginning of part 2 of the assignment. Did not complete mean, median,
    #- standard deviation calculations
    count = MA.MaskedArray.count(masked_temps)
    
    #- Create, draw, and show the graph
    plt.title('Surface Heat Budget of the Arctic')
    plt.xlabel('Julian Day')
    plt.ylabel('Temperature (celsius)')
    plt.plot(days, masked_temps)
    plt.show()