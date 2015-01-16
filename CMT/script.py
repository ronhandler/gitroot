#!/usr/bin/env python

import argparse
import cv2
from numpy import empty, nan
import os
import sys
import time

import CMT
import numpy as np
import util


CMT = CMT.CMT()

parser = argparse.ArgumentParser(description='Track an object.')

parser.add_argument('--preview', dest='preview', action='store_const', const=True, default=None, help='Force preview')
parser.add_argument('--no-preview', dest='preview', action='store_const', const=False, default=None, help='Disable preview')
parser.add_argument('--no-scale', dest='estimate_scale', action='store_false', help='Disable scale estimation')
parser.add_argument('--with-rotation', dest='estimate_rotation', action='store_true', help='Enable rotation estimation')
parser.add_argument('--quiet', dest='quiet', action='store_true', help='Do not show graphical output (Useful in combination with --output-dir ).')
parser.add_argument('--banana', dest='banana', help='Specify an image of a banana')

args = parser.parse_args()

CMT.estimate_scale = args.estimate_scale
CMT.estimate_rotation = args.estimate_rotation

pause_time = 10

# Clean up
#cv2.destroyAllWindows()

preview = args.preview

# If no input path was specified, open camera device
cap = cv2.VideoCapture(0)
if preview is None:
    preview = True

# Check if videocapture is working
if not cap.isOpened():
    print 'Unable to open video input.'
    sys.exit(1)

while preview:
    status, im = cap.read()
    cv2.imshow('Preview', im)
    k = cv2.waitKey(10)
    if not k == -1:
        break

if args.banana is not None:

    status, banana = cap.read()
    banana=cv2.imread(args.banana, cv2.IMREAD_GRAYSCALE )
    tl=[0,0]
    br=[banana.shape[1],banana.shape[0]]

    status, im0 = cap.read()
    im_gray0 = cv2.cvtColor(im0, cv2.COLOR_BGR2GRAY)

    # Trying to overlay banana on top of the captured frame.
    x_offset=y_offset=0
    im_gray0[y_offset:y_offset+banana.shape[0], x_offset:x_offset+banana.shape[1]] = banana

    # Temp drawing of the images. Rectangle is ignored here.
    im_draw = np.copy(im_gray0)
    (tl2, br2) = util.get_rect(im_draw)

    print 'using', tl, br, 'as init bb'
    CMT.initialise(im_gray0, tl, br)
else:
    status, im0 = cap.read()
    im_gray0 = cv2.cvtColor(im0, cv2.COLOR_BGR2GRAY)
    im_draw = np.copy(im0)
    (tl, br) = util.get_rect(im_draw)
    print 'using', tl, br, 'as init bb'
    CMT.initialise(im_gray0, tl, br)
    status, im0 = cap.read()
    im_gray0 = cv2.cvtColor(im0, cv2.COLOR_BGR2GRAY)
    im_draw = np.copy(im0)



frame = 1
while True:
    # Read image
    status, im = cap.read()

    if not status:
        break

    #if args.banana is not None:
        #im_gray = cv2.cvtColor(banana, cv2.COLOR_BGR2GRAY)
        #im_draw = np.copy(banana)
    #else:
        #im_gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
        #im_draw = np.copy(im)

    if frame<=1:
        im_gray = np.copy(im_gray0)
    else:
        im_gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
    im_draw = np.copy(im)

    tic = time.time()
    CMT.process_frame(im_gray)
    toc = time.time()

    # Display results

    # Draw updated estimate
    if CMT.has_result:
        cv2.line(im_draw, CMT.tl, CMT.tr, (0, 255, 255), 4)
        cv2.line(im_draw, CMT.tr, CMT.br, (0, 255, 255), 4)
        cv2.line(im_draw, CMT.br, CMT.bl, (0, 255, 255), 4)
        cv2.line(im_draw, CMT.bl, CMT.tl, (0, 255, 255), 4)

        util.draw_keypoints(CMT.tracked_keypoints, im_draw, (255, 255, 255))
        # this is from simplescale
        util.draw_keypoints(CMT.votes[:, :2], im_draw)  # blue
        util.draw_keypoints(CMT.outliers[:, :2], im_draw, (0, 0, 255))

    if not args.quiet:
        cv2.imshow('main', im_draw)

        # Check key input
        k = cv2.waitKey(pause_time)
        key = chr(k & 255)
        if key == 'q':
            break

    # Remember image
    im_prev = im_gray

    # Advance frame number
    frame += 1

    print '{5:04d}: center: {0:.2f},{1:.2f} scale: {2:.2f}, active: {3:03d}, {4:04.0f}ms'.format(CMT.center[0], CMT.center[1], CMT.scale_estimate, CMT.active_keypoints.shape[0], 1000 * (toc - tic), frame)

