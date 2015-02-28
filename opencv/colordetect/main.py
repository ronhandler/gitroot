#!/usr/bin/env python
import cv2
import numpy as np
from ColourDetection import *

image = np.zeros((512, 512, 3), np.uint8)
image[:,0:512] = (0, 255, 0) # Green in BGR.
#image[:,0:512] = (0, 0, 255) # Red in BGR.
#image[:,0:512] = (255, 0, 0) # Blue in BGR.
color = ColourDetection.detect_color(image)
print("The returned color is: " + color)
#cv2.imwrite('output.jpg', image)
