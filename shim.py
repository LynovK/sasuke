import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(22, GPIO.OUT, initial = 0)
p = GPIO.PWM(22, 10)
 
def ChangeDutyCycle(dutycycle):
    p.start(dutycycle)

try:
    while True:
        inputStr = input("Введите число от 0 до 100, 'q' для выхода >")

        if inputStr.isdigit():
            dutycycle = int(inputStr)
            if dutycycle > 100:
                print ("Error")
                continue
            ChangeDutyCycle(dutycycle)
        elif inputStr == 'q':
            break
        else:
            print ("Error")
finally:
    p.stop()
    GPIO.cleanup()
