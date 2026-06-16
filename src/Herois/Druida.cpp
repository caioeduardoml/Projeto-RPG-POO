#include "../include/Druida.hpp"
#include <iostream>

Druida::Druida(string p_nome, int p_nivel, float p_vida, float p_sabedoria) 
    : Jogador(p_nome, p_nivel, p_vida, 80.0f, 5.0f), sabedoria(p_sabedoria) {}

void Druida::subirNivel() {
    nivel++;
    maxVida += 40.0f;
    vida = maxVida; 
    maxEnergia += 15.0f;
    sabedoria += 7.0f;
    defesa += 2.5f;
    cout << "\n>>> LEVEL UP! " << nome << " atingiu o Nível " << nivel << "! <<<\n";
    cout << "Vida Max: " << maxVida << " | Sabedoria: " << sabedoria << " | Defesa: " << defesa << "\n";
}

void Druida::exibirOpcoesAtaque() const {
    cout << "Opções de Ataque do Druida:\n";
    cout << "1. Lançar Pedra (0 Energia) - Dano Base\n";
    cout << "2. Ira da Natureza (15 Energia) - Dano Natural Intenso\n";
}

float Druida::realizarAtaque(int escolha) {
    if (escolha == 1) {
        float dano = sabedoria * 0.8f; 
        cout << "[Druida] " << nome << " lanca uma pedra! Dano bruto: " << dano << "\n";
        return dano;
    } else if (escolha == 2) {
        if (energia >= 15.0f) {
            energia -= 15.0f;
            float dano = sabedoria * 2.5f;
            cout << "[Druida] " << nome << " invoca a Ira da Natureza! Dano massivo bruto: " << dano << "\n";
            return dano;
        } else {
            cout << "[Druida] Energia insuficiente! Lançando pedra em vez disso...\n";
            return realizarAtaque(1);
        }
    } else {
        cout << "Escolha inválida. O Druida tropeça em uma raiz.\n";
        return 0;
    }
}
