#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Sun Feb 23 16:58:21 2020

@author: nelson
"""

from mpi4py import MPI
import numpy as np

comm = MPI.COMM_WORLD
rank = MPI.COMM_WORLD.Get_rank()

length = 16
no_of_processors = 4

#%% pre-processing

register = [i for i in range(16)]
new_register = [len(register) for i in enumerate(register)]

loop_length = int(len(register)/no_of_processors )

#%% parallel loops    
if rank == 0:
    new_register[0] = comm.recv(source = no_of_processors-1, tag =11) #receive data from processor 3
    for i in np.arange(1, loop_length): #internal process
            new_register[i] = register[i-1]
    comm.isend(register[loop_length -1], dest=1, tag =11)
  
elif rank > 0 and rank < no_of_processors-1:
    new_register[rank*loop_length] = comm.irecv(source = rank-1, tag =11)
    for i in np.arange(rank*loop_length, rank*loop_length+loop_length):
            new_register[i] = register[i-1]
    comm.isend(register[loop_length*rank + 1], dest=rank+1, tag =11)
   
    
    
else:
    new_register[-1] = comm.irecv(source = no_of_processors-2, tag =11) #receive data from processor 2
    for i in np.arange(rank*loop_length, loop_length*rank+loop_length):
            new_register[i] = register[i-1]
    comm.isend(register[-1], dest=0, tag =11)
    print(rank)

    
print(new_register)