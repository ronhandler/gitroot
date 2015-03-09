#!/usr/bin/env python
import sys
import os.path
import cv2
import numpy as np

import boto
from boto.s3.key import Key

cap = cv2.VideoCapture(0)
ret, new_image = cap.read()
if ret == False:
    exit(1)
filename = 'new.jpg'
cv2.imwrite(filename, new_image)

bucket_name = 'ronhandler'
AWS_ACCESS_KEY_ID = 'AKIAIYLDR3LU2XDICTSQ'
AWS_SECRET_ACCESS_KEY = '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'

print('Connecting to AWS S3...')
conn = boto.connect_s3(AWS_ACCESS_KEY_ID,
        AWS_SECRET_ACCESS_KEY,
        # Hardcoding the host parameter is a workaround for bug:
        # https://github.com/boto/boto/issues/621
        host="s3-eu-west-1.amazonaws.com")
bucket = conn.get_bucket(bucket_name)

k = Key(bucket)
k.key = filename

testfile =  "/share/" + filename
print('Uploading "%s" to "%s/%s"...' % (testfile, bucket_name, k.key))

k.set_contents_from_filename(testfile)

print('Notifying the server that we have uploaded a file...')
import urllib2
url = """http://ec2-52-16-188-96.eu-west-1.compute.amazonaws.com/admin/run.php"""
urllib2.urlopen(url).read()
