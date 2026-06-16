#include "../include/Monstro.hpp"
#include <iostream>
#include <cstdlib>

Monstro::Monstro(string p_nome, int p_nivel, float p_vida, float p_forca, float p_agilidade, float p_defesa) 
    : Jogador(p_nome, p_nivel, p_vida, 50.0f, p_defesa), forca(p_forca), agilidade(p_agilidade) {}

void Monstro::subirNivel() {
    // Monstros na arena não sobem de nível
}

void Monstro::exibirOpcoesAtaque() const {
    // Monstros não exibem opções interativas
}

float Monstro::realizarAtaque(int /*escolha*/) {
    // IA Simples: Se tiver energia, 30% de chance de usar ataque forte
    float sorte = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    
    if (energia >= 15.0f && sorte > 0.7f) {
        energia -= 15.0f;
        float dano = forca * 2.0f; 
        cout << "[Monstro] " << nome << " usa um ATAQUE ESMAGADOR! Dano bruto: " << dano << "\n";
        return dano;
    } else {
        float dano_base = forca * 0.8f + agilidade * 0.2f; 
        cout << "[Monstro] " << nome << " ataca com suas garras/armas! Dano bruto: " << dano_base << "\n";
        return dano_base;
    }
}

// Goblin (Fraco)
Goblin::Goblin() : Monstro("Goblin Saqueador", 5, 50.0f, 10.0f, 15.0f, 1.0f) {}

// Orc (Médio)
Orc::Orc() : Monstro("Orc Guerreiro", 15, 150.0f, 25.0f, 10.0f, 5.0f) {}

// Dragão (Forte)
Dragao::Dragao() : Monstro("Dragão Ancião", 30, 400.0f, 50.0f, 20.0f, 20.0f) {}
