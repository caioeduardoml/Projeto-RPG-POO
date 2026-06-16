#include "../include/Guerreiro.hpp"
#include <iostream>

Guerreiro::Guerreiro(string p_nome, int p_nivel, float p_vida, float p_forca) 
    : Jogador(p_nome, p_nivel, p_vida, 50.0f, 10.0f), forca(p_forca) {}

void Guerreiro::subirNivel() {
    nivel++;
    maxVida += 50.0f;
    vida = maxVida; // Restaura a vida
    maxEnergia += 10.0f;
    forca += 8.0f;
    defesa += 4.0f;
    cout << "\n>>> LEVEL UP! " << nome << " atingiu o Nível " << nivel << "! <<<\n";
    cout << "Vida Max: " << maxVida << " | Força: " << forca << " | Defesa: " << defesa << "\n";
}

void Guerreiro::exibirOpcoesAtaque() const {
    cout << "Opções de Ataque do Guerreiro:\n";
    cout << "1. Golpe de Espada (0 Energia) - Dano Base\n";
    cout << "2. Fúria Incontrolável (20 Energia) - Dano Massivo\n";
}

float Guerreiro::realizarAtaque(int escolha) {
    if (escolha == 1) {
        float dano = forca; 
        cout << "[Guerreiro] " << nome << " ataca com um Golpe de Espada! Dano bruto: " << dano << "\n";
        return dano;
    } else if (escolha == 2) {
        if (energia >= 20.0f) {
            energia -= 20.0f;
            float dano = forca * 2.5f;
            cout << "[Guerreiro] " << nome << " usa Fúria Incontrolável! Dano massivo bruto: " << dano << "\n";
            return dano;
        } else {
            cout << "[Guerreiro] Energia insuficiente! Realizando Golpe de Espada em vez disso...\n";
            return realizarAtaque(1);
        }
    } else {
        cout << "Escolha inválida. O Guerreiro perde o foco e ataca fraco.\n";
        return forca * 0.5f;
    }
}
