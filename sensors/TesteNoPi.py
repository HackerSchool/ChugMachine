import sensores.py

GPIO.setmode(GPIO.BCM)

sensor1 = sensor("sensor1",18,24)
ListaDeSensores = [sensor1]
try:
    while True:
        sensorsLoop(ListaDeSensores)
        print("State: " sensor1.state" ; Timer: " sensor1.timer " \n")

exceptKeyboardInterrupt:
    print("Dude porque é que me terminaste?\n")
