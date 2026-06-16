#include "../include/Ladrao.hpp"
#include <iostream>
#include <cstdlib>

Ladrao::Ladrao(string p_nome, int p_nivel, float p_vida, float p_agilidade, float p_chance_critico) 
    : Jogador(p_nome, p_nivel, p_vida, 40.0f, 2.0f), agilidade(p_agilidade), chance_critico(p_chance_critico) {}

void Ladrao::subirNivel() {
    nivel++;
    maxVida += 20.0f;
    vida = maxVida; 
    maxEnergia += 10.0f;
    agilidade += 6.0f;
    chance_critico += 0.05f;
    defesa += 1.0f;
    cout << "\n>>> LEVEL UP! " << nome << " atingiu o Nível " << nivel << "! <<<\n";
    cout << "Vida Max: " << maxVida << " | Agilidade: " << agilidade << " | Chance Crítico: " << chance_critico*100 << "% | Defesa: " << defesa << "\n";
}

void Ladrao::exibirOpcoesAtaque() const {
    cout << "Opções de Ataque do Ladrão:\n";
    cout << "1. Ataque Rápido (0 Energia) - Pode causar Crítico\n";
    cout << "2. Assassinato Furtivo (15 Energia) - Crítico Garantido\n";
}

float Ladrao::realizarAtaque(int escolha) {
    if (escolha == 1) {
        float dano_base = agilidade;
        float sorte = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

        if (sorte <= chance_critico) {
            float dano_critico = dano_base * 3.0f; 
            cout << "[Ladrão] " << nome << " ataca rápido e encontra uma brecha! ACERTO CRÍTICO! Dano bruto: " << dano_critico << "\n";
            return dano_critico;
        } else {
            cout << "[Ladrão] " << nome << " realiza um ataque rápido! Dano bruto: " << dano_base << "\n";
            return dano_base;
        }
    } else if (escolha == 2) {
        if (energia >= 15.0f) {
            energia -= 15.0f;
            float dano_critico = agilidade * 4.0f;
            cout << "[Ladrão] " << nome << " surge das sombras para um ASSASSINATO FURTIVO! Dano letal bruto: " << dano_critico << "\n";
            return dano_critico;
        } else {
            cout << "[Ladrão] Energia insuficiente para se esconder! Realizando Ataque Rápido...\n";
            return realizarAtaque(1);
        }
    } else {
        cout << "Escolha inválida. O Ladrão escorrega.\n";
        return 0;
    }
}
