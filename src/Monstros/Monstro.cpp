#include "../include/Monstro.hpp"
#include <iostream>

Monstro::Monstro(string p_nome, int p_nivel, float p_vida, float p_forca, float p_inteligencia)
    : Entidade(p_nome, p_nivel, p_vida), forca(p_forca), inteligencia(p_inteligencia) {}

float Monstro::getForca() const { return forca; }
float Monstro::getInteligencia() const { return inteligencia; }

void Monstro::receberDano(float dano) {
    vida -= dano;
    if (vida < 0) vida = 0;
    cout << "[" << nome << " recebe " << dano << " de dano!]\n";
}

float Monstro::realizarAtaque() const {
    cout << nome << " ataca ferozmente!\n";
    return forca * 1.5f; // Dano simples baseado na força
}

Goblin::Goblin() : Monstro("Goblin", 1, 30.0f, 5.0f, 2.0f) {}

// Renomeado para não conflitar com a Raca Orc
OrcMonstro::OrcMonstro() : Monstro("Orc Furioso", 3, 80.0f, 15.0f, 3.0f) {}

GiganteMalvado::GiganteMalvado() : Monstro("Gigante Malvadão", 10, 300.0f, 50.0f, 40.0f) {}

LoboMau::LoboMau() : Monstro("Lobo Mau", 5, 100.0f, 20.0f, 5.0f) {}
