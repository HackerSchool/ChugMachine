#Este script tem tudo o que e preciso para controlar e saber o estado dos sensores,
#para corre lo basta chamar a funcao sensorsLoop(ListaDeSensores).
#a classe "sensor" e as funcoes dela sao super simples, mas como foram feitas
#em blocos simples e separados, da para alterar facilmente cada estado e cada transicao
#Em principio basta criar uma lista de sensores na main.py e, em cada loop da main ou do
#jogo chamar a sensorsLoop(ListaDeSensores) para isto funcionar


#Libraries
import RPi.GPIO as GPIO
import time

class sensor:
    def __init__(self, name,TRIGGER,ECHO):
        self.name = name #nome do sensor
        self.trigger = TRIGGER #num do pin de pin de trigger (no pi)
        self.echo = ECHO #num do pin de echo (no pi)
        self.timer = 0.0 #guarda o tempo desde que o sensor foi ativado
        self.state = 0 #guarda o estado do sensor : 0-> sensor em stand by; 1-> sensor em contagem
        self.previousTimer = 0.0 #talvez fazer uma lista de timers??
        self.startTime = 0.0 #guarda o tempo no instante em que foi iniciado o timer (ver time.time() para mais info)

        #Para definir os pins de entrada e de saida
        GPIO.setup(self.trigger,   GPIO.OUT)
        GPIO.setup(self.echo, GPIO.IN)


# Function to calculate the distance measured by the sensor


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
        minDist = 27.5 #cms


        if (self.state == 0 and self.distance() > minDist ):
            #condition to transition from state 0->1
            self.state0To1()

        if(self.state ==1):
            self.doState1()

        if(self.state == 1 and self.distance() <= minDist):
            self.state1To0()




    def state0To1(self):
        self.startTime = time.time()
        self.state = 1

    def state1To0(self):
        self.previousTimer = self.timer
        self.timer = 0.0
        self.state = 0

    def doState1(self):
        self.timer = time.time() - self.startTime


def sensorsLoop(ListaDeSensores):
    for sensor in ListaDeSensores:
        sensor.figureOutNextState()



#GPIO Mode (BOARD / BCM)
#GPIO.setmode(GPIO.BCM)
#Exemplo de variaveis:
#sensor1 = sensor("sensor1",18,24)
#sensor2 = sensor("sensor2",13,15)

#sensors = [sensor1,sensor2]
