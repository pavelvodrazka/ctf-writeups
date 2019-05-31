#!/usr/bin/env python3

import os
import sys
import cv2 as cv

def filter_image(image_file):
    original = cv.imread(image_file, cv.IMREAD_COLOR)

    show_image(original, 'original')

    grayscale = cv.imread(image_file, cv.IMREAD_GRAYSCALE)

    filtered = cv.adaptiveThreshold(grayscale, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C, cv.THRESH_BINARY_INV, 7, 4)
    filtered = cv.GaussianBlur(filtered, (21, 21), 0)
    _, filtered = cv.threshold(filtered, 40, 255, cv.THRESH_BINARY)

    show_image(filtered, 'filtered')

def show_image(image, title):
    resized_width = int(image.shape[1] * 0.5)
    resized_height = int(image.shape[0] * 0.5)
    resized = cv.resize(image, (resized_width, resized_height), interpolation = cv.INTER_AREA)

    cv.imshow(title, resized)

img_file = sys.argv[1]

if not os.path.isfile(img_file):
    print(img_file + ' is not a file!')
    exit(-1)

filter_image(img_file)

cv.waitKey()
