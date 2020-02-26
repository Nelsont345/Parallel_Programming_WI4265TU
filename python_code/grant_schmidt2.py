#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Mon Feb 24 14:24:32 2020

@author: nelson
"""

from mpi4py import MPI
import numpy as np

comm = MPI.COMM_WORLD
rank = MPI.COMM_WORLD.Get_rank()

dimensions = 4

np.random.seed(1)
matrix_values = np.array([[np.random.rand(1) for i in range(dimensions)]for j in range(dimensions)])

#%% calculate ck
c_set = [0 for i in range(dimensions)]
#new_matrix = np.array([[1 for i in range(dimensions)]for j in range(dimensions)])

row = [[] for i in range(dimensions)]
new_row = np.array([[1. for i in range(dimensions)] for i in range(dimensions)])

if rank == 0:
    data = []
    new_matrix = [] 
    row  = matrix_values[:,0]
    for i in range(dimensions):
        current_element = matrix_values[0,i]  #current element
        for j in np.arange(0, i):
            multiplication_element = matrix_values[0,j]  #current element
            c_set[i] += current_element*multiplication_element
        
        new_element = current_element
        for j in range(i):
             
            new_element -= c_set[j]*row[j] 
        new_row[i,0] = new_element
    data.append(new_row[:,0])
    for i in np.arange(1, dimensions):
        data.append(comm.recv(source = i))
        new_matrix = data
#        print(new_matrix)
    print(new_matrix)
    
else:
    row  = matrix_values[:,rank-1]
    for i in range(dimensions):
        current_element = matrix_values[rank,i]  #current element
        for j in np.arange(0, i):
            multiplication_element = matrix_values[rank,j]  #current element
            c_set[i] += current_element*multiplication_element
        
        new_element = current_element
        for j in range(i):
             
            new_element -= c_set[j]*row[j] 
        new_row[rank, i] = new_element
#    print(new_row[rank])
    comm.send(new_row[rank], dest=0)
    
        
    