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
}
