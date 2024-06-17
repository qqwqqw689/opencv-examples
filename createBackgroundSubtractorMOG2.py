import numpy as np
import cv2

# Use the first available webcam
cap = cv2.VideoCapture(0)

# Check if the webcam is opened correctly
if not cap.isOpened():
    print("Error: Could not open webcam.")
    exit()

# Shape kernel for morphological operations
kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3, 3))

# Create a background subtractor using MOG2 method
fgbg = cv2.createBackgroundSubtractorMOG2()

while True:
    ret, frame = cap.read()
    # ret: This is a boolean value indicating whether the frame was read correctly 
    # frame: This is the actual frame captured from the video.
    if not ret:
        print("Error: Could not read frame.")
        break

    fgmask = fgbg.apply(frame)
    # Morphological opening to remove noise
    fgmask = cv2.morphologyEx(fgmask, cv2.MORPH_OPEN, kernel)
    # cv2.MORPH_OPEN indicates an opening operation,
    # which is composed of an erosion followed by a dilation

    # Find contours in the mask
    contours, hierarchy = cv2.findContours(fgmask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    # cv2.RETR_EXTERNAL retrieves only the external contours (contours on the outer boundary)
    # cv2.CHAIN_APPROX_SIMPLE compresses horizontal, vertical, and 
    # diagonal segments and leaves only their end points.
    # contours: A Python list of all the contours found in the image. 

    for c in contours:
        # Calculate the perimeter of each contour
        perimeter = cv2.arcLength(c, True)
        if perimeter > 188:
            # Find a bounding rectangle for the contour
            x, y, w, h = cv2.boundingRect(c)
            # Draw the rectangle on the original frame
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

    # Display the original frame with rectangles
    cv2.imshow('frame', frame)
    # Display the foreground mask
    cv2.imshow('fgmask', fgmask)

    # Break the loop if 'ESC' is pressed
    k = cv2.waitKey(150) & 0xff
    if k == 27:
        break

# Release the webcam and close all OpenCV windows
cap.release()
cv2.destroyAllWindows()
