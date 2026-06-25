#include "../../include/Arqueiro.hpp"
#include "../../include/GerenciadorJogo.hpp"
#include <iostream>
#include <memory>

namespace RpgGame {

Arqueiro::Arqueiro(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel)
    : Personagem(p_nome, "Arqueiro", p_raca, p_nivel, 100, 15, 10) {
    adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Tiro Certeiro", "Disparo preciso de flecha", 10, 25));
    adicionar_habilidade(std::make_unique<HabilidadeDefensiva>("Esquiva", "Aumenta a chance de esquiva", 10, 15));
}

void Arqueiro::subir_nivel() {
    pontos_vida_max += 12;
    pontos_vida_atual = pontos_vida_max;
    forca += 4;
    inteligencia += 2;
    
    std::string msg = nome + " subiu para o nível " + std::to_string(nivel) + "!\n" +
                      "Vida máxima aumentada para " + std::to_string(pontos_vida_max) + 
                      " e Força para " + std::to_string(forca) + ".";
    GerenciadorJogo::get_instancia().notificar(msg);

    if (nivel == 2) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Chuva de Flechas", "Dispara várias flechas", 25, 45));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Chuva de Flechas! <<<");
    } else if (nivel == 3) {
        adicionar_habilidade(std::make_unique<HabilidadeDefensiva>("Passo Leve", "Aumenta esquiva consideravelmente", 15, 30));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Passo Leve! <<<");
    }
}

} // namespace RpgGame
