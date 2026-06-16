import random

class Jogador:
    def __init__(self, p_nome, p_nivel, p_vida):
        self._nome = p_nome
        self._nivel = p_nivel
        self._vida = p_vida

    def get_nome(self):
        return self._nome

    def atacar(self):
        raise NotImplementedError("Subclasses devem implementar o método atacar()")


class Guerreiro(Jogador):
    def __init__(self, p_nome, p_nivel, p_vida, p_forca):
        super().__init__(p_nome, p_nivel, p_vida)
        self.__forca = p_forca

    def atacar(self):
        dano = self.__forca * 1.5
        print(f"[Guerreiro] {self._nome} golpeia com força bruta! Dano causado: {dano:.1f}")
        return dano


class Mago(Jogador):
    def __init__(self, p_nome, p_nivel, p_vida, p_mana, p_inteligencia):
        super().__init__(p_nome, p_nivel, p_vida)
        self.__mana = p_mana
        self.__inteligencia = p_inteligencia

    def atacar(self):
        if self.__mana >= 10.0:
            self.__mana -= 10.0
            dano = self.__inteligencia * 2.0
            print(f"[Mago] {self._nome} conjura chamas mágicas! (Mana restante: {self.__mana:.1f}) Dano: {dano:.1f}")
            return dano
        else:
            dano_base = 5.0
            print(f"[Mago] {self._nome} está sem mana e ataca fracamente com o cajado! Dano base: {dano_base:.1f}")
            return dano_base


class Druida(Jogador):
    def __init__(self, p_nome, p_nivel, p_vida, p_mana, p_sabedoria):
        super().__init__(p_nome, p_nivel, p_vida)
        self.__mana = p_mana
        self.__sabedoria = p_sabedoria

    def atacar(self):
        if self.__mana >= 8.0:
            self.__mana -= 8.0
            dano = self.__sabedoria * 2.5
            print(f"[Druida] {self._nome} lanca uma pedra! (Mana restante: {self.__mana:.1f}) Dano: {dano:.1f}")
            return dano
        else:
            dano_base = 5.0
            print(f"[Druida] {self._nome} está sem mana e ataca fracamente com o cajado! Dano base: {dano_base:.1f}")
            return dano_base


class Arqueiro(Jogador):
    def __init__(self, p_nome, p_nivel, p_vida, p_destreza, p_agilidade, p_municao):
        super().__init__(p_nome, p_nivel, p_vida)
        self.__destreza = p_destreza
        self.__agilidade = p_agilidade
        self.__municao = p_municao

    def atacar(self):
        if self.__municao >= 1:
            self.__municao -= 1
            dano = self.__agilidade * 1.5
            print(f"[Arqueiro] {self._nome} atira uma flecha! (Flechas restantes: {self.__municao}) Dano: {dano:.1f}")
            return dano
        else:
            dano_base = 1.5 * self.__destreza
            print(f"[Arqueiro] {self._nome} está sem flechas e bate com o arco! Dano: {dano_base:.1f}")
            return dano_base


class Ladrao(Jogador):
    def __init__(self, p_nome, p_nivel, p_vida, p_agilidade, p_chance_critico):
        super().__init__(p_nome, p_nivel, p_vida)
        self.__agilidade = p_agilidade
        self.__chance_critico = p_chance_critico

    def atacar(self):
        dano_base = self.__agilidade
        sorte = random.random()

        if sorte <= self.__chance_critico:
            dano_critico = dano_base * 3.0
            print(f"[Ladrão] {self._nome} encontra uma brecha! ACERTO CRÍTICO! Dano: {dano_critico:.1f}")
            return dano_critico
        else:
            print(f"[Ladrão] {self._nome} realiza um ataque rápido! Dano: {dano_base:.1f}")
            return dano_base


class Monstro(Jogador):
    def __init__(self, p_nome, p_nivel, p_vida, p_forca, p_agilidade):
        super().__init__(p_nome, p_nivel, p_vida)
        self.__forca = p_forca
        self.__agilidade = p_agilidade

    def atacar(self):
        if self.__forca >= 8.0:
            self.__forca -= 8.0
            dano = self.__forca * 2.5
            print(f"[Monstro] {self._nome} ataca com suas presas! Dano: {dano:.1f}")
            return dano
        else:
            dano_base = 5.0
            print(f"[Monstro] {self._nome} ataca com as garras! Dano base: {dano_base:.1f}")
            return dano_base


class ConstrutorEnergia(Jogador):
    def __init__(self, p_nome, p_nivel, p_vida, p_energia, p_criatividade):
        super().__init__(p_nome, p_nivel, p_vida)
        self.__energia = p_energia
        self.__criatividade = p_criatividade

    def atacar(self):
        if self.__energia >= 8.0:
            self.__energia -= 8.0
            dano = self.__criatividade * 2.5
            print(f"[ConstrutorEnergia] {self._nome} lança uma constructo de energia! (Energia restante: {self.__energia:.1f}) Dano: {dano:.1f}")
            return dano
        else:
            dano_base = 5.0
            print(f"[ConstrutorEnergia] {self._nome} ataca com as mãos! Dano base: {dano_base:.1f}")
            return dano_base


def main():
    grupo = []

    grupo.append(Guerreiro("Guts", 15, 250.0, 30.0))
    grupo.append(Mago("Gandalf", 20, 120.0, 15.0, 40.0))
    grupo.append(Druida("JoãoFrango", 15, 180.0, 20.0, 25.0))
    grupo.append(Arqueiro("VolinHabba", 15, 120.0, 1.9, 20.0, 0))
    grupo.append(ConstrutorEnergia("Goku", 20, 120.0, 15.0, 40.0))
    grupo.append(Monstro("Dragão", 20, 120.0, 15.0, 40.0))
    grupo.append(Ladrao("Garrett", 12, 100.0, 22.0, 0.35))

    print("--- INÍCIO DO COMBATE ---")
    
    for rodada in range(1, 3):
        print(f"\n=== Turno {rodada} ===")
        
        for jogador in grupo:
            jogador.atacar()

if __name__ == "__main__":
    main()