#include "../../include/Druida.hpp"
#include "../../include/GerenciadorJogo.hpp"
#include <iostream>
#include <memory>

namespace RpgGame {

Druida::Druida(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel)
    : Personagem(p_nome, "Druida", p_raca, p_nivel, 120, 10, 15), comunhao(20) {
    adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Ira da Natureza", "Magia ofensiva da natureza", 15, 25));
    adicionar_habilidade(std::make_unique<HabilidadeSuporte>("Cura da Terra", "Cura um aliado", 20, 30));
}

void Druida::subir_nivel() {
    pontos_vida_max += 15;
    pontos_vida_atual = pontos_vida_max;
    forca += 2;
    inteligencia += 4;
    comunhao += 10;
    if (comunhao > 100) comunhao = 100;
    
    std::string msg = nome + " subiu para o nível " + std::to_string(nivel) + "!\n" +
                      "Vida máxima aumentada para " + std::to_string(pontos_vida_max) + 
                      ", Inteligência para " + std::to_string(inteligencia) + 
                      " e Comunhão aumentada para " + std::to_string(comunhao) + "%.";
    GerenciadorJogo::get_instancia().notificar(msg);

    if (nivel == 2) {
        adicionar_habilidade(std::make_unique<HabilidadeDefensiva>("Pele de Árvore", "Reduz danos recebidos", 15, 40));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Pele de Árvore! <<<");
    } else if (nivel == 3) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Enxame de Insetos", "Causa dano contínuo", 20, 50));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Enxame de Insetos! <<<");
    } else if (nivel == 4) {
        adicionar_habilidade(std::make_unique<HabilidadeSuporte>("Regeneração Natural", "Cura contínua", 25, 60));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Regeneração Natural! <<<");
    } else if (nivel == 5) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Raízes Aprisionadoras", "Paralisa o inimigo", 30, 80));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Raízes Aprisionadoras! <<<");
    } else if (nivel == 6) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Fúria da Floresta", "Dano em área massivo", 50, 150));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Fúria da Floresta! <<<");
    }
}

void Druida::receber_dano(int dano) {
    // Especialização: Absorve 20% do dano líquido e converte em recuperação de energia
    int defesa = get_defesa_total();
    int danoLiquido = dano - defesa;
    if (danoLiquido < 0) danoLiquido = 0;

    int absorvido = static_cast<int>(danoLiquido * 0.2f);
    danoLiquido -= absorvido;

    pontos_vida_atual -= danoLiquido;
    if (pontos_vida_atual < 0) pontos_vida_atual = 0;

    // Converte dano absorvido em energia recuperada
    int energiaRecuperada = absorvido / 2;
    if (energiaRecuperada > 0) {
        recuperar_energia(energiaRecuperada);
    }
    
    // Aumenta a comunhão ao sofrer dano
    comunhao += danoLiquido / 4;
    if (comunhao > 100) comunhao = 100;

    std::string log = "[" + nome + " recebe " + std::to_string(danoLiquido) + 
                      " de dano! (Absorvido " + std::to_string(absorvido) + " convertido em " + std::to_string(energiaRecuperada) + " Energia)]";
    GerenciadorJogo::get_instancia().notificar(log);
}

int Druida::get_comunhao() const { return comunhao; }

} // namespace RpgGame
