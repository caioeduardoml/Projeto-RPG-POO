<div align="center">
  <h1>⚔️ RPG Manager (C++) ⚔️</h1>
  <p>Um sistema completo de gerenciamento de jogo de RPG por turnos com interface gráfica desenvolvida em Qt5 e backend puramente estruturado em C++17.</p>
  <p>Desenvolvido para atender aos critérios da disciplina de <b>Programação Orientada a Objetos (POO)</b> da <b>UTFPR (Universidade Tecnológica Federal do Paraná)</b>.</p>
</div>

---

## 📖 Sobre o Projeto

O **RPG Manager** é um jogo de estratégia em turnos onde o jogador cria um personagem customizado (escolhendo nome, raça e classe) e enfrenta uma sequência linear de desafios na arena. O projeto une a robustez de um motor de combate baseado nos conceitos mais fundamentais de Orientação a Objetos (Herança, Polimorfismo, Encapsulamento, Sobrecarga e Padrões de Design) a uma interface rica e reativa construída utilizando a biblioteca **Qt5**.

---

## ✨ Funcionalidades Principais

* **Interface Gráfica Interativa (Qt5)**:
  * **Criação de Personagem**: Menu inicial `Welcome Dialog` com caixas de seleção estilizadas (dropdowns com visual sombrio/preto) para definição de raça, classe e habilidades iniciais.
  * **Ficha em Tempo Real**: Indicadores de nível, barra de vida (HP) e barra de energia (EP/Mana/Fé) dinamicamente atualizados de acordo com as estatísticas do jogador.
  * **Painel de Inventário & Equipamentos**: Listagem com descrição de bônus (Ex: `+20 dano`, `+15 defesa`) e gerenciamento inteligente de itens equipados (arma e armaduras em seus respectivos slots), incluindo botão interativo de desequipar no painel dedicado.
  * **Console de Logs de Batalha**: Redirecionamento em tempo real do fluxo do terminal `std::cout` diretamente para um painel gráfico (`QTextBrowser`).
* **Mecânicas Avançadas de Combate**:
  * **Diferenciação de Dano e Mitigação**: Cada classe possui uma mecânica exclusiva de tratamento de danos recebidos (ex: mitigação baseada em fúria acumulada, consumo de energia/mana, ou barreira de energia fixa).
  * **Ataque Básico vs. Habilidades**: O ataque básico regenera energia (+15 EP), enquanto habilidades potentes consomem recursos específicos.
  * **Habilidades de Suporte**: Habilidades voltadas à regeneração de atributos ou cura agem corretamente sobre o próprio herói, garantindo estratégias dinâmicas.
* **Arena de Dificuldade Linear**:
  * O combate randômico foi substituído por uma progressão desafiadora contra monstros que escalam de nível e poder:
    1. **Goblin** (Nível 1)
    2. **Orc Furioso** (Nível 3)
    3. **Lobo Mau** (Nível 5)
    4. **Gigante Malvadão** (Nível 10)
    5. **Peppa Pig** (Nível 20 - Desafio Final)
* **Persistência de Estado**:
  * Permite salvar e carregar o estado do herói e o progresso exato da batalha na arena através do arquivo [savegame.txt](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/savegame.txt).
* **Suíte de Testes Automatizados**:
  * Testes unitários cobrindo mitigações de dano de classe, limites do inventário, inicialização de personagens e operações matemáticas.

---

## 🛡️ Classes de Heróis e Raças

### Raças Disponíveis
Cada raça altera os atributos iniciais do herói (Vida, Força ou Inteligência) ao ser selecionada:
* **Humano**: Bônus balanceado de atributos.
* **Elfo**: Foco em inteligência e agilidade.
* **Anão**: Alta resistência e bônus de vida.
* **Orc**: Foco em força física brutal.
* **Dragão**: Defesas elevadas e vida formidável.

### Classes e suas Mecânicas Exclusivas
Cada herói herda da classe base [Personagem](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/include/Personagem.hpp) e implementa sua mecânica de combate singular:
1. **Guerreiro**: Foco em força física e dano direto. Mitiga parte do dano recebido acumulando *Fúria*.
2. **Mago**: Mestre de magias. Possui *Escudo de Mana*, consumindo sua reserva mágica para absorver 50% de todo dano líquido recebido.
3. **Druida**: Equilíbrio com a natureza. Utiliza *Comunhão* para absorver 20% do dano líquido e convertê-lo em energia adicional.
4. **Arqueiro**: Combate à distância com alta precisão e chances ampliadas de acertos críticos.
5. **Ladrão**: Mestre da evasão. Utiliza *Furtividade* para atenuar em 30% o dano recebido ao custo de sua reserva furtiva.
6. **Clérigo**: Combatente santo focado em suporte. Utiliza *Fé* para absorver 30% do dano sofrido e conjura habilidades de cura divina e bênçãos sagradas.
7. **Construtor de Energia**: Engenheiro arcano que ergue uma *Barreira de Energia* duradoura, mitigando um valor fixo de dano por golpe.

---

## 🧩 Aplicação dos Conceitos de POO (UTFPR)

O projeto foi meticulosamente desenhado para servir de modelo acadêmico dos seguintes pilares:

