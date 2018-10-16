import sensores
GPIO.setmode(GPIO.BCM)

sensor1 = sensores.sensor("sensor1",18,24)
ListaDeSensores = [sensor1]
try:
    while True:
        sensores.sensorsLoop(ListaDeSensores)
        print("State: " + str(sensor1.state) +  " ; Timer: " + str(sensor1.timer) + " \n")

except KeyboardInterrupt:
    print("Dude porque e que me terminaste?\n")
