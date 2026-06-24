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

    if (nivel == 2) {
        cout << ">>> Nova Habilidade Desbloqueada: Pele de Árvore! <<<\n";
        adicionarHabilidade(new HabilidadeDefensiva("Pele de Árvore", "Reduz danos recebidos", 15.0f, 40.0f));
    } else if (nivel == 3) {
        cout << ">>> Nova Habilidade Desbloqueada: Enxame de Insetos! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Enxame de Insetos", "Causa dano contínuo", 20.0f, 50.0f));
    } else if (nivel == 4) {
        cout << ">>> Nova Habilidade Desbloqueada: Regeneração Natural! <<<\n";
        adicionarHabilidade(new HabilidadeSuporte("Regeneração Natural", "Cura contínua", 25.0f, 60.0f));
    } else if (nivel == 5) {
        cout << ">>> Nova Habilidade Desbloqueada: Raízes Aprisionadoras! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Raízes Aprisionadoras", "Paralisa o inimigo", 30.0f, 80.0f));
    } else if (nivel == 6) {
        cout << ">>> Nova Habilidade Desbloqueada: Fúria da Floresta! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Fúria da Floresta", "Dano em área massivo", 50.0f, 150.0f));
    }
}
