#Libraries
import RPi.GPIO as GPIO
import time

class sensor:
    def __init__(self, name,TRIGGER,ECHO):
        self.name = name
        self.trigger = TRIGGER
        self.echo = ECHO
        self.timer = 0
        self.state = 0

        GPIO.setup(self.trigger,   GPIO.OUT)
        GPIO.setup(self.echo, GPIO.IN)


    def distance(self):
        # set Trigger to HIGH
        GPIO.output(self.trigger, True)

        # set Trigger after 0.01ms to LOW
        time.sleep(0.00001)
        GPIO.output(self.trigger, False)

        StartTime = time.time()
        StopTime = time.time()

        # save StartTime
        while GPIO.input(self.echo) == 0:
            StartTime = time.time()

        # save time of arrival
        while GPIO.input(self.echo) == 1:
            StopTime = time.time()

        # time difference between start and arrival
        TimeElapsed = StopTime - StartTime
        # multiply with the sonic speed (34300 cm/s)
        # and divide by 2, because there and back
        distance = (TimeElapsed * 34300) / 2

        return distance

    def figureOutNextState(self):

    def state










    0(self):

    def state1(self):

    def state2(self):







#GPIO Mode (BOARD / BCM)
GPIO.setmode(GPIO.BCM)

sensor1 = sensor("sensor1",18,24)





#set GPIO Pins
#GPIO_TRIGGER = 18
#GPIO_ECHO = 24