#include "../../include/Monstro.hpp"
#include "../../include/GerenciadorJogo.hpp"
#include <iostream>

namespace RpgGame {

Monstro::Monstro(std::string p_nome, int p_nivel, int p_vida, int p_forca, int p_inteligencia)
    : Entidade(p_nome, p_nivel, p_vida), forca(p_forca), inteligencia(p_inteligencia), 
      comportamento_ataque(std::make_shared<AtaqueFisicoFeroz>()) {}

int Monstro::get_forca() const { return forca; }
int Monstro::get_inteligencia() const { return inteligencia; }

void Monstro::receber_dano(int dano) {
    pontos_vida_atual -= dano;
    if (pontos_vida_atual < 0) pontos_vida_atual = 0;
    
    std::string log = "[" + nome + " recebe " + std::to_string(dano) + " de dano!]";
    GerenciadorJogo::get_instancia().notificar(log);
}

int Monstro::realizar_ataque() const {
    if (comportamento_ataque) {
        int dano = comportamento_ataque->calcular_dano(forca, inteligencia);
        std::string log = nome + " usa " + comportamento_ataque->get_nome_ataque() + "!";
        GerenciadorJogo::get_instancia().notificar(log);
        return dano;
    }
    
    std::string log = nome + " ataca ferozmente!";
    GerenciadorJogo::get_instancia().notificar(log);
    return static_cast<int>(forca * 1.5f);
}

void Monstro::set_comportamento_ataque(std::shared_ptr<ComportamentoAtaque> comp) {
    comportamento_ataque = comp;
}

Goblin::Goblin() : Monstro("Goblin", 1, 30, 5, 2) {
    set_comportamento_ataque(std::make_shared<AtaqueFisicoFeroz>());
}

GoblinChefao::GoblinChefao() : Monstro("Goblin Chefao", 5, 100, 20, 5) {
    set_comportamento_ataque(std::make_shared<AtaqueFisicoFeroz>());
}

OrcMonstro::OrcMonstro() : Monstro("Orc Furioso", 3, 80, 15, 3) {
    set_comportamento_ataque(std::make_shared<AtaqueFisicoFeroz>());
}

GiganteMalvado::GiganteMalvado() : Monstro("Gigante Malvadão", 10, 300, 50, 40) {
    set_comportamento_ataque(std::make_shared<AtaqueFisicoFeroz>());
}

LoboMau::LoboMau() : Monstro("Lobo Mau", 5, 100, 20, 5) {
    set_comportamento_ataque(std::make_shared<AtaqueFisicoFeroz>());
}

PeppaPig::PeppaPig() : Monstro("Peppa Pig", 20, 1000, 100, 100) {
    // Peppa pig usa ataque mágico arcano como graça!
    set_comportamento_ataque(std::make_shared<AtaqueMagicoArcano>());
}

} // namespace RpgGame
