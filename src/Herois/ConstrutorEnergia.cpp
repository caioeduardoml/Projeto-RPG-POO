#include "../include/ConstrutorEnergia.hpp"
#include <iostream>

ConstrutorEnergia::ConstrutorEnergia(string p_nome, int p_nivel, float p_vida, float p_criatividade) 
    : Jogador(p_nome, p_nivel, p_vida, 9999.0f, 99.0f), criatividade(p_criatividade) {}

void ConstrutorEnergia::subirNivel() {
    nivel++;
    maxVida += 40.0f;
    vida = maxVida; 
    maxEnergia += 20.0f;
    criatividade += 8.0f;
    defesa += 3.0f;
    cout << "\n>>> LEVEL UP! " << nome << " atingiu o Nível " << nivel << "! <<<\n";
    cout << "Vida Max: " << maxVida << " | Criatividade: " << criatividade << " | Defesa: " << defesa << "\n";
}

void ConstrutorEnergia::exibirOpcoesAtaque() const {
    cout << "Opções de Ataque do Construtor de Energia:\n";
    cout << "1. Soco de Energia (0 Energia) - Dano Base\n";
    cout << "2. Constructo Colossal (30 Energia) - Dano Massivo e Criativo\n";
}

float ConstrutorEnergia::realizarAtaque(int escolha) {
    if (escolha == 1) {
        float dano = criatividade * 0.5f; 
        cout << "[ConstrutorEnergia] " << nome << " ataca com as mãos infundidas! Dano bruto: " << dano << "\n";
        return dano;
    } else if (escolha == 2) {
        if (energia >= 30.0f) {
            energia -= 30.0f;
            float dano = criatividade * 3.5f;
            cout << "[ConstrutorEnergia] " << nome << " cria um CONSTRUCTO COLOSSAL! Dano destruidor bruto: " << dano << "\n";
            return dano;
        } else {
            cout << "[ConstrutorEnergia] Energia insuficiente! Dando um soco de energia em vez disso...\n";
            return realizarAtaque(1);
        }
    } else {
        cout << "Escolha inválida. O Construtor perde a concentração.\n";
        return 0;
    }
}
