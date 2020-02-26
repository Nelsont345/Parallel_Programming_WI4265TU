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

np.random.seed(1)
matrix_values = np.array([[np.random.rand(1) for i in range(dimensions)]for j in range(dimensions)])

#%% calculate ck

def calc_new_row_elements(row):
    c_set = [0. for i in range(dimensions)]
    new_row = row
    for i in np.arange(1, len(row)):
        current_element = row[i]
        for j in np.arange(0,i):
            multiplication_element = row[j]
            c_set[i] += current_element*multiplication_element
        for j in np.arange(0,i):
            new_row[j] -= c_set[j]*row[j] 
    return new_row
            
if rank == 0:
    #
    new_row_unormalised  = np.array(calc_new_row_elements(matrix_values[:,0]))
    data = new_row_unormalised*new_row_unormalised
    comm.send(data, dest=1, tag=11)
    normailisation_costant = comm.recv(source=dimensions-1, tag=11)
    print(new_row_unormalised, rank )
    print(normailisation_costant)        
        
elif rank > 0 and rank < dimensions-2:
    normalisation_vector = comm.recv(source=rank-1, tag=11)
    new_row_unormalised  = np.array(calc_new_row_elements(matrix_values[:,rank]))
    data = new_row_unormalised+(new_row_unormalised*new_row_unormalised)
    print(new_row_unormalised, rank)
    comm.send(data, dest=rank+1, tag=11)
    
else:
    normalisation_vector = comm.recv(source=dimensions-2, tag=11)
    new_row_unormalised  = np.array(calc_new_row_elements(matrix_values[:,rank]))   
    data = normalisation_vector+(new_row_unormalised*new_row_unormalised)
    comm.send(data, dest=0, tag=11) 
    print(new_row_unormalised, rank )
    