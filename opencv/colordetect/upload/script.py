#!/usr/bin/python

import detect
from boto.s3.connection import S3Connection
 
AWS_ACCESS_KEY_ID = '********************'
AWS_SECRET_ACCESS_KEY = '****************************************'
BUCKET_NAME = 'ronhandler'
filename="new.jpg"
aws_connection = S3Connection(AWS_ACCESS_KEY_ID, AWS_SECRET_ACCESS_KEY)
bucket = aws_connection.get_bucket(BUCKET_NAME)
print('Downloading from bucket...')
k = bucket.get_key('new.jpg')
if k == None:
    print('Error. Could not find key in bucket.')
    exit(1)
k.get_contents_to_filename('/upload/new.jpg')
print('Deleting from bucket...')
bucket.delete_key(k)

print('Detecting color...')
detect.Detect()
