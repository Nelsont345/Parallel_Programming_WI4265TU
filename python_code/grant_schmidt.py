#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Mon Feb 24 14:24:32 2020

@author: nelson
"""

from mpi4py import MPI
import numpy as np

dimensions = 4

np.random.seed(1)
matrix_values = np.array([[np.random.rand(1) for i in range(dimensions)]for j in range(dimensions)])

#%% calculate ck
c_set = [0 for i in range(dimensions)]
new_matrix = []
for i in range(dimensions):
    current_column = matrix_values[:,i]  #current column
    for j in np.arange(0, i):
        multiplication_column = matrix_values[:,j]  #current column
        c_set[i] += current_column*multiplication_column
    
    new_column = current_column
    for j in range(i):
         
        new_column -= c_set[j]*matrix_values[:,j] 
    new_matrix.append(new_column/abs(sum(new_column)))
    
    
        
    
        
print(new_matrix)