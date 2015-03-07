#!/usr/bin/env python
import os.path
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
# If the old image exists:
if os.path.isfile('old.jpg') :
    old_image = cv2.imread('old.jpg')
    cv2.imwrite('old.jpg', new_image)
    # Generate a diff image.
    diff_image = diff_func(old_image, new_image);
    color = ColourDetection.detect_color(diff_image)
    
    cv2.imshow('new_image',new_image)
    cv2.imshow('old_image',old_image)
    cv2.imshow('diff_image',diff_image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    color = ColourDetection.detect_color(diff_image)
# Otherwise, there is no old image:
else:
    cv2.imwrite('old.jpg', new_image)
    color = ColourDetection.detect_color(new_image)

print("The detected color is: " + color)

