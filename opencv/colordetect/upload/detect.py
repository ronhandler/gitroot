#!/usr/bin/env python
import os.path
import cv2
import numpy as np
from ColourDetection import *
from image_func import *

def Detect():
    new_image = cv2.imread('/upload/new.jpg')
    # If the old image exists:
    if os.path.isfile('/upload/old.jpg') :
        old_image = cv2.imread('/upload/old.jpg')
        cv2.imwrite('/upload/old.jpg', new_image)
        # Generate a diff image.
        diff_image = diff_func(old_image, new_image);
        color = ColourDetection.detect_color(diff_image)
    # Otherwise, there is no old image:
    else:
        cv2.imwrite('/upload/old.jpg', new_image)
        color = ColourDetection.detect_color(new_image)

    print("The detected color is: " + color)

    if color != "No colour found":
        # Push the color to the local web server.
        import urllib2 
        url = """http://localhost/admin/push.php?color=""" + color
        urllib2.urlopen(url).read()
    return

