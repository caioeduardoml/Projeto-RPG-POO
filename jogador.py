class Jogador:
    def __init__(self, nome, nivel, hp_maximo):
        self.nome = nome
        self.nivel = nivel
        self.hp_maximo = hp_maximo
        self.hp = hp_maximo
    
    def exibirStatus(self):
        print(f"Nome: {self.nome}")
        print(f"Nível: {self.nivel}")
        print(f"HP: {self.hp}/{self.hp_maximo}")
        print("-" * 20)
    
    def estaVivo(self):
        return self.hp > 0
    
    def receberDano(self, dano):
        self.hp -= dano
        if self.hp < 0:
            self.hp = 0
        print(f"{self.nome} recebeu {dano} de dano!")
        print(f"HP atual: {self.hp}/{self.hp_maximo}")
        if not self.estaVivo():
            print(f"{self.nome} morreu!")
    
    def curar(self, quantidade):
        self.hp += quantidade
        if self.hp > self.hp_maximo:
            self.hp = self.hp_maximo
        print(f"{self.nome} recuperou {quantidade} de HP!")
        print(f"HP atual: {self.hp}/{self.hp_maximo}")


# Criando jogador
jogador = Jogador("Caio Bonitao", 999, 9999999)
jogador.exibirStatus()

# Testando métodos
print("Vivo?", jogador.estaVivo(),"\n")

jogador.receberDano(999)
jogador.exibirStatus()

jogador.curar(99)
jogador.exibirStatus()

jogador.receberDano(999999)
jogador.exibirStatus()

print("Vivo?", jogador.estaVivo())