#include "../include/GerenciadorJogo.hpp"
#include "../include/MonstroFactory.hpp"
#include "../include/Exceptions.hpp"
#include <iostream>

namespace RpgGame {

std::unique_ptr<GerenciadorJogo> GerenciadorJogo::instancia = nullptr;

GerenciadorJogo::GerenciadorJogo() : heroi(nullptr), monstro_atual(nullptr), progresso_batalha(0) {}

GerenciadorJogo& GerenciadorJogo::get_instancia() {
    if (!instancia) {
        instancia = std::unique_ptr<GerenciadorJogo>(new GerenciadorJogo());
    }
    return *instancia;
}

std::shared_ptr<Personagem> GerenciadorJogo::get_heroi() const { return heroi; }
void GerenciadorJogo::set_heroi(std::shared_ptr<Personagem> p_heroi) { heroi = p_heroi; }

std::shared_ptr<Monstro> GerenciadorJogo::get_monstro_atual() const { return monstro_atual; }
void GerenciadorJogo::set_monstro_atual(std::shared_ptr<Monstro> p_monstro) { monstro_atual = p_monstro; }

std::shared_ptr<Entidade> GerenciadorJogo::get_inimigo_ativo() const { return monstro_atual; }

int GerenciadorJogo::get_progresso_batalha() const { return progresso_batalha; }
void GerenciadorJogo::set_progresso_batalha(int progresso) { progresso_batalha = progresso; }

void GerenciadorJogo::iniciar_desafio_arena() {
    if (progresso_batalha >= 5) {
        throw CombateException("Arena concluída! O reino está em paz.");
    }
    
    std::string nomeMonstro = "";
    switch(progresso_batalha) {
        case 0: nomeMonstro = "Goblin"; break;
        case 1: nomeMonstro = "Orc Furioso"; break;
        case 2: nomeMonstro = "Lobo Mau"; break;
        case 3: nomeMonstro = "Gigante Malvado"; break;
        case 4: nomeMonstro = "Peppa Pig"; break;
    }
    
    monstro_atual = MonstroFactory::criar_monstro(nomeMonstro);
    
    if (heroi) {
        heroi->recuperar_vida(heroi->get_pontos_vida_max());
        heroi->recuperar_energia(heroi->get_energia_max());
    }
    
    notificar("INICIANDO COMBATE: " + heroi->get_nome() + " VS " + monstro_atual->get_nome() + "!");
}

} // namespace RpgGame
