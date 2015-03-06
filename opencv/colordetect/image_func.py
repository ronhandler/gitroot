
import cv2
import math
import numpy as np

def diff_func(prev_i,state_i):
    #new_i = cv2.imread("/shared/new_copy.jpg")
    # This is a weird way to define new_i as an image...
    new_i = prev_i

    #THRESHOLD = input('Please enter your requested level of Threshold')
    THRESHOLD = 5

    height, width = prev_i.shape[:2]
    i = 0
    j = 0
    #width = width - 1
    #height = height - 1
    for i in range (0,width):
        for j in range (0,height):
            if compare_pixel(state_i[j,i],prev_i[j,i],THRESHOLD):
                new_i[j,i] = state_i[j,i]
            else:
                new_i[j,i] = [0,0,0]

    #new_i = cv2.cvtColor(new_i, cv2.COLOR_BGR2GRAY)
    return new_i

def absval(qt):
    if qt<0:
        qt = qt/-1
        return qt
    return qt

def trans_scalar_level(input_num,THRESHOLD):
    x = (input_num/THRESHOLD)*10
    return round(x)

def compare_pixel(rhs,lhs,THRESHOLD):
    check = absval(int(rhs[0])-int(lhs[0])) + absval(int(rhs[1])-int(lhs[1])) + absval(int(rhs[2])-int(lhs[2]))
    if check <= THRESHOLD:
        #if rhs[0]==lhs[0] and rhs[1]==lhs[1] and rhs[2]==rhs[2]:
        return 0
    return 1
    #return trans_scalar_level(check,THRESHOLD)
