#include "../include/Druida.hpp"
#include <iostream>

Druida::Druida(string p_nome, Raca* p_raca, int p_nivel)
    : Personagem(p_nome, "Druida", p_raca, p_nivel, 120.0f, 10.0f, 15.0f) {
    adicionarHabilidade(new HabilidadeOfensiva("Ira da Natureza", "Magia ofensiva da natureza", 15.0f, 25.0f));
    adicionarHabilidade(new HabilidadeSuporte("Cura da Terra", "Cura um aliado", 20.0f, 30.0f));
}

void Druida::subirNivel() {
    maxVida += 15.0f;
    vida = maxVida;
    forca += 2.0f;
    inteligencia += 4.0f;
    cout << nome << " subiu para o nível " << nivel << "!\n";
}