* **Encapsulamento**: Uso rigoroso de modificadores de visibilidade (`private`, `protected`), getters/setters bem delimitados e interfaces limpas.
* **Herança & Polimorfismo**:
  * Classe abstrata [Entidade](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/include/Entidade.hpp) serve como base polimórfica para [Personagem](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/include/Personagem.hpp) e [Monstro](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/include/Monstro.hpp).
  * Divisão polimórfica de itens ([Item](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/include/Item.hpp) -> `Arma`, `Armadura`, `Pocao`, `ItemEspecial`) e habilidades ([Habilidade](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/include/Habilidade.hpp)).
* **Composição & Agregação**:
  * Relação de composição estrita entre [Personagem](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/include/Personagem.hpp) e seu [Inventario](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/include/Inventario.hpp).
  * Agregação polimórfica de [Habilidade](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/include/Habilidade.hpp) na ficha do personagem.
* **Sobrecarga de Operadores**:
  * `==` e `<` na classe [Entidade](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/include/Entidade.hpp) para comparação de níveis e igualdade.
  * `+` na classe [Personagem](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/include/Personagem.hpp) sobrecarregado para ganho direto de XP (`heroi + 50.0f`) e inserção direta de itens no inventário (`heroi + novoItem`).
* **Gerenciamento Seguro de Memória**:
  * Controle de desalocação explícita nos destrutores das classes proprietárias utilizando o operador `delete` para evitar memory leaks, atendendo às restrições de uso de Smart Pointers no núcleo de dados.
* **Padrões de Projeto (Design Patterns)**:
  * **Strategy**: A IA dos monstros adota diferentes estratégias de ataque baseadas na sua energia.
  * **Observer**: A janela principal [MainWindow](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/include/MainWindow.hpp) implementa a interface [CombateObserver](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/include/Observer.hpp), reagindo de forma reativa a cada log ou alteração de turno gerado na classe [Batalha](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/include/Batalha.hpp).
  * **Factory**: Instanciação centralizada de entidades por meio de [PersonagemFactory](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/include/PersonagemFactory.hpp) e [MonstroFactory](file:///home/sexta-feira/Documents/Facul/POO/Projeto%20RPG/include/MonstroFactory.hpp).
  * **Template Method**: Hook virtual puro `subir_nivel` na classe abstrata de personagens.

---

## 💻 Estrutura do Código

```text
Projeto RPG/
├── Makefile                        # Automação do processo de compilação
├── savegame.txt                    # Arquivo de persistência de progresso
├── include/                        # Arquivos de cabeçalho (.hpp)
│   ├── Entidade.hpp                # Classe abstrata base das entidades
│   ├── Personagem.hpp              # Classe base dos heróis (composição de inventário)
│   ├── Raca.hpp                    # Classe e subclasses de raças
│   ├── Monstro.hpp                 # Classe e subclasses de monstros
│   ├── Item.hpp                    # Itens e subclasses (Arma, Armadura, Poção, ItemEspecial)
│   ├── Inventario.hpp              # Sistema de peso e limite de carga
│   ├── Habilidade.hpp              # Habilidades ativas de combate/suporte
│   ├── Batalha.hpp                 # Lógica de turnos e combate
│   ├── MainWindow.hpp              # Interface de visualização Qt5
│   └── ...                         # Factories, Observers e Exceções
├── core/                           # Arquivos de implementação (.cpp)
│   ├── Herois/                     # Lógica interna de cada classe de Herói
│   │   ├── Guerreiro.cpp, Mago.cpp, Druida.cpp, Arqueiro.cpp,
│   │   └── Ladrao.cpp, Clerigo.cpp, ConstrutorEnergia.cpp
│   ├── Monstros/                   # Lógica dos inimigos
│   │   └── Monstro.cpp
│   ├── Entidade.cpp, Personagem.cpp, Raca.cpp, Item.cpp,
│   └── Inventario.cpp, Habilidade.cpp, Batalha.cpp, Persistencia.cpp
├── src/                            # Interface gráfica e execução
│   ├── main.cpp                    # Ponto de entrada (inicialização do Qt e UI)
│   └── MainWindow.cpp              # Fluxo e desenho de telas da GUI Qt5
└── tests/                          # Testes unitários
    ├── test_main.cpp               # Inicializador do Google Test
    └── test_rpg.cpp                # Casos de teste estruturais
```

---

## 🚀 Como Compilar e Jogar

O projeto utiliza o `g++` com o padrão **C++17**, a biblioteca **Qt5Widgets** e o framework **Google Test**.

### Requisitos Prévios (Linux Debian/Ubuntu)
```bash
sudo apt update
sudo apt install build-essential qtbase5-dev libgtest-dev
```

### 1. Compilação do Jogo
Para compilar a interface gráfica completa do jogo:
```bash
make
```
Isso gerará o executável `rpg_game` na raiz do projeto.

### 2. Executando o Jogo
```bash
./rpg_game
```

### 3. Executando a Suíte de Testes Unitários
Para compilar e rodar os testes automatizados da lógica de combate:
```bash
make test
```
Isso compilará o executável `test_rpg` e exibirá os resultados do Google Test diretamente no terminal.

### 4. Limpando Arquivos Gerados
Para limpar os arquivos temporários e binários compilados:
```bash
make clean
```
