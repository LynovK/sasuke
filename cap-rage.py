import RPi.GPIO as GPIO
dac = [26, 19, 13, 6, 5, 11, 9, 10]
import time
bits = len(dac)
levels = 2**bits
maxVoltage = 3.3
i = 0
def decimal2binary(decimal):
    return [int(bit) for bit in bin(decimal)[2:].zfill(bits)]
def bin2dac(value):
    signal = decimal2binary(value)
    GPIO.output(dac, signal)
    return signal
GPIO.setmode(GPIO.BCM)
GPIO.setup(dac, GPIO.OUT, initial = GPIO.LOW)
try:
    while True:
        for i in range(255):
            bin2dac(i)
            print(i)
            time.sleep(0.01)
        i = 255
        while i >= 0:
            bin2dac(i)
            print(i)
            time.sleep(0.01)
            i = i-1
finally:
    GPIO.output(dac, GPIO.LOW)
    GPIO.cleanup(dac)
    print("GPIO cleanup completed")