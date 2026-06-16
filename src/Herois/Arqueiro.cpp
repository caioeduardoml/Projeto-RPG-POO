#include "../include/Arqueiro.hpp"
#include <iostream>

Arqueiro::Arqueiro(string p_nome, int p_nivel, float p_vida, float p_destreza, float p_agilidade) 
    : Jogador(p_nome, p_nivel, p_vida, 60.0f, 4.0f), destreza(p_destreza), agilidade(p_agilidade) {}

void Arqueiro::subirNivel() {
    nivel++;
    maxVida += 30.0f;
    vida = maxVida; 
    maxEnergia += 15.0f;
    destreza += 5.0f;
    agilidade += 5.0f;
    defesa += 2.0f;
    cout << "\n>>> LEVEL UP! " << nome << " atingiu o Nível " << nivel << "! <<<\n";
    cout << "Vida Max: " << maxVida << " | Destreza: " << destreza << " | Agilidade: " << agilidade << " | Defesa: " << defesa << "\n";
}

void Arqueiro::exibirOpcoesAtaque() const {
    cout << "Opções de Ataque do Arqueiro:\n";
    cout << "1. Bater com o Arco (0 Energia) - Dano Base\n";
    cout << "2. Flecha Perfurante (10 Energia) - Dano Rápido e Preciso\n";
}

float Arqueiro::realizarAtaque(int escolha) {
    if (escolha == 1) {
        float dano = destreza * 1.5f; 
        cout << "[Arqueiro] " << nome << " bate com o arco! Dano bruto: " << dano << "\n";
        return dano;
    } else if (escolha == 2) {
        if (energia >= 10.0f) {
            energia -= 10.0f;
            float dano = agilidade * 2.5f;
            cout << "[Arqueiro] " << nome << " atira uma Flecha Perfurante! Dano crítico bruto: " << dano << "\n";
            return dano;
        } else {
            cout << "[Arqueiro] Energia insuficiente para armar o arco! Batendo com o arco em vez disso...\n";
            return realizarAtaque(1);
        }
    } else {
        cout << "Escolha inválida. A flecha cai no chão.\n";
        return 0;
    }
}
