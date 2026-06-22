#include "../include/ConstrutorEnergia.hpp"
#include <iostream>

ConstrutorEnergia::ConstrutorEnergia(string p_nome, Raca* p_raca, int p_nivel)
    : Personagem(p_nome, "Construtor de Energia", p_raca, p_nivel, 150.0f, 20.0f, 20.0f) {
    adicionarHabilidade(new HabilidadeOfensiva("Kamehameha", "Ataque massivo de energia", 50.0f, 100.0f));
}

void ConstrutorEnergia::subirNivel() {
    maxVida += 50.0f;
    vida = maxVida;
    forca += 10.0f;
    inteligencia += 10.0f;
    cout << nome << " subiu para o nível " << nivel << "!\n";

    if (nivel == 2) {
        cout << ">>> Nova Habilidade Desbloqueada: Escudo de Energia! <<<\n";
        adicionarHabilidade(new HabilidadeDefensiva("Escudo de Energia", "Escudo que protege contra ataques", 0.0f, 50.0f));
    } else if (nivel == 3) {
        cout << ">>> Nova Habilidade Desbloqueada: Golpe de Energia! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Golpe de Energia", "Golpe de energia", 50.0f, 50.0f));
    } else if (nivel == 4) {
        cout << ">>> Nova Habilidade Desbloqueada: Sobrecarga! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Sobrecarga", "Explosão de energia massiva", 70.0f, 150.0f));
    } else if (nivel == 5) {
        cout << ">>> Nova Habilidade Desbloqueada: Bateria Infinita! <<<\n";
        adicionarHabilidade(new HabilidadeSuporte("Bateria Infinita", "Restaura muita energia", 0.0f, 200.0f));
    } else if (nivel == 6) {
        cout << ">>> Nova Habilidade Desbloqueada: Genki Dama! <<<\n";
        adicionarHabilidade(new HabilidadeOfensiva("Genki Dama", "Ataque supremo de energia", 100.0f, 300.0f));
    }
}
