#include "../include/Clerigo.hpp"
#include <iostream>

Clerigo::Clerigo(string p_nome, Raca* p_raca, int p_nivel)
    : Personagem(p_nome, "Clérigo", p_raca, p_nivel, 120.0f, 10.0f, 18.0f) {
    adicionarHabilidade(new HabilidadeOfensiva("Luz Sagrada", "Ataque de energia divina", 15.0f, 20.0f));
    adicionarHabilidade(new HabilidadeSuporte("Cura Divina", "Restaura os pontos de vida", 15.0f, 35.0f));
}

void Clerigo::subirNivel() {
    maxVida += 15.0f;
    vida = maxVida;
    forca += 2.0f;
    inteligencia += 4.0f;
    cout << nome << " subiu para o nível " << nivel << "!\n";
    cout << "Vida máxima aumentada para " << maxVida << " e Inteligência para " << inteligencia << ".\n";

    if (nivel == 2) {
        cout << ">>> Nova Habilidade Desbloqueada: Escudo Divino! <<<\n";
        adicionarHabilidade(new HabilidadeDefensiva("Escudo Divino", "Aumenta a defesa", 10.0f, 30.0f));
    } else if (nivel == 3) {
        cout << ">>> Nova Habilidade Desbloqueada: Julgamento! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Julgamento", "Ataque sagrado de fogo", 25.0f, 50.0f));
    } else if (nivel == 4) {
        cout << ">>> Nova Habilidade Desbloqueada: Ressurreição! <<<\n";
        adicionarHabilidade(new HabilidadeSuporte("Ressurreição", "Restaura muito a vida", 40.0f, 100.0f));
    } else if (nivel == 5) {
        cout << ">>> Nova Habilidade Desbloqueada: Prece de Cura! <<<\n";
        adicionarHabilidade(new HabilidadeSuporte("Prece de Cura", "Cura divina em área", 30.0f, 80.0f));
    } else if (nivel == 6) {
        cout << ">>> Nova Habilidade Desbloqueada: Ira de Deus! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Ira de Deus", "Ataque divino catastrófico", 60.0f, 180.0f));
    }
}
