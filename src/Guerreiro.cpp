#include "../include/Guerreiro.hpp"
#include <iostream>

Guerreiro::Guerreiro(string p_nome, Raca* p_raca, int p_nivel)
    : Personagem(p_nome, "Guerreiro", p_raca, p_nivel, 150.0f, 20.0f, 5.0f) {
    // Habilidades iniciais do guerreiro
    adicionarHabilidade(new HabilidadeOfensiva("Golpe Forte", "Ataque físico poderoso", 15.0f, 30.0f));
    adicionarHabilidade(new HabilidadeDefensiva("Bloqueio com Escudo", "Aumenta defesa no turno", 10.0f, 20.0f));
}

void Guerreiro::subirNivel() {
    maxVida += 20.0f;
    vida = maxVida;
    forca += 5.0f;
    inteligencia += 1.0f;
    cout << nome << " subiu para o nível " << nivel << "!\n";
    cout << "Vida máxima aumentada para " << maxVida << " e Força para " << forca << ".\n";
}
