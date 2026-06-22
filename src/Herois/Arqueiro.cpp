#include "../include/Arqueiro.hpp"
#include <iostream>

Arqueiro::Arqueiro(string p_nome, Raca* p_raca, int p_nivel)
    : Personagem(p_nome, "Arqueiro", p_raca, p_nivel, 110.0f, 15.0f, 10.0f) {
    adicionarHabilidade(new HabilidadeOfensiva("Tiro Certeiro", "Ataque à distância com alta precisão", 10.0f, 25.0f));
}

void Arqueiro::subirNivel() {
    maxVida += 15.0f;
    vida = maxVida;
    forca += 3.0f;
    inteligencia += 2.0f;
    cout << nome << " subiu para o nível " << nivel << "!\n";
}
