<div align="center">
  <h1>⚔️ Arena RPG (C++) ⚔️</h1>
  <p>Um jogo de RPG interativo em modo texto desenvolvido puramente em C++ aplicando conceitos avançados de Orientação a Objetos.</p>
</div>

---

## 📖 Sobre o Projeto
O **Arena RPG** é um jogo de turnos via terminal onde o jogador escolhe um herói com habilidades únicas para enfrentar uma horda (Torre) de monstros com dificuldades crescentes. O jogo se destaca pelo uso de um sistema inteligente de energia, gerenciamento de atributos dinâmicos e mecânicas de mitigação de dano através de armadura.

## ✨ Funcionalidades Principais

* **Diversidade de Heróis**: Escolha entre 6 classes distintas de heróis.
* **Sistema de Batalha por Turnos**: Decida estrategicamente quando usar um ataque básico (gratuito) ou acumular sua reserva para desferir um Ataque Especial devastador!
* **Mecânica de Energia**: Todo turno você e os monstros recuperam energia. Gerencie-a com cuidado.
* **Inteligência Artificial Simples**: Os inimigos tomam decisões com base na energia acumulada e possuem chance de realizar ataques esmagadores.
* **Mitigação por Defesa**: O dano não é direto! O valor do dano sofrido é matematicamente reduzido pela sua armadura (Defesa), tornando combates contra chefes um verdadeiro desafio tático.
* **Sistema de Progressão (Level Up)**: A cada monstro derrotado, seu herói sobe de nível: vida máxima aumentada, poder destrutivo escalonado e recuperação total de saúde como recompensa.

## 🛡️ Classes Disponíveis

Cada herói herda da classe base `Jogador`, mas implementa status, custos e ataques únicos:

1. **Guerreiro**: Alto poder destrutivo e vida abundante. (Ataque Especial: *Fúria Incontrolável*)
2. **Mago**: Mestre do dano em área com a maior reserva de energia mágica. (Ataque Especial: *Bola de Fogo Mágica*)
3. **Druida**: Equilíbrio perfeito utilizando a sabedoria da terra. (Ataque Especial: *Ira da Natureza*)
4. **Arqueiro**: Dano rápido, crítico e consistente. (Ataque Especial: *Flecha Perfurante*)
5. **Construtor de Energia**: O gênio criativo capaz de criar aliados colossais. (Ataque Especial: *Constructo Colossal*)
6. **Ladrão**: Especialista em acertos críticos e assassinatos pelas sombras. (Ataque Especial: *Assassinato Furtivo*)

## 🐉 A Horda Inimiga

Para salvar o reino, você precisa derrotar:
- 🟢 **Goblin Saqueador (Nv. 5)** - Ágil, mas com defesa nula.
- 🟡 **Orc Guerreiro (Nv. 15)** - Um brutamontes com vida elevada.
- 🔴 **Dragão Ancião (Nv. 30)** - O desafio final com defesas quase impenetráveis.

## 💻 Estrutura do Código

O projeto obedece aos pilares da Programação Orientada a Objetos (Herança, Polimorfismo e Encapsulamento):

```text
Projeto RPG/
├── Makefile                # Script de compilação automatizada
├── include/                # Arquivos de cabeçalho (.hpp)
│   ├── Jogador.hpp         # Classe Base (Status e Métodos Virtuais Puros)
│   ├── Guerreiro.hpp       # Subclasses de Heróis...
│   └── Monstro.hpp         # Classe e Subclasses de Inimigos (Goblin, Orc, Dragão)
└── src/                    # Arquivos de implementação (.cpp)
    ├── Herois/             # Lógica detalhada dos heróis
    ├── main.cpp            # Loop do jogo (Arena, Menus e Inputs)
    └── Monstro.cpp         # IA dos Monstros
```

## 🚀 Como Jogar

Este projeto foi construído para ser facilmente compilado em ambientes Linux/Unix que possuam o `g++` e o `make` instalados.

1. **Clone o repositório:**
   ```bash
   git clone https://github.com/caioeduardoml/Projeto-RPG-POO.git
   cd Projeto-RPG-POO
   ```

2. **Compile o jogo:**
   ```bash
   make
   ```
   *(Para forçar uma recompilação completa do zero, você pode rodar `make clean && make`)*

3. **Execute:**
   ```bash
   ./rpg_game
   ```

Divirta-se tentando chegar vivo até o Dragão Ancião! ⚔️🛡️
