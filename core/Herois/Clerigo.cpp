#include "../../include/Clerigo.hpp"
#include "../../include/GerenciadorJogo.hpp"
#include <iostream>
#include <memory>

namespace RpgGame {

Clerigo::Clerigo(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel)
    : Personagem(p_nome, "Clérigo", p_raca, p_nivel, 120, 10, 18), fe_max(50), fe_atual(50) {
    adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Luz Sagrada", "Ataque de energia divina", 15, 20));
    adicionar_habilidade(std::make_unique<HabilidadeSuporte>("Cura Divina", "Restaura os pontos de vida", 15, 35));
}

void Clerigo::subir_nivel() {
    pontos_vida_max += 15;
    pontos_vida_atual = pontos_vida_max;
    forca += 2;
    inteligencia += 4;
    fe_max += 15;
    fe_atual = fe_max;
    
    std::string msg = nome + " subiu para o nível " + std::to_string(nivel) + "!\n" +
                      "Vida máxima aumentada para " + std::to_string(pontos_vida_max) + 
                      ", Inteligência para " + std::to_string(inteligencia) + 
                      " e Fé máxima para " + std::to_string(fe_max) + ".";
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

void Clerigo::receber_dano(int dano) {
    // Especialização: Fé protege contra 30% do dano líquido consumindo 15 de fé
    int defesa = get_defesa_total();
    int danoLiquido = dano - defesa;
    if (danoLiquido < 0) danoLiquido = 0;

    int mitigado = 0;
    if (fe_atual >= 15 && danoLiquido > 0) {
        mitigado = static_cast<int>(danoLiquido * 0.3f);
        fe_atual -= 15;
        danoLiquido -= mitigado;
    }

    pontos_vida_atual -= danoLiquido;
    if (pontos_vida_atual < 0) pontos_vida_atual = 0;

    std::string log = "[" + nome + " recebe " + std::to_string(danoLiquido) + 
                      " de dano! (Mitigado por Fé: " + std::to_string(mitigado) + " | Fé restante: " + std::to_string(fe_atual) + ")]";
    GerenciadorJogo::get_instancia().notificar(log);
}

int Clerigo::get_fe_max() const { return fe_max; }
int Clerigo::get_fe_atual() const { return fe_atual; }
void Clerigo::recuperar_fe(int quantidade) {
    fe_atual += quantidade;
    if (fe_atual > fe_max) fe_atual = fe_max;
}

} // namespace RpgGame
