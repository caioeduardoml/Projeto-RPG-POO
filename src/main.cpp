#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

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

Personagem* criarPersonagem() {
    int escolhaClasse, escolhaRaca;
    string nome;

    cout << "Digite o nome do seu herói: ";
    cin >> ws; // clear whitespace
    getline(cin, nome);

    cout << "\nEscolha sua Raça:\n";
    cout << "1. Humano\n2. Elfo\n3. Anão\n4. Orc\n5. Dragão\n";
    cout << "Opção: ";
    cin >> escolhaRaca;

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
    return p;
}

int main() {
    srand(time(0));

    cout << "=======================================\n";
    cout << "       BEM-VINDO À ARENA RPG!        \n";
    cout << "=======================================\n\n";

    Personagem* meuHeroi = nullptr;

    ifstream in("savegame.txt");
    if (in.is_open()) {
        in.close();
        int op;
        cout << "Um jogo salvo foi encontrado. Deseja carregar? (1 para Sim, 0 para Novo Jogo): ";
        cin >> op;
        if (op == 1) {
            meuHeroi = Persistencia::carregarJogo("savegame.txt");
        }
    }

    if (!meuHeroi) {
        meuHeroi = criarPersonagem();
    }

    // Usando sobrecarga do operador + para adicionar itens ao inventário
    *meuHeroi + new Arma("Espada Longa", "Uma espada de aço afiada", 3.0f, 15.0f);
    *meuHeroi + new Pocao("Poção de Cura", "Restaura 50 de vida", 0.5f, 50.0f);
    *meuHeroi + new PocaoEnergia("Poção de Energia", "Restaura 30 de energia", 0.5f, 30.0f);
    *meuHeroi + new BombaCaseira("Bomba Caseira", "Causa 40 de dano ao inimigo", 1.0f, 40.0f);
    *meuHeroi + new ItemEspecial("Cristal Místico", "Restaura 40 de energia (Especial)", 0.2f, 40.0f);

    // Usando sobrecarga do operador + para ganhar XP
    *meuHeroi + 15.0f;

    cout << "\nSeu Herói foi criado!\n";
    cout << *meuHeroi << "\n"; // Testa a sobrecarga do operador <<
    meuHeroi->getInventario().listarItens();
    cout << "\n";

    // Demonstrando operadores de comparação == e <
    Goblin g1;
    OrcMonstro o1;
    cout << "--- Comparando Inimigos com operadores == e < ---\n";
    cout << "g1 (" << g1.getNome() << " Nv." << g1.getNivel() << ") == o1 (" << o1.getNome() << " Nv." << o1.getNivel() << ")? " 
         << (g1 == o1 ? "Sim" : "Não") << "\n";
    cout << "g1 (" << g1.getNome() << " Nv." << g1.getNivel() << ") < o1 (" << o1.getNome() << " Nv." << o1.getNivel() << ")? " 
         << (g1 < o1 ? "Sim" : "Não") << "\n\n";

    // Criando monstros
    vector<Monstro*> monstros;
    monstros.push_back(new Goblin());
    monstros.push_back(new OrcMonstro());
    monstros.push_back(new GiganteMalvado());

    bool venceuTudo = true;

    for (size_t i = 0; i < monstros.size(); ++i) {
        Batalha batalha(meuHeroi, monstros[i]);
        if (!batalha.iniciar()) {
            venceuTudo = false;
            break;
        }

        int opcao;
        cout << "Deseja salvar o jogo? (1 para Sim, 0 para Não): ";
        cin >> opcao;
        if (opcao == 1) {
            Persistencia::salvarJogo(meuHeroi, "savegame.txt");
        }
    }

    if (venceuTudo) {
        cout << "=======================================\n";
        cout << " PARABÉNS! VOCÊ DERROTOU TODOS OS MONSTROS!\n";
        cout << " O REINO ESTÁ SALVO!\n";
        cout << "=======================================\n";
    }

    // Limpeza
    delete meuHeroi;
    for (Monstro* m : monstros) {
        delete m;
    }

    return 0;
}
