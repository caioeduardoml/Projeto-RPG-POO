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

    if (nivel == 2) {
        cout << ">>> Nova Habilidade Desbloqueada: Raio Congelante! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Raio Congelante", "Magia que causa dano e lentidão", 25.0f, 50.0f));
    } else if (nivel == 3) {
        cout << ">>> Nova Habilidade Desbloqueada: Escudo Arcano! <<<\n";
        adicionarHabilidade(new HabilidadeDefensiva("Escudo Arcano", "Escudo mágico de proteção", 20.0f, 60.0f));
    } else if (nivel == 4) {
        cout << ">>> Nova Habilidade Desbloqueada: Tempestade de Raios! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Tempestade de Raios", "Dano elétrico em área", 35.0f, 90.0f));
    } else if (nivel == 5) {
        cout << ">>> Nova Habilidade Desbloqueada: Clareza Mental! <<<\n";
        adicionarHabilidade(new HabilidadeSuporte("Clareza Mental", "Restaura bastante energia", 10.0f, 100.0f));
    } else if (nivel == 6) {
        cout << ">>> Nova Habilidade Desbloqueada: Meteoro! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Meteoro", "Destruição em massa", 60.0f, 200.0f));
    }
}
