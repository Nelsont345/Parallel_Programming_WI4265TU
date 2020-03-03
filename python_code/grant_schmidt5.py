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

dimensions = 3

np.random.seed(0)
#matrix_values = np.array([[np.random.rand(1) for i in range(dimensions)]for j in range(dimensions)])
matrix_values = np.array([[1.0, 1.0, 0.0], [1.0, 3.0, 1.0], [2.0, -1.0, 1.0]]) #columns
#%% calculate ck



    
    
def calc_new_row_elements(row):
    """Calculates a new unormalised row element"""
    c_set = [[0.,1.] for i in range(dimensions)]
    print(row)
    for i in np.arange(0, len(row)-1):
        current_element = row[i]
        print(current_element)
        for j in np.arange(0,i):
            multiplication_element = row[j]
            c_set[i][0] += (current_element*multiplication_element)
            c_set[i][1] += (current_element*current_element)
    
    return c_set

            
if rank == 0:
    c_set_0  = np.array(calc_new_row_elements(matrix_values[:,0]))
#    data = new_row_unormalised*new_row_unormalised
    comm.send(c_set_0, dest=1, tag=11)
    complete_c_set = comm.recv(source=dimensions-1, tag=11)
#    print(complete_c_set)
    c_read_set = np.array([e[0]/e[1] for i,e in enumerate(complete_c_set)])
#    print(c_read_set)
    for i in np.arange(1, dimensions):  
        comm.send(c_read_set, dest=i, tag=12)    
    print(matrix_values[:,0]*(1-c_read_set), rank)    
        
elif rank > 0 and rank < dimensions-1:
    new_set = comm.recv(source=rank-1, tag=11)
    new_set += np.array(calc_new_row_elements(matrix_values[:,rank]))
    comm.send(new_set, dest=rank+1, tag=11)
    complete_c_set = comm.recv(source=0, tag=12)
    print(matrix_values[:,rank]*(1-complete_c_set), rank)
    
else:
    new_set = comm.recv(source=dimensions-2, tag=11)
    new_set += np.array(calc_new_row_elements(matrix_values[:,rank]))   
    comm.send(new_set, dest=0, tag=11) 
    complete_c_set = comm.recv(source=0, tag=12)
    print(matrix_values[:,rank]*(1-complete_c_set), rank) 

    
   