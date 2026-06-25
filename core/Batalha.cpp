#include "../include/Batalha.hpp"
#include "../include/Item.hpp"
#include "../include/Exceptions.hpp"
#include <iostream>
#include <cstdlib>

namespace RpgGame {

Batalha::Batalha(std::shared_ptr<Personagem> p_heroi, std::shared_ptr<Monstro> p_monstro)
    : heroi(p_heroi), monstro(p_monstro) {}

bool Batalha::iniciar() {
    std::cout << "=======================================\n";
    std::cout << " BATALHA: " << heroi->get_nome() << " VS " << monstro->get_nome() << "!\n";
    std::cout << "=======================================\n";

    int turno = 1;

    while (heroi->is_vivo() && monstro->is_vivo()) {
        std::cout << "\n--- Turno " << turno << " ---\n";
        
        // Turno do Herói
        std::cout << "[Seu Status] ";
        heroi->exibir_status();
        std::cout << "[Inimigo]    ";
        monstro->exibir_status();
        std::cout << "\n";

        heroi->listar_habilidades();
        int escolhaAtaque;
        std::cout << "Escolha sua ação (-2 para Equipamentos, -1 para Inventário, 0 para ataque básico, 1+ para habilidade): ";
        std::cin >> escolhaAtaque;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            escolhaAtaque = 0;
        }

        std::cout << "\n";
        bool perdeuTurno = false;
        
        try {
            if (escolhaAtaque == -2) {
                heroi->exibir_equipamentos();
                std::string slotEscolhido;
                std::cout << "Digite o nome do slot para desequipar (Ex: Arma, Capacete) ou 0 para cancelar: ";
                std::cin >> slotEscolhido;
                if (slotEscolhido == "0") {
                    std::cout << "Ação cancelada. Turno reiniciado.\n";
                    continue;
                } else if (slotEscolhido == "Arma" || slotEscolhido == "arma") {
                    heroi->desequipar_item("Arma");
                    continue;
                } else {
                    heroi->desequipar_item(slotEscolhido);
                    continue;
                }
            } else if (escolhaAtaque == -1) {
                heroi->get_inventario().listar_itens();
                int escolhaItem;
                std::cout << "Escolha um item (0 para cancelar): ";
                std::cin >> escolhaItem;
                
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    escolhaItem = 0;
                }
                
                if (escolhaItem > 0) {
                    auto itemEscolhido = heroi->get_inventario().get_item(escolhaItem - 1);
                    if (itemEscolhido) {
                        heroi->usar_item(itemEscolhido->get_nome());
                        perdeuTurno = true;
                    } else {
                        std::cout << "Item inválido!\n";
                    }
                } else {
                    std::cout << "Ação cancelada. Turno reiniciado.\n";
                    continue; 
                }
            } else if (escolhaAtaque == 0) {
                heroi->atacar(*monstro, 0);
                perdeuTurno = true;
            } else {
                heroi->atacar(*monstro, escolhaAtaque);
                perdeuTurno = true;
            }
        } catch (const RPGException& e) {
            std::cout << "Erro: " << e.what() << "\n";
            std::cout << "Tente novamente.\n";
            continue;
        }

        if (!perdeuTurno) continue;

        if (!monstro->is_vivo()) {
            std::cout << "\n>>> VOCÊ DERROTOU O " << monstro->get_nome() << "! <<<\n";
            try {
                auto drop = gerar_drop_aleatorio();
                if (drop) {
                    std::cout << ">>> O monstro dropou: " << drop->get_nome() << " (" << drop->get_descricao() << ") <<<\n\n";
                    heroi->get_inventario().adicionar_item(drop);
                } else {
                    std::cout << "\n";
                }
            } catch (const InventarioException& e) {
                std::cout << "O monstro dropou um item, mas: " << e.what() << "\n\n";
            }
            heroi->ganhar_experiencia(50 * monstro->get_nivel());
            return true;
        }

        // Turno do Monstro
        int danoMonstro = monstro->realizar_ataque();
        heroi->receber_dano(danoMonstro);

        if (!heroi->is_vivo()) {
            std::cout << "\n>>> " << heroi->get_nome() << " CAIU EM BATALHA... GAME OVER <<<\n";
            return false;
        }

        turno++;
    }
    return false;
}

std::shared_ptr<Item> Batalha::gerar_drop_aleatorio() {
    int chance = rand() % 100;
    if (chance < 40) { // 40% chance de consumível
        int tipo = rand() % 3;
        if (tipo == 0) return std::make_shared<Pocao>("Poção de Vida", "Restaura 50 de vida", 0.5, 5, 50.0f);
        if (tipo == 1) return std::make_shared<PocaoEnergia>("Poção de Mana", "Restaura 30 de energia", 0.5, 5, 30.0f);
        if (tipo == 2) return std::make_shared<BombaCaseira>("Bomba Menor", "Causa 20 de dano", 1.0, 10, 20.0f);
    } else if (chance < 70) { // 30% chance de arma/escudo
        int tipo = rand() % 4;
        if (tipo == 0) return std::make_shared<Arma>("Espada de Aço", "Arma cortante", 3.0, 10, 20.0f);
        if (tipo == 1) return std::make_shared<Arma>("Cajado Místico", "Arma mágica", 2.0, 12, 15.0f);
        if (tipo == 2) return std::make_shared<Arma>("Arco Longo", "Ataque à distância", 3.0, 15, 18.0f);
        if (tipo == 3) return std::make_shared<Armadura>("Escudo de Madeira", "Proteção básica", 5.0, 8, 10.0f);
    } else { // 30% chance de armadura/acessório
        int tipo = rand() % 5;
        if (tipo == 0) return std::make_shared<Armadura>("Capacete de Ferro", "Protege a cabeça", 3.0, 10, 10.0f);
        if (tipo == 1) return std::make_shared<Armadura>("Peitoral de Aço", "Protege o torso", 8.0, 25, 20.0f);
        if (tipo == 2) return std::make_shared<Armadura>("Bota de Couro", "Protege os pés", 2.0, 6, 5.0f);
        if (tipo == 3) return std::make_shared<Armadura>("Anel da Força", "Aumenta atributos", 0.1, 15, 5.0f);
        if (tipo == 4) return std::make_shared<Armadura>("Colar Mágico", "Aumenta resistência", 0.2, 18, 8.0f);
    }
    return nullptr;
}

} // namespace RpgGame
