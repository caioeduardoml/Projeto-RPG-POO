#include "../include/Mago.hpp"
#include <iostream>

Mago::Mago(string p_nome, Raca* p_raca, int p_nivel)
    : Personagem(p_nome, "Mago", p_raca, p_nivel, 80.0f, 5.0f, 25.0f) {
    adicionarHabilidade(new HabilidadeOfensiva("Bola de Fogo", "Magia elemental de fogo", 20.0f, 40.0f));
    adicionarHabilidade(new HabilidadeSuporte("Cura Menor", "Restaura uma pequena quantidade de vida", 15.0f, 20.0f));
}

void Mago::subirNivel() {
    maxVida += 10.0f;
    vida = maxVida;
    forca += 1.0f;
    inteligencia += 6.0f;
    cout << nome << " subiu para o nível " << nivel << "!\n";
    cout << "Vida máxima aumentada para " << maxVida << " e Inteligência para " << inteligencia << ".\n";
}
