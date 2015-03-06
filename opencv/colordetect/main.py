#!/usr/bin/env python
import cv2
import numpy as np
from ColourDetection import *
from image_func import *

#image = np.zeros((512, 512, 3), np.uint8)
#image[:,0:512] = (0, 255, 0) # Green in BGR.
#image[:,0:512] = (0, 0, 255) # Red in BGR.
#image[:,0:512] = (255, 0, 0) # Blue in BGR.

cap = cv2.VideoCapture(0)
ret, new_image = cap.read()

old_image = cv2.imread('old.jpg')


height1, width1 = old_image.shape[:2]
height2, width2 = new_image.shape[:2]

#print("The sizes are:" + str(width1) + "x" + str(height1))
#print("The sizes are:" + str(width2) + "x" + str(height2))

diff_image = diff_func(new_image, old_image);

color = ColourDetection.detect_color(diff_image)
print("The returned color is: " + color)
cv2.imwrite('old.jpg', new_image)

