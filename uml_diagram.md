# Diagrama UML - RPG Manager

Abaixo está o diagrama de classes atualizado, refletindo as implementações de padrões de projeto (Observer, Strategy, Factory, Singleton) e a herança entre as entidades principais do sistema.

```mermaid
classDiagram
    class Subject {
        <<abstract>>
        -observers : vector~CombateObserver*~
        +registrarObserver(obs: CombateObserver*)
        +removerObserver(obs: CombateObserver*)
        +notificar(log: string)
    }

    class CombateObserver {
        <<interface>>
        +aoAcontecerEvento(log: string)*
    }

    class GerenciadorJogo {
        <<Singleton>>
        -instancia : unique_ptr~GerenciadorJogo~
        -heroi : shared_ptr~Personagem~
        -monstro_atual : shared_ptr~Monstro~
        -progresso_batalha : int
        +get_instancia() GerenciadorJogo$
        +iniciar_desafio_arena()
        +get_heroi() shared_ptr~Personagem~
        +get_monstro_atual() shared_ptr~Monstro~
    }

    Subject <|-- GerenciadorJogo
    CombateObserver "many" <--* "1" Subject : notifica

    class Entidade {
        <<abstract>>
        #nome : string
        #nivel : int
        #pontos_vida_atual : int
        #pontos_vida_max : int
        #energia_atual : int
        #energia_max : int
        +receber_dano(dano: int)*
        +exibir_status()
        +gastar_energia(qtd: int)
    }

    class Personagem {
        <<abstract>>
        -raca : string
        -classe_rpg : string
        -experiencia : int
        -inventario : Inventario
        -habilidades : vector~unique_ptr~Habilidade~~
        +subir_nivel()*
        +ganhar_experiencia(exp: int)
        +atacar(alvo: Entidade&, index_habilidade: int)
        +operator+(exp: int) Personagem&
        +operator+(item: shared_ptr~Item~) Personagem&
    }

    class Monstro {
        -tipo : string
        -comportamentoAtaque : unique_ptr~ComportamentoAtaque~
        +realizar_ataque(alvo: Personagem&)
    }

    Entidade <|-- Personagem
    Entidade <|-- Monstro

    class Guerreiro
    class Mago
    class Arqueiro
    class Clerigo
    Personagem <|-- Guerreiro
    Personagem <|-- Mago
    Personagem <|-- Arqueiro
    Personagem <|-- Clerigo

    class Item {
        <<abstract>>
        #nome : string
        #descricao : string
        #peso : double
        #valor_moedas : int
        +usar(usuario: Personagem&)*
    }

    class Arma
    class Armadura
    class Pocao
    Item <|-- Arma
    Item <|-- Armadura
    Item <|-- Pocao

    class Inventario {
        -capacidade_maxima_peso : double
        -itens : vector~shared_ptr~Item~~
        +adicionarItem(item: shared_ptr~Item~)
        +removerItem(nome: string)
    }

    Personagem *-- Inventario : possui
    Inventario o-- Item : agrega

    class ComportamentoAtaque {
        <<interface>>
        +calcular_dano(forca: int, inteligencia: int) int*
        +get_nome_ataque() string*
    }

    class AtaqueFisicoFeroz
    class AtaqueMagicoArcano
    ComportamentoAtaque <|-- AtaqueFisicoFeroz
    ComportamentoAtaque <|-- AtaqueMagicoArcano

    Monstro *-- ComportamentoAtaque : usa (Strategy)

    class MonstroFactory {
        <<Factory>>
        +criar_monstro(tipo: string) shared_ptr~Monstro~$
    }
    
    class PersonagemFactory {
        <<Factory>>
        +criar_personagem(classe: string, raca: string) shared_ptr~Personagem~$
    }

    MonstroFactory ..> Monstro : cria
    PersonagemFactory ..> Personagem : cria
```

### Explicação do Diagrama
- **Padrão Strategy**: O `Monstro` utiliza a interface `ComportamentoAtaque` para delegar o cálculo de dano, permitindo variar os ataques em tempo de execução.
- **Padrão Observer**: `GerenciadorJogo` herda de `Subject` e emite notificações de eventos para qualquer `CombateObserver` registrado (neste caso, a interface gráfica).
- **Padrão Factory**: `MonstroFactory` e `PersonagemFactory` instanciam dinamicamente subclasses abstratas, encapsulando a complexidade de criação.
- **Padrão Singleton**: O `GerenciadorJogo` é unicamente instanciado no sistema via `get_instancia()`.
- **Composição de Inventário**: A classe `Personagem` contém instâncias de `Inventario` (Composição), o qual por sua vez agrega coleções de classes filhas de `Item` (Polimorfismo).
