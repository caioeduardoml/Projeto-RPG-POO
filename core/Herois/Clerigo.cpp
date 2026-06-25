#include "../../include/Clerigo.hpp"
#include "../../include/GerenciadorJogo.hpp"
#include <iostream>
#include <memory>

namespace RpgGame {

Clerigo::Clerigo(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel)
    : Personagem(p_nome, "Clérigo", p_raca, p_nivel, 120, 10, 18) {
    adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Luz Sagrada", "Ataque de energia divina", 15, 20));
    adicionar_habilidade(std::make_unique<HabilidadeSuporte>("Cura Divina", "Restaura os pontos de vida", 15, 35));
}

void Clerigo::subir_nivel() {
    pontos_vida_max += 15;
    pontos_vida_atual = pontos_vida_max;
    forca += 2;
    inteligencia += 4;
    
    std::string msg = nome + " subiu para o nível " + std::to_string(nivel) + "!\n" +
                      "Vida máxima aumentada para " + std::to_string(pontos_vida_max) + 
                      " e Inteligência para " + std::to_string(inteligencia) + ".";
    GerenciadorJogo::get_instancia().notificar(msg);

    if (nivel == 2) {
        adicionar_habilidade(std::make_unique<HabilidadeDefensiva>("Escudo Divino", "Aumenta a defesa", 10, 30));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Escudo Divino! <<<");
    } else if (nivel == 3) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Julgamento", "Ataque sagrado de fogo", 25, 50));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Julgamento! <<<");
    } else if (nivel == 4) {
        adicionar_habilidade(std::make_unique<HabilidadeSuporte>("Ressurreição", "Restaura muito a vida", 40, 100));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Ressurreição! <<<");
    } else if (nivel == 5) {
        adicionar_habilidade(std::make_unique<HabilidadeSuporte>("Prece de Cura", "Cura divina em área", 30, 80));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Prece de Cura! <<<");
    } else if (nivel == 6) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Ira de Deus", "Ataque divino catastrófico", 60, 180));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Ira de Deus! <<<");
    }
}

} // namespace RpgGame
