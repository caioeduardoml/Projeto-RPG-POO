#include "../include/Ladrao.hpp"
#include <iostream>

Ladrao::Ladrao(string p_nome, Raca* p_raca, int p_nivel)
    : Personagem(p_nome, "Ladrão", p_raca, p_nivel, 100.0f, 12.0f, 12.0f) {
    adicionarHabilidade(new HabilidadeOfensiva("Ataque Furtivo", "Causa dano extra se não for detectado", 10.0f, 30.0f));
}

void Ladrao::subirNivel() {
    maxVida += 12.0f;
    vida = maxVida;
    forca += 3.0f;
    inteligencia += 3.0f;
    cout << nome << " subiu para o nível " << nivel << "!\n";

    if(nivel == 2){
        adicionarHabilidade(new HabilidadeOfensiva("Ataque olhos fechado", "Causa dano extra se não for detectado", 10.0f, 60.0f));
    }
    else if(nivel == 3){
        adicionarHabilidade(new HabilidadeOfensiva("Ataque com punho", "Causa dano extra se não for detectado", 10.0f, 50.0f));
    }
    else if (nivel == 4) {
        adicionarHabilidade(new HabilidadeOfensiva("Facada nas Costas", "Ataque fatal e preciso", 20.0f, 80.0f));
    }
    else if (nivel == 5) {
        adicionarHabilidade(new HabilidadeDefensiva("Evasão Perfeita", "Desvia de ataques com extrema facilidade", 15.0f, 100.0f));
    }
    else if (nivel == 6) {
        adicionarHabilidade(new HabilidadeOfensiva("Roubo de Vida", "Ataca o inimigo e recupera vida", 25.0f, 120.0f));
    }
}
