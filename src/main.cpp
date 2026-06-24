#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <limits>

#include "../include/Personagem.hpp"
#include "../include/Guerreiro.hpp"
#include "../include/Mago.hpp"
#include "../include/Druida.hpp"
#include "../include/Arqueiro.hpp"
#include "../include/Ladrao.hpp"
#include "../include/ConstrutorEnergia.hpp"
#include "../include/Clerigo.hpp"
#include "../include/Raca.hpp"
#include "../include/Item.hpp"
#include "../include/Batalha.hpp"
#include "../include/Persistencia.hpp"

using namespace std;

// Funções auxiliares
void limparTela() {
    std::system("clear");
}

void limparBuffer() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void pausar() {
    cout << "\nPressione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

Personagem* criarPersonagem() {
    limparTela();
    int escolhaClasse, escolhaRaca;
    string nome;

    cout << "=======================================\n";
    cout << "           CRIAÇÃO DE HERÓI            \n";
    cout << "=======================================\n";
    cout << "Digite o nome do seu herói: ";
    cin >> ws; // clear whitespace
    getline(cin, nome);

    cout << "\nEscolha sua Raça:\n";
    cout << "1. Humano\n2. Elfo\n3. Anão\n4. Orc\n5. Dragão\n";
    cout << "Opção: ";
    cin >> escolhaRaca;
    limparBuffer();

    Raca* raca = nullptr;
    switch (escolhaRaca) {
        case 1: raca = new Humano(); break;
        case 2: raca = new Elfo(); break;
        case 3: raca = new Anao(); break;
        case 4: raca = new Orc(); break;
        case 5: raca = new Dragao(); break;
        default: raca = new Humano(); break;
    }

    cout << "\nEscolha sua Classe:\n";
    cout << "1. Guerreiro\n2. Mago\n3. Arqueiro\n4. Druida\n5. Ladrão\n6. Construtor de Energia\n7. Clérigo\n";
    cout << "Opção: ";
    cin >> escolhaClasse;
    limparBuffer();

    Personagem* p = nullptr;
    switch (escolhaClasse) {
        case 1: p = new Guerreiro(nome, raca, 1); break;
        case 2: p = new Mago(nome, raca, 1); break;
        case 3: p = new Arqueiro(nome, raca, 1); break;
        case 4: p = new Druida(nome, raca, 1); break;
        case 5: p = new Ladrao(nome, raca, 1); break;
        case 6: p = new ConstrutorEnergia(nome, raca, 1); break;
        case 7: p = new Clerigo(nome, raca, 1); break;
        default: p = new Guerreiro(nome, raca, 1); break;
    }
    
    // Itens iniciais testando a sobrecarga de operador
    *p + new Arma("Espada Inicial", "Arma básica", 2.0f, 10.0f);
    *p + new Pocao("Poção de Cura", "Restaura 50 de vida", 0.5f, 50.0f);
    *p + new PocaoEnergia("Poção de Energia", "Restaura 30 de energia", 0.5f, 30.0f);
    
    return p;
}

void menuInventario(Personagem* heroi) {
    bool noInventario = true;
    while (noInventario) {
        limparTela();
        cout << "=======================================\n";
        cout << "           GERENCIAR INVENTÁRIO        \n";
        cout << "=======================================\n";
        cout << "Capacidade: " << heroi->getInventario().getPesoAtual() << " / " << heroi->getInventario().getCapacidade() << " kg\n";
        cout << "---------------------------------------\n";
        heroi->getInventario().listarItens();
        cout << "---------------------------------------\n";
        
        cout << "Escolha o índice do item para interagir (ou 0 para voltar, -1 para ver equipamentos): ";
        int escolha;
        cin >> escolha;
        limparBuffer();
        
        if (escolha == 0) {
            noInventario = false;
        } else if (escolha == -1) {
            limparTela();
            heroi->exibirEquipamentos();
            string slotEscolhido;
            cout << "\nDigite o nome do slot para desequipar (Ex: Arma, Capacete) ou 0 para cancelar: ";
            cin >> slotEscolhido;
            limparBuffer();
            if (slotEscolhido != "0") {
                if (slotEscolhido == "Arma" || slotEscolhido == "arma") {
                    heroi->desequiparArma();
                } else {
                    heroi->desequiparArmadura(slotEscolhido);
                }
                pausar();
            }
        } else if (escolha > 0 && escolha <= heroi->getInventario().getQuantidadeItens()) {
            Item* item = heroi->getInventario().getItem(escolha - 1);
            if (item) {
                if (item->getTipo() == TipoItem::Arma) {
                    heroi->equiparArma(dynamic_cast<Arma*>(item));
                } else if (item->getTipo() == TipoItem::Armadura) {
                    heroi->equiparArmadura(dynamic_cast<Armadura*>(item));
                } else if (item->getTipo() == TipoItem::Bomba) {
                    cout << "Você não pode usar uma bomba fora de batalha!\n";
                } else {
                    // Consumível (Poções, Especial)
                    item->usar(heroi, nullptr);
                    heroi->getInventario().removerItem(item);
                    delete item; // Consumido
                }
                pausar();
            }
        } else {
            cout << "Opção inválida!\n";
            pausar();
        }
    }
}

void menuBatalha(Personagem* heroi, int& progressoBatalha) {
    limparTela();
    cout << "=======================================\n";
    cout << "           ARENA DE BATALHA            \n";
    cout << "=======================================\n";
    
    if (progressoBatalha >= 5) {
        cout << "Parabéns! Você já derrotou todos os monstros na Arena e salvou o reino!\n";
        pausar();
        return;
    }

    Monstro* monstro = nullptr;
    switch(progressoBatalha) {
        case 0: monstro = new Goblin(); break;
        case 1: monstro = new OrcMonstro(); break;
        case 2: monstro = new LoboMau(); break;
        case 3: monstro = new GiganteMalvado(); break;
        case 4: monstro = new PeppaPig(); break;
    }

    cout << "Você encontrou o " << monstro->getNome() << " Nv." << monstro->getNivel() << " (Desafio " << progressoBatalha + 1 << "/5)!\n";
    
    // Demonstração dos operadores == e < (como exigido nas regras de POO)
    cout << "\n--- Comparação Rápida (Operadores) ---\n";
    cout << "Heroi (" << heroi->getNome() << ") == Monstro (" << monstro->getNome() << ") ? " << (*heroi == *monstro ? "Sim" : "Não") << "\n";
    cout << "Nível do Herói < Nível do Monstro ? " << (*heroi < *monstro ? "Sim" : "Não") << "\n";
    cout << "--------------------------------------\n";
    pausar();
    limparTela();

    Batalha batalha(heroi, monstro);
    bool venceu = batalha.iniciar();

    if (venceu) {
        cout << "\nVitória na Arena! O drop aleatório já foi processado.\n";
        progressoBatalha++; // Avança a fase
    } else {
        cout << "\nVocê foi derrotado!\n";
    }

    delete monstro;
    pausar();
}

int main() {
    srand(time(0));

    Personagem* meuHeroi = nullptr;
    int progressoBatalha = 0;

    limparTela();
    cout << "=======================================\n";
    cout << "       BEM-VINDO AO RPG MANAGER        \n";
    cout << "=======================================\n\n";

    int op = 0;
    while (!meuHeroi) {
        cout << "[1] Novo Jogador\n";
        cout << "[2] Carregar Jogador\n";
        cout << "Escolha uma opção: ";
        cin >> op;
        limparBuffer();

        if (op == 1) {
            meuHeroi = criarPersonagem();
        } else if (op == 2) {
            ifstream in("savegame.txt");
            if (in.is_open()) {
                in.close();
                meuHeroi = Persistencia::carregarJogo("savegame.txt", progressoBatalha);
                if (!meuHeroi) {
                    cout << "Erro ao carregar o jogo salvo.\n";
                    pausar();
                    limparTela();
                }
            } else {
                cout << "Nenhum jogo salvo encontrado! Crie um novo personagem.\n";
                pausar();
                limparTela();
            }
        } else {
            cout << "Opção inválida!\n";
            pausar();
            limparTela();
        }
    }

    bool executando = true;

    while (executando && meuHeroi->isVivo()) {
        limparTela();
        cout << "=======================================\n";
        cout << "             MENU PRINCIPAL            \n";
        cout << "=======================================\n";
        cout << " Herói: " << *meuHeroi << "\n"; // Uso do operator<< exigido
        cout << " Arena: Desafio " << (progressoBatalha >= 5 ? 5 : progressoBatalha + 1) << "/5\n";
        cout << "=======================================\n";
        cout << "[1] Ficha do Herói (Status)\n";
        cout << "[2] Gerenciar Inventário e Equipamentos\n";
        cout << "[3] Arena de Batalha\n";
        cout << "[4] Salvar Jogo\n";
        cout << "[0] Sair\n";
        cout << "=======================================\n";
        cout << "Escolha uma opção: ";
        
        int opcao;
        cin >> opcao;
        limparBuffer();

        switch (opcao) {
            case 1:
                limparTela();
                cout << "=======================================\n";
                cout << "             FICHA DO HERÓI            \n";
                cout << "=======================================\n";
                meuHeroi->exibirStatus(); // Polimorfismo
                pausar();
                break;
            case 2:
                menuInventario(meuHeroi);
                break;
            case 3:
                menuBatalha(meuHeroi, progressoBatalha);
                break;
            case 4:
                Persistencia::salvarJogo(meuHeroi, "savegame.txt", progressoBatalha);
                cout << "Jogo salvo com sucesso!\n";
                pausar();
                break;
            case 0:
                executando = false;
                break;
            default:
                cout << "Opção inválida!\n";
                pausar();
                break;
        }
    }

    limparTela();
    if (!meuHeroi->isVivo()) {
        cout << "=======================================\n";
        cout << "              GAME OVER                \n";
        cout << "=======================================\n";
        cout << "Seu herói sucumbiu em batalha.\n";
    } else {
        cout << "=======================================\n";
        cout << "        OBRIGADO POR JOGAR!            \n";
        cout << "=======================================\n";
    }

    // Liberação de memória dos ponteiros brutos (Exigido no ponto 1. [0] Sair)
    delete meuHeroi;

    return 0;
}
