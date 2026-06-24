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

    if (nivel == 2) {
        cout << ">>> Nova Habilidade Desbloqueada: Corte Duplo! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Corte Duplo", "Ataque rápido com a espada", 20.0f, 50.0f));
    } else if (nivel == 3) {
        cout << ">>> Nova Habilidade Desbloqueada: Postura de Combate! <<<\n";
        adicionarHabilidade(new HabilidadeDefensiva("Postura de Combate", "Aumenta defesa consideravelmente", 15.0f, 40.0f));
    } else if (nivel == 4) {
        cout << ">>> Nova Habilidade Desbloqueada: Ataque Giratório! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Ataque Giratório", "Causa dano a todos ao redor", 30.0f, 80.0f));
    } else if (nivel == 5) {
        cout << ">>> Nova Habilidade Desbloqueada: Grito de Guerra! <<<\n";
        adicionarHabilidade(new HabilidadeSuporte("Grito de Guerra", "Aumenta ataque temporariamente", 20.0f, 50.0f));
    } else if (nivel == 6) {
        cout << ">>> Nova Habilidade Desbloqueada: Golpe Devastador! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Golpe Devastador", "Ataque com força máxima", 50.0f, 150.0f));
    }
}
