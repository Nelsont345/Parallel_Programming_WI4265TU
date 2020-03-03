#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Wed Feb 26 19:06:07 2020

@author: nelson
"""
#makes othogonal rows and does not normalise

import numpy

def gs_cofficient(v1, v2):
    return numpy.dot(v2, v1) / numpy.dot(v1, v1)

def multiply(cofficient, v):
    return map((lambda x : x * cofficient), v)

def proj(v1, v2):
    return multiply(gs_cofficient(v1, v2) , v1)

def gs(X):
    Y = []
    for i in range(len(X)):
        temp_vec = X[i]
        for inY in Y :
            proj_vec = proj(inY, X[i])
            #print "i =", i, ", projection vector =", proj_vec
            temp_vec = map(lambda x, y : x - y, temp_vec, proj_vec)
            #print "i =", i, ", temporary vector =", temp_vec
        Y.append(temp_vec)
    return Y

test = numpy.array([[3.0, 1.0], [2.0, 2.0]])
test2 = numpy.array([[1.0, 1.0, 0.0], [1.0, 3.0, 1.0], [2.0, -1.0, 1.0]])
dimensions = 4
numpy.random.seed(0)
test3 = numpy.array([[0.5488135 , 0.71518937, 0.60276338, 0.54488318],
        [0.24955165, 0.64589411, 0.43758721, 0.891773  ],
        [0.06058404, 0.38344152, 0.79172504, 0.52889492],
        [0.56804456, 0.92559664, 0.07103606, 0.0871293 ]])
#print numpy.array(gs(test))
print numpy.array(gs(test2))
#print numpy.array(gs(test3))