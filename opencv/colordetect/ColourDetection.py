#!/usr/bin/env python
import  cv2
import  numpy   as  np

class ColourDetection(object):
    #HSV 180-255-255 max values openCV (recalculate from GIMP)
    #these need adjusting
    BOUNDARIES = {
    'red1': ([0, 50, 50], [20, 255, 255]),
    'red2': ([160, 50, 50], [179, 255, 255]),
    'blue': ([110, 50, 50], [130, 255, 255]),
    'green': ([38, 50, 50], [75, 255, 255]),
    'yellow':([103, 50, 50], [145, 255, 255])
    }

    @staticmethod
    def detect_color(detection_image):
        img_hsv = cv2.cvtColor(detection_image, cv2.COLOR_BGR2HSV)
        #loop for all defined colours
        for k,v in ColourDetection.BOUNDARIES.iteritems():
            #convert to numpty arrays
            lower_color = np.array(v[0], np.uint8)
            upper_color = np.array(v[1], np.uint8)
            #create mask from colour bounds
            mask = cv2.inRange(img_hsv, lower_color, upper_color)
            #count found colour pixels
            amount_not_zero = cv2.countNonZero(mask)
            if amount_not_zero > 9000:
                if k=='red1' or k=='red2':
                    return 'red'
                else:
                    return k
            else:
                #print("  Did not find " + k)
                continue
        return "No colour found"
