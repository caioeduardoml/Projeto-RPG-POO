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

    if (nivel == 2) {
        cout << ">>> Nova Habilidade Desbloqueada: Flecha Perfurante! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Flecha Perfurante", "Ignora parte da defesa", 15.0f, 40.0f));
    } else if (nivel == 3) {
        cout << ">>> Nova Habilidade Desbloqueada: Agilidade Élfica! <<<\n";
        adicionarHabilidade(new HabilidadeSuporte("Agilidade Élfica", "Aumenta chance de esquiva", 10.0f, 30.0f));
    } else if (nivel == 4) {
        cout << ">>> Nova Habilidade Desbloqueada: Chuva de Flechas! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Chuva de Flechas", "Atinge múltiplos alvos", 25.0f, 70.0f));
    } else if (nivel == 5) {
        cout << ">>> Nova Habilidade Desbloqueada: Tiro Fatal! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Tiro Fatal", "Acerto crítico garantido", 30.0f, 100.0f));
    } else if (nivel == 6) {
        cout << ">>> Nova Habilidade Desbloqueada: Flecha do Dragão! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Flecha do Dragão", "Ataque devastador", 50.0f, 150.0f));
    }
}
