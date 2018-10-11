import sensores.py

state = 0;

while True:
    if state == 0: #waiting
        #RESET TIMER
        #WAITING FOR START BUTTON TO BE PRESSED
        n_penalties = int(input ("Quantos penalties vão beber?"))
        state += 1
