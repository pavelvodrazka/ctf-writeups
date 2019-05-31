#!/usr/bin/env python3

import os
import sys
import cv2 as cv
import numpy as np

def count_eggs(image_file, show_keypoints = False):
    filtered = filter_image(image_file)

    # setup blob detector parameters
    params = cv.SimpleBlobDetector_Params()
    params.filterByColor = True
    params.blobColor = 0
    params.filterByConvexity = False
    params.filterByInertia = True
    params.minInertiaRatio = 0.4
    params.filterByArea = True
    params.minArea = 1500
    params.maxArea = 5000
    params.filterByCircularity = False

    # detect blobs
    detector = cv.SimpleBlobDetector_create(params)
    keypoints = detector.detect(filtered)

    # show keypoints
    if show_keypoints:
        img_with_keypoints = cv.drawKeypoints(filtered, keypoints, np.array([]), (0, 0, 255), cv.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
        show_image(img_with_keypoints, 'keypoints')

    return len(keypoints)

def filter_image(image_file):
    grayscale = cv.imread(image_file, cv.IMREAD_GRAYSCALE)

    filtered = cv.adaptiveThreshold(grayscale, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C, cv.THRESH_BINARY_INV, 7, 4)
    filtered = cv.GaussianBlur(filtered, (21, 21), 0)
    _, filtered = cv.threshold(filtered, 40, 255, cv.THRESH_BINARY)

    return filtered

def show_image(image, title):
    resized_width = int(image.shape[1] * 0.5)
    resized_height = int(image.shape[0] * 0.5)
    resized = cv.resize(image, (resized_width, resized_height), interpolation = cv.INTER_AREA)

    cv.imshow(title, resized)

img_file = sys.argv[1]

if not os.path.isfile(img_file):
    print(img_file + ' is not a file!')
    exit(-1)

show_img = len(sys.argv) > 2 and sys.argv[2] == 'show'

eggs = count_eggs(img_file, show_img)
print(eggs)

cv.waitKey()
