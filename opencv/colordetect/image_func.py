#!/usr/bin/python

import cv2
import math
import numpy as np

prev_i = cv2.imread("/shared/prev_copy.jpg")
state_i = cv2.imread("/shared/new_copy.jpg")
new_i = cv2.imread("/shared/new_copy.jpg")

THRESHOLD = 5

height, width = prev_i.shape[:2]

i = 0
j = 0


def absval(qt):
	if qt<0:
		qt = qt/-1
		return qt
	return qt


def compare_pixel(rhs,lhs,THRESHOLD):
	#check = absval(int(rhs[0])-int(lhs[0]))
	#check += absval(int(rhs[1])-int(lhs[1]))
	#check += absval(int(rhs[2])-int(lhs[2]))
	#if check <= THRESHOLD:
	if rhs[0]==lhs[0] and rhs[1]==lhs[1] and rhs[2]==rhs[2]:
		return 0
	return 1

for i in range (0,width):
        for j in range (0,height):
                if compare_pixel(state_i[i,j],prev_i[i,j],THRESHOLD):
                        new_i[i,j] = state_i[i,j]
                else:
                        new_i[i,j] = [0,0,0]

#new_i = cv2.cvtColor(new_i, cv2.COLOR_BGR2GRAY)

cv2.imwrite("diff.jpg",new_i)
