import RPi.GPIO as GPIO
import time
import numpy as np
import matplotlib.pyplot as plt

dac = [26, 19, 13, 6, 5, 11, 9, 10]
leds = [21, 20, 16, 12, 7, 8, 25, 24]
bits = len(dac)
levels = 2**bits
maxVoltage = 3.3
troykamodule = 17
comp = 4

U_t = [0]

def decimal2binary(value):
    return [int(bit) for bit in bin(value)[2:].zfill(8)]


def num2dac(value):
    signal = decimal2binary(value)
    GPIO.output(dac, signal)
    return signal

def findbinary(a,b):
    if (b-a > 1):
        signal = num2dac(int(a + int((b-a)/2))) 
        time.sleep(0.01)
        compvalue = GPIO.input(comp)
        if (compvalue == 0):
            findbinary(a,a + int((b-a)/2))
        else: 
            findbinary(a + int((b-a)/2), b)
    else:
        signal = num2dac(int(a + int((b-a)/2)))
        voltage = (a/levels) * maxVoltage
        indicator(voltage)
        print("Current voltage = {: /2f}".format(voltage))
        U_t.append(voltage)

# shows voltage percent on leds       
def indicator(voltage): 
    p = int((voltage/maxVoltage)*10)
    sig = int (2**(p-1) - 0.5)
    out_sig = decimal2binary(sig)
    GPIO.output(leds, out_sig)

# initialisation
GPIO.setmode(GPIO.BCM)
GPIO.setup(dac, GPIO.OUT, initial = GPIO.LOW)
GPIO.setup(leds, GPIO.OUT, initial = GPIO.LOW)
GPIO.setup(comp, GPIO.IN)
GPIO.setwarnings(False)


try:
    start_time = time.time()
    #zaryadka
    while U_t[-1] < 3.26:
        findbinary(0,256)
        GPIO.setup(troykamodule, GPIO.OUT, initial = 1)
    #razryadka
    while U_t[-1] > 0:
        findbinary(0,256)
        GPIO.setup(troykamodule, GPIO.OUT, initial = 0)

except KeyboardInterrupt:
    print("Stopped by kb")
else: 
    print("min voltage is reached")
finally:
    #cleanup
    GPIO.output(dac, GPIO.LOW)
    GPIO.cleanup(dac)
    GPIO.cleanup(leds)
    GPIO.cleanup(troykamodule)

    print("GPIO cleanup completed")
    print("Due time equal %s" % (time.time() - start_time))
    times = np.linspace(start = 0, stop = time.time() - start_time, num = len(U_t))
    
    ### file output 
    U_t_str = [str(item) for item in U_t]
    with open("data.txt", "w") as f:
        f.write("U(t) is: \n" )
        f.write("\n".join(U_t_str))
    with open("settings.txt", "w") as f:
        f.write("Due time is: \n")
        f.write(str(time.time() - start_time))
        f.write("\ndelta t is: \n")
        f.write(str(times[1]))
        f.write("nDiscritisation is:\n")
        f.write(str((time.time() - start_time)/len(times)))
        f.write("\nDelta is:\n")
        f.write(str(3.3/255))
    ### plots of U(t)
    plt.plot(times, U_t, c="green")
    plt.show()
    
    




