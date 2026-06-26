#include "../../include/Arqueiro.hpp"
#include "../../include/GerenciadorJogo.hpp"
#include <iostream>
#include <memory>
#include <cstdlib>

namespace RpgGame {

Arqueiro::Arqueiro(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel)
    : Personagem(p_nome, "Arqueiro", p_raca, p_nivel, 100, 15, 10), esquiva(15) {
    adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Tiro Certeiro", "Disparo preciso de flecha", 10, 25));
    adicionar_habilidade(std::make_unique<HabilidadeDefensiva>("Esquiva", "Aumenta a chance de esquiva", 10, 15));
}

void Arqueiro::subir_nivel() {
    pontos_vida_max += 12;
    pontos_vida_atual = pontos_vida_max;
    forca += 4;
    inteligencia += 2;
    esquiva += 3;
    if (esquiva > 60) esquiva = 60;
    
    std::string msg = nome + " subiu para o nível " + std::to_string(nivel) + "!\n" +
                      "Vida máxima aumentada para " + std::to_string(pontos_vida_max) + 
                      ", Força para " + std::to_string(forca) + 
                      " e Esquiva aumentada para " + std::to_string(esquiva) + "%.";
    GerenciadorJogo::get_instancia().notificar(msg);

    if (nivel == 2) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Chuva de Flechas", "Dispara várias flechas", 25, 45));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Chuva de Flechas! <<<");
    } else if (nivel == 3) {
        adicionar_habilidade(std::make_unique<HabilidadeDefensiva>("Passo Leve", "Aumenta esquiva consideravelmente", 15, 30));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Passo Leve! <<<");
    }
}

void Arqueiro::receber_dano(int dano) {
    // Especialização: chance de se esquivar completamente do ataque
    int chance = rand() % 100;
    if (chance < esquiva) {
        std::string log = "[Esquiva! " + nome + " desviou completamente do ataque de " + std::to_string(dano) + " de dano!]";
        GerenciadorJogo::get_instancia().notificar(log);
        return;
    }

    int defesa = get_defesa_total();
    int danoLiquido = dano - defesa;
    if (danoLiquido < 0) danoLiquido = 0;
    
    pontos_vida_atual -= danoLiquido;
    if (pontos_vida_atual < 0) pontos_vida_atual = 0;

    std::string log = "[" + nome + " recebe " + std::to_string(danoLiquido) + " de dano!]";
    GerenciadorJogo::get_instancia().notificar(log);
}

int Arqueiro::get_esquiva() const { return esquiva; }

} // namespace RpgGame
