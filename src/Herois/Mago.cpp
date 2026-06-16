#include "../include/Mago.hpp"
#include <iostream>

Mago::Mago(string p_nome, int p_nivel, float p_vida, float p_inteligencia) 
    : Jogador(p_nome, p_nivel, p_vida, 100.0f, 3.0f), inteligencia(p_inteligencia) {}

void Mago::subirNivel() {
    nivel++;
    maxVida += 25.0f;
    vida = maxVida; 
    maxEnergia += 20.0f;
    inteligencia += 10.0f;
    defesa += 1.5f;
    cout << "\n>>> LEVEL UP! " << nome << " atingiu o Nível " << nivel << "! <<<\n";
    cout << "Vida Max: " << maxVida << " | Inteligência: " << inteligencia << " | Defesa: " << defesa << "\n";
}

void Mago::exibirOpcoesAtaque() const {
    cout << "Opções de Ataque do Mago:\n";
    cout << "1. Golpe de Cajado (0 Energia) - Dano Base\n";
    cout << "2. Bola de Fogo Mágica (25 Energia) - Dano Massivo em Área\n";
}

float Mago::realizarAtaque(int escolha) {
    if (escolha == 1) {
        float dano = inteligencia * 0.5f; 
        cout << "[Mago] " << nome << " ataca fracamente com o cajado! Dano bruto: " << dano << "\n";
        return dano;
    } else if (escolha == 2) {
        if (energia >= 25.0f) {
            energia -= 25.0f;
            float dano = inteligencia * 3.0f;
            cout << "[Mago] " << nome << " conjura uma incrível BOLA DE FOGO! Dano massivo bruto: " << dano << "\n";
            return dano;
        } else {
            cout << "[Mago] Energia insuficiente! Realizando Golpe de Cajado em vez disso...\n";
            return realizarAtaque(1);
        }
    } else {
        cout << "Escolha inválida. O Mago erra a magia e perde o turno.\n";
        return 0;
    }
}
