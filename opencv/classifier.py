#!/usr/bin/python

import numpy as np
import cv2

#face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
#eye_cascade = cv2.CascadeClassifier('haarcascade_eye.xml')
banana_cascade = cv2.CascadeClassifier('banana.xml')

img = cv2.imread('Banana.png')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

for (x,y,w,h) in banana_cascade.detectMultiScale(gray, 1.3, 5):
    cv2.rectangle(img,(x,y),(x+w,y+h),(0,0,0),3)

cv2.imshow('img',img)
cv2.waitKey(0)
cv2.destroyAllWindows()


