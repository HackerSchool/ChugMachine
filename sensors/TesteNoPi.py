from sensores import sensor,  sensorsLoop

GPIO.setmode(GPIO.BCM)

sensor1 = sensor("sensor1",18,24)
ListaDeSensores = [sensor1]
try:
    while True:
        sensorsLoop(ListaDeSensores)
        print("State: " + str(sensor1.state) +  " ; Timer: " + str(sensor1.timer) + " \n")

except KeyboardInterrupt:
    print("Dude porque é que me terminaste?\n")
