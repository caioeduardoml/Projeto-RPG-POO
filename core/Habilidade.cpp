#include "../include/Habilidade.hpp"
#include "../include/Entidade.hpp"
#include "../include/Personagem.hpp"
#include "../include/GerenciadorJogo.hpp"
#include <iostream>

namespace RpgGame {

// --- Habilidade ---
Habilidade::Habilidade(std::string p_nome, std::string p_descricao, int p_custo_energia)
    : nome(p_nome), descricao(p_descricao), custo_energia(p_custo_energia) {}

std::string Habilidade::get_nome() const { return nome; }
std::string Habilidade::get_descricao() const { return descricao; }
int Habilidade::get_custo_energia() const { return custo_energia; }

// --- Habilidade Ofensiva ---
HabilidadeOfensiva::HabilidadeOfensiva(std::string p_nome, std::string p_descricao, int p_custo_energia, int p_dano_base)
    : Habilidade(p_nome, p_descricao, p_custo_energia), dano_base(p_dano_base) {}

void HabilidadeOfensiva::usar(Entidade* usuario, Entidade* alvo) {
    if (!usuario || !alvo) return;
    int danoFinal = dano_base;
    Personagem* p = dynamic_cast<Personagem*>(usuario);
    if (p) {
        danoFinal += p->get_dano_total();
    }
    
    std::string msg = usuario->get_nome() + " usa " + nome + " em " + alvo->get_nome() + "!";
    GerenciadorJogo::get_instancia().notificar(msg);
    
    alvo->receber_dano(danoFinal);
}

std::string HabilidadeOfensiva::get_efeito_str() const {
    return "(Dano: " + std::to_string(dano_base) + ")";
}

// --- Habilidade Defensiva ---
HabilidadeDefensiva::HabilidadeDefensiva(std::string p_nome, std::string p_descricao, int p_custo_energia, int p_aumento_defesa)
    : Habilidade(p_nome, p_descricao, p_custo_energia), aumento_defesa(p_aumento_defesa) {}

void HabilidadeDefensiva::usar(Entidade* usuario, Entidade* /*alvo*/) {
    if (!usuario) return;
    // Como Entidade base não tem método de adicionar defesa temporária, apenas notificamos a ação.
    std::string msg = usuario->get_nome() + " usa " + nome + " e aumenta sua defesa em " + 
                      std::to_string(aumento_defesa) + "! (Cosmético)";
    GerenciadorJogo::get_instancia().notificar(msg);
}

std::string HabilidadeDefensiva::get_efeito_str() const {
    return "(Defesa: " + std::to_string(aumento_defesa) + ")";
}

// --- Habilidade Suporte ---
HabilidadeSuporte::HabilidadeSuporte(std::string p_nome, std::string p_descricao, int p_custo_energia, int p_cura_base)
    : Habilidade(p_nome, p_descricao, p_custo_energia), cura_base(p_cura_base) {}

void HabilidadeSuporte::usar(Entidade* usuario, Entidade* /*alvo*/) {
    if (!usuario) return;
    
    std::string msg = usuario->get_nome() + " usa " + nome + "!";
    GerenciadorJogo::get_instancia().notificar(msg);
    
    if (nome == "Clareza Mental" || nome == "Bateria Infinita" || descricao.find("energia") != std::string::npos || descricao.find("Energia") != std::string::npos) {
        usuario->recuperar_energia(cura_base);
        GerenciadorJogo::get_instancia().notificar(
            usuario->get_nome() + " recuperou " + std::to_string(cura_base) + " pontos de energia."
        );
    } else {
        usuario->recuperar_vida(cura_base);
        GerenciadorJogo::get_instancia().notificar(
            usuario->get_nome() + " recuperou " + std::to_string(cura_base) + " pontos de vida."
        );
    }
}

std::string HabilidadeSuporte::get_efeito_str() const {
    if (nome == "Clareza Mental" || nome == "Bateria Infinita" || descricao.find("energia") != std::string::npos || descricao.find("Energia") != std::string::npos) {
        return "(Energia: " + std::to_string(cura_base) + ")";
    }
    return "(Cura: " + std::to_string(cura_base) + ")";
}

} // namespace RpgGame
