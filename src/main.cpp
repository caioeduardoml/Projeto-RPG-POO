#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "../include/Jogador.hpp"
#include "../include/Guerreiro.hpp"
#include "../include/Mago.hpp"
#include "../include/Druida.hpp"
#include "../include/Arqueiro.hpp"
#include "../include/Ladrao.hpp"
#include "../include/Monstro.hpp"
#include "../include/ConstrutorEnergia.hpp"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "=======================================\n";
    cout << "       BEM-VINDO À ARENA RPG!        \n";
    cout << "=======================================\n\n";

    vector<Jogador*> heroisDisponiveis;
    heroisDisponiveis.push_back(new Guerreiro("Guts - Guerreiro", 15, 250.0f, 30.0f));
    heroisDisponiveis.push_back(new Mago("Gandalf - Mago", 20, 120.0f, 40.0f)); 
    heroisDisponiveis.push_back(new Druida("JoãoFrango - Druida", 15, 180.0f, 25.0f)); 
    heroisDisponiveis.push_back(new Arqueiro("VolinHabba - Arqueiro", 15, 120.0f, 15.0f, 20.0f)); 
    heroisDisponiveis.push_back(new ConstrutorEnergia("Goku - Construtor de Energia", 69, 999.0f, 96.0f));
    heroisDisponiveis.push_back(new Ladrao("Garrett - Ladrao", 12, 100.0f, 22.0f, 0.35f)); 

    cout << "Escolha o seu Herói:\n";
    for (size_t i = 0; i < heroisDisponiveis.size(); ++i) {
        cout << i + 1 << ". ";
        heroisDisponiveis[i]->exibirStatus();
    }

    int escolhaHeroi = -1;
    while (escolhaHeroi < 1 || escolhaHeroi > static_cast<int>(heroisDisponiveis.size())) {
        cout << "\nDigite o número do herói que deseja jogar: ";
        cin >> escolhaHeroi;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            escolhaHeroi = -1;
        }
    }

    Jogador* meuHeroi = heroisDisponiveis[escolhaHeroi - 1];
    cout << "\nVocê escolheu jogar com " << meuHeroi->getNome() << "!\n\n";

    // Cria a sequência de monstros (Torre)
    vector<Monstro*> monstros;
    monstros.push_back(new Goblin());
    monstros.push_back(new Orc());
    monstros.push_back(new Dragao());

    bool venceuTudo = true;

    for (size_t i = 0; i < monstros.size(); ++i) {
        Monstro* inimigo = monstros[i];
        cout << "=======================================\n";
        cout << " BATALHA " << i + 1 << ": " << inimigo->getNome() << " apareceu!\n";
        cout << "=======================================\n";

        int turno = 1;

        while (meuHeroi->isVivo() && inimigo->isVivo()) {
            cout << "\n--- Turno " << turno << " ---\n";
            
            // Turno do Herói
            meuHeroi->recuperarEnergia(10.0f); 
            cout << "[Seu Status] ";
            meuHeroi->exibirStatus();
            cout << "[Inimigo]    ";
            inimigo->exibirStatus();
            cout << "\n";

            meuHeroi->exibirOpcoesAtaque();
            int escolhaAtaque;
            cout << "Escolha seu ataque: ";
            cin >> escolhaAtaque;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                escolhaAtaque = 1; // Default
            }

            cout << "\n";
            float danoCausado = meuHeroi->realizarAtaque(escolhaAtaque);
            inimigo->receberDano(danoCausado);

            if (!inimigo->isVivo()) {
                cout << "\n>>> VOCÊ DERROTOU O " << inimigo->getNome() << "! <<<\n\n";
                meuHeroi->subirNivel();
                break;
            }

            // Turno do Inimigo
            inimigo->recuperarEnergia(5.0f);
            float danoSofrido = inimigo->realizarAtaque(0); // IA não precisa de escolha
            meuHeroi->receberDano(danoSofrido);

            if (!meuHeroi->isVivo()) {
                cout << "\n>>> " << meuHeroi->getNome() << " CAIU EM BATALHA... GAME OVER <<<\n";
                venceuTudo = false;
                break;
            }

            turno++;
        }

        if (!meuHeroi->isVivo()) {
            break; // Sai do loop de monstros se morreu
        }
    }

    if (venceuTudo) {
        cout << "=======================================\n";
        cout << " PARABÉNS! VOCÊ DERROTOU TODOS OS MONSTROS!\n";
        cout << " O REINO ESTÁ SALVO!\n";
        cout << "=======================================\n";
    }

    // Limpeza de memória
    for (Jogador* h : heroisDisponiveis) {
        delete h;
    }
    for (Monstro* m : monstros) {
        delete m;
    }

    return 0;
}
