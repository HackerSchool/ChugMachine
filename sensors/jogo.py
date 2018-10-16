import sensores.py

class jogo:
    def __init__(self):
        self.state = 0
        self.gamemode = 0
        self.jogador1 = ''
        self.jogador2 = ''
        self.tempo1 = 0.0
        self.tempo2 = 0.0


    def state0(self):
        # espera por input no browser

    def state1(self):
        self.gamemode = int(input("Quantos copos é que cada um de vocês vai emborcar?\n"))
        self.jogador1 = input("Nome do jogador 1: ")
        self.jogador2 = input("Nome do jogador 2: ")
        #eventualmente trocar isto por qlqr coisa equivalete no browser

    def state2(self):
        for i in self.gamemode:
            # funçao tipo start-stop para cada copo, recebe self.tempo1 e self.tempo2 como variáveis para o timer

    def state3(self):
        if self.tempo1 < self.tempo2:
            print(f"{self.jogador1} ganhou!\n")
        elif self.tempo1 > self.tempo2:
            print(f"{self.jogador2} ganhou!\n")
        else:
            print("É um empate!")

        #função que armazena os rezultados, juntando-os aos já existentes
