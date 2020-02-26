#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Sat Feb 22 22:10:36 2020

@author: nelson
"""

from mpi4py import MPI
from subprocess import call

comm = MPI.COMM_WORLD
rank = MPI.COMM_WORLD.Get_rank()
print (comm.rank, comm.size)

#cmd = "processCcd.py DATA --rerun processCcdOutputs --id visit=%d ccd=%d" % (visit, ccd)
cmd = "sleep 3"
call(cmd, shell=1)

#MPI.Init()    #occurs automatically

end = 5  #relates to number of processors

if rank == 0:
    data = 4#{'a': 7, 'b': 3.14}
    comm.send(data, dest=1, tag=11)
    data = comm.recv(source=end-1, tag=11)
    print(data)
elif rank  > 0 and rank < end-1:
    data = comm.recv(source=rank-1, tag=11)
    data = data*4
    comm.send(data, dest=rank+1, tag=11)
else:
    data = comm.recv(source = end-2, tag=11)
    data = data*4
    comm.send(data, dest=0, tag=11)
    
    
    

 
    
#MPI.Finalize()  #occurs automatically