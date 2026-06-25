#include "../../include/Mago.hpp"
#include "../../include/GerenciadorJogo.hpp"
#include <iostream>
#include <memory>

namespace RpgGame {

Mago::Mago(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel)
    : Personagem(p_nome, "Mago", p_raca, p_nivel, 80, 5, 25), mana_max(100), mana_atual(100) {
    adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Bola de Fogo", "Magia elemental de fogo", 20, 40));
    adicionar_habilidade(std::make_unique<HabilidadeSuporte>("Cura Menor", "Restaura uma pequena quantidade de vida", 15, 20));
}

void Mago::subir_nivel() {
    pontos_vida_max += 10;
    pontos_vida_atual = pontos_vida_max;
    forca += 1;
    inteligencia += 6;
    mana_max += 25;
    mana_atual = mana_max;
    
    std::string msg = nome + " subiu para o nível " + std::to_string(nivel) + "!\n" +
                      "Vida máxima aumentada para " + std::to_string(pontos_vida_max) + 
                      ", Inteligência para " + std::to_string(inteligencia) + 
                      " e Mana máxima para " + std::to_string(mana_max) + ".";
    GerenciadorJogo::get_instancia().notificar(msg);

    if (nivel == 2) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Raio Congelante", "Magia que causa dano e lentidão", 25, 50));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Raio Congelante! <<<");
    } else if (nivel == 3) {
        adicionar_habilidade(std::make_unique<HabilidadeDefensiva>("Escudo Arcano", "Escudo mágico de proteção", 20, 60));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Escudo Arcano! <<<");
    } else if (nivel == 4) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Tempestade de Raios", "Dano elétrico em área", 35, 90));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Tempestade de Raios! <<<");
    } else if (nivel == 5) {
        adicionar_habilidade(std::make_unique<HabilidadeSuporte>("Clareza Mental", "Restaura bastante energia", 10, 100));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Clareza Mental! <<<");
    } else if (nivel == 6) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Meteoro", "Destruição em massa", 60, 200));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Meteoro! <<<");
    }
}

void Mago::receber_dano(int dano) {
    // Especialização: Escudo mágico consome mana para absorver 50% do dano
    int defesa = get_defesa_total();
    int danoLiquido = dano - defesa;
    if (danoLiquido < 0) danoLiquido = 0;

    int absorvido = 0;
    if (mana_atual > 0 && danoLiquido > 0) {
        absorvido = danoLiquido / 2; // Absorve metade
        if (absorvido > mana_atual) {
            absorvido = mana_atual;
        }
        mana_atual -= absorvido;
        danoLiquido -= absorvido;
    }

    pontos_vida_atual -= danoLiquido;
    if (pontos_vida_atual < 0) pontos_vida_atual = 0;

    std::string log = "[" + nome + " recebe " + std::to_string(danoLiquido) + 
                      " de dano! (Absorvido pelo Escudo Mágico: " + std::to_string(absorvido) + " | Mana restante: " + std::to_string(mana_atual) + ")]";
    GerenciadorJogo::get_instancia().notificar(log);
}

int Mago::get_mana_max() const { return mana_max; }
int Mago::get_mana_atual() const { return mana_atual; }
void Mago::recuperar_mana(int quantidade) {
    mana_atual += quantidade;
    if (mana_atual > mana_max) mana_atual = mana_max;
}

} // namespace RpgGame
