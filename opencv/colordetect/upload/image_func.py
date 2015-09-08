#!/usr/bin/python

import cv2
import math
import numpy as np

#images uploading / not mandatory in case of calling the function from other scope

#pre = cv2.imread("/shared/prev_copy.jpg")
#post = cv2.imread("/shared/new_copy.jpg")

# some global vars

LOWER_LIMIT = 0    # At your choice for threshold
ABSPIXEL = 255*3    # The value of the sum of pix
FACTOR = 3          # Scalar using us to enhance - working in the contrary to LOWER_LIMIT 

def trans_scalar_level(val_of_transform):   # Transformation calculus function -> returning scalar 
    return FACTOR*val_of_transform/float(ABSPIXEL)

def compare_pixel(rhs,lhs,limit):       # Comparison function - sums the absolute diff in pixes values
    check = abs(int(rhs[0])-int(lhs[0])) + abs(int(rhs[1])-int(lhs[1])) + abs(int(rhs[2])-int(lhs[2]))
    if check <= limit:
        return 0
    return trans_scalar_level(check)

# "Main Function" - returning an image of diffrances between to images
def diff_func(pre, post):
    new_i = pre
    height, width = pre.shape[:2]
    for i in range (0,width):
        for j in range (0,height):
            new_i[j,i] = compare_pixel(post[j,i],pre[j,i],LOWER_LIMIT)*np.array(post[j,i])
    return new_i
