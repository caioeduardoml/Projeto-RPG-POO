#include "../../include/Guerreiro.hpp"
#include "../../include/GerenciadorJogo.hpp"
#include <iostream>
#include <memory>

namespace RpgGame {

Guerreiro::Guerreiro(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel)
    : Personagem(p_nome, "Guerreiro", p_raca, p_nivel, 150, 20, 5), furia(0) {
    // Habilidades iniciais do guerreiro usando unique_ptr
    adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Golpe Forte", "Ataque físico poderoso", 15, 30));
    adicionar_habilidade(std::make_unique<HabilidadeDefensiva>("Bloqueio com Escudo", "Aumenta defesa no turno", 10, 20));
}

void Guerreiro::subir_nivel() {
    pontos_vida_max += 20;
    pontos_vida_atual = pontos_vida_max;
    forca += 5;
    inteligencia += 1;
    
    std::string msg = nome + " subiu para o nível " + std::to_string(nivel) + "!\n" +
                      "Vida máxima aumentada para " + std::to_string(pontos_vida_max) + 
                      " e Força para " + std::to_string(forca) + ".";
    GerenciadorJogo::get_instancia().notificar(msg);

    if (nivel == 2) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Corte Duplo", "Ataque rápido com a espada", 20, 50));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Corte Duplo! <<<");
    } else if (nivel == 3) {
        adicionar_habilidade(std::make_unique<HabilidadeDefensiva>("Postura de Combate", "Aumenta defesa consideravelmente", 15, 40));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Postura de Combate! <<<");
    } else if (nivel == 4) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Ataque Giratório", "Causa dano a todos ao redor", 30, 80));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Ataque Giratório! <<<");
    } else if (nivel == 5) {
        adicionar_habilidade(std::make_unique<HabilidadeSuporte>("Grito de Guerra", "Aumenta ataque temporariamente", 20, 50));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Grito de Guerra! <<<");
    } else if (nivel == 6) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Golpe Devastador", "Ataque com força máxima", 50, 150));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Golpe Devastador! <<<");
    }
}

void Guerreiro::receber_dano(int dano) {
    // Especialização: Mitigação com armadura e ganho de fúria
    int defesa = get_defesa_total() + (furia / 10); // A fúria concede defesa passiva extra
    int danoLiquido = dano - defesa;
    if (danoLiquido < 0) danoLiquido = 0;
    
    pontos_vida_atual -= danoLiquido;
    if (pontos_vida_atual < 0) pontos_vida_atual = 0;
    
    // Ganha fúria ao tomar dano
    furia += danoLiquido / 2;
    if (furia > 100) furia = 100;

    std::string log = "[" + nome + " recebe " + std::to_string(danoLiquido) + 
                      " de dano! (Fúria atual: " + std::to_string(furia) + ")]";
    GerenciadorJogo::get_instancia().notificar(log);
}

int Guerreiro::get_furia() const { return furia; }

} // namespace RpgGame
