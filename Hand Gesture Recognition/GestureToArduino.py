import time

import cv2
import numpy as np
import serial

# Set up serial communication
# Change 'COM3' to the correct port for your system
ser = serial.Serial('COM3', 9600)
time.sleep(2)  # Wait for the serial connection to initialize

# Load pre-trained hand gesture model
model = cv2.dnn.readNetFromTensorflow('hand_gesture_model.pb')

# Initialize webcam
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Prepare image for model
    blob = cv2.dnn.blobFromImage(frame, scalefactor=1.0, size=(
        224, 224), mean=(0, 0, 0), swapRB=True, crop=False)
    model.setInput(blob)
    output = model.forward()

    # Determine gesture
    gesture = np.argmax(output[0])
    print(f'Gesture Detected: {gesture}')

    # Send gesture to Arduino
    ser.write(str(gesture).encode())

    # Display frame
    cv2.imshow('Hand Gesture Recognition', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
ser.close()
