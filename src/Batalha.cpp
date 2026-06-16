#include "../include/Batalha.hpp"
#include <iostream>

Batalha::Batalha(Personagem* p_heroi, Monstro* p_monstro)
    : heroi(p_heroi), monstro(p_monstro) {}

bool Batalha::iniciar() {
    cout << "=======================================\n";
    cout << " BATALHA: " << heroi->getNome() << " VS " << monstro->getNome() << "!\n";
    cout << "=======================================\n";

    int turno = 1;

    while (heroi->isVivo() && monstro->isVivo()) {
        cout << "\n--- Turno " << turno << " ---\n";
        
        // Turno do Herói
        cout << "[Seu Status] ";
        heroi->exibirStatus();
        cout << "[Inimigo]    ";
        monstro->exibirStatus();
        cout << "\n";

        heroi->listarHabilidades();
        int escolhaAtaque;
        cout << "Escolha sua ação (-1 para Inventário, 0 para ataque básico, 1+ para habilidade): ";
        cin >> escolhaAtaque;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            escolhaAtaque = 0;
        }

        cout << "\n";
        bool perdeuTurno = false;
        
        if (escolhaAtaque == -1) {
            heroi->getInventario().listarItens();
            int escolhaItem;
            cout << "Escolha um item (0 para cancelar): ";
            cin >> escolhaItem;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                escolhaItem = 0;
            }
            
            if (escolhaItem > 0) {
                Item* itemEscolhido = heroi->getInventario().getItem(escolhaItem - 1);
                if (itemEscolhido) {
                    itemEscolhido->usar(heroi, monstro);
                    // Consumíveis (Poções, Bombas) são removidos após o uso
                    if (itemEscolhido->getTipo() == TipoItem::Pocao || 
                        itemEscolhido->getTipo() == TipoItem::PocaoEnergia || 
                        itemEscolhido->getTipo() == TipoItem::Bomba) {
                        heroi->getInventario().removerItem(itemEscolhido);
                        delete itemEscolhido; // Evitar memory leak pois não está mais no inventário
                    }
                    perdeuTurno = true;
                } else {
                    cout << "Item inválido!\n";
                }
            } else {
                cout << "Ação cancelada. Turno reiniciado.\n";
                continue; // Volta ao início do while, não avança o turno
            }
        } else if (escolhaAtaque == 0) {
            // Ataque básico
            cout << heroi->getNome() << " realiza um ataque básico!\n";
            monstro->receberDano(10.0f); // Dano básico fixo para simplificar
            perdeuTurno = true;
        } else {
            Habilidade* hab = heroi->escolherHabilidade(escolhaAtaque - 1);
            if (hab) {
                hab->usar(heroi, monstro);
                perdeuTurno = true;
            } else {
                cout << "Ação inválida, perdeu o turno!\n";
                perdeuTurno = true;
            }
        }

        if (!perdeuTurno) continue;

        if (!monstro->isVivo()) {
            cout << "\n>>> VOCÊ DERROTOU O " << monstro->getNome() << "! <<<\n\n";
            heroi->ganharExperiencia(50.0f * monstro->getNivel());
            return true;
        }

        // Turno do Monstro
        float danoMonstro = monstro->realizarAtaque();
        heroi->receberDano(danoMonstro);

        if (!heroi->isVivo()) {
            cout << "\n>>> " << heroi->getNome() << " CAIU EM BATALHA... GAME OVER <<<\n";
            return false;
        }

        turno++;
    }
    return false;
}
