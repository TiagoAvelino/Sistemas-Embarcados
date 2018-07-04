from picamera import PiCamera
from time import sleep
import pyzbar.pyzbar as pyzbar
import cv2

camera = PiCamera()
camera.resolution = (200, 300)
arq = open("/home/pi/Desktop/Projeto_Final/codigo.txt", "w")
aux = 0
i = 1

camera.capture('/home/pi/Desktop/Projeto_Final/output.jpg')
im = cv2.imread('output.jpg')
decodedObjects = pyzbar.decode(im)

while i:
    camera.capture('/home/pi/Desktop/Projeto_Final/output.jpg')
    im = cv2.imread('output.jpg')

    for obj in decodedObjects:
        aux = obj.data
    
    decodedObjects = pyzbar.decode(im)


    for obj in decodedObjects:
      print(obj.data)

    for obj in decodedObjects:
        if aux == obj.data:
            arq.seek(0, 0)
            arq.write(obj.data)
            i = 0

arq.close()
