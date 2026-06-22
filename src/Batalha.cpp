#include "../include/Batalha.hpp"
#include "../include/Item.hpp"
#include <iostream>
#include <cstdlib>

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
        cout << "Escolha sua ação (-2 para Equipamentos, -1 para Inventário, 0 para ataque básico, 1+ para habilidade): ";
        cin >> escolhaAtaque;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            escolhaAtaque = 0;
        }

        cout << "\n";
        bool perdeuTurno = false;
        
        if (escolhaAtaque == -2) {
            heroi->exibirEquipamentos();
            string slotEscolhido;
            cout << "Digite o nome do slot para desequipar (Ex: Arma, Capacete) ou 0 para cancelar: ";
            cin >> slotEscolhido;
            if (slotEscolhido == "0") {
                cout << "Ação cancelada. Turno reiniciado.\n";
                continue;
            } else if (slotEscolhido == "Arma" || slotEscolhido == "arma") {
                heroi->desequiparArma();
                continue;
            } else {
                heroi->desequiparArmadura(slotEscolhido);
                continue;
            }
        } else if (escolhaAtaque == -1) {
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
            monstro->receberDano(heroi->getDanoTotal());
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
            cout << "\n>>> VOCÊ DERROTOU O " << monstro->getNome() << "! <<<\n";
            Item* drop = gerarDropAleatorio();
            if (drop) {
                cout << ">>> O monstro dropou: " << drop->getNome() << " (" << drop->getDescricao() << ") <<<\n\n";
                heroi->getInventario().adicionarItem(drop);
            } else {
                cout << "\n";
            }
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

Item* Batalha::gerarDropAleatorio() {
    int chance = rand() % 100;
    if (chance < 40) { // 40% chance de consumível
        int tipo = rand() % 3;
        if (tipo == 0) return new Pocao("Poção de Vida", "Restaura 50 de vida", 0.5f, 50.0f);
        if (tipo == 1) return new PocaoEnergia("Poção de Mana", "Restaura 30 de energia", 0.5f, 30.0f);
        if (tipo == 2) return new BombaCaseira("Bomba Menor", "Causa 20 de dano", 1.0f, 20.0f);
    } else if (chance < 70) { // 30% chance de arma/escudo
        int tipo = rand() % 4;
        if (tipo == 0) return new Arma("Espada de Aço", "Arma cortante", 3.0f, 20.0f);
        if (tipo == 1) return new Arma("Cajado Místico", "Arma mágica", 2.0f, 15.0f);
        if (tipo == 2) return new Arma("Arco Longo", "Ataque à distância", 3.0f, 18.0f);
        if (tipo == 3) return new Armadura("Escudo de Madeira", "Proteção básica", 5.0f, 10.0f);
    } else { // 30% chance de armadura/acessório
        int tipo = rand() % 5;
        if (tipo == 0) return new Armadura("Capacete de Ferro", "Protege a cabeça", 3.0f, 10.0f);
        if (tipo == 1) return new Armadura("Peitoral de Aço", "Protege o torso", 8.0f, 20.0f);
        if (tipo == 2) return new Armadura("Bota de Couro", "Protege os pés", 2.0f, 5.0f);
        if (tipo == 3) return new Armadura("Anel da Força", "Aumenta atributos", 0.1f, 5.0f);
        if (tipo == 4) return new Armadura("Colar Mágico", "Aumenta resistência", 0.2f, 8.0f);
    }
    return nullptr;
}
