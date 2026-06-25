#include "../include/Item.hpp"
#include "../include/Personagem.hpp"
#include "../include/GerenciadorJogo.hpp"
#include <iostream>

namespace RpgGame {

// --- Item ---
Item::Item(std::string p_nome, std::string p_descricao, double p_peso, int p_valor_moedas, TipoItem p_tipo)
    : nome(p_nome), descricao(p_descricao), peso(p_peso), valor_moedas(p_valor_moedas), tipo(p_tipo) {}

std::string Item::get_nome() const { return nome; }
std::string Item::get_descricao() const { return descricao; }
double Item::get_peso() const { return peso; }
int Item::get_valor_moedas() const { return valor_moedas; }
TipoItem Item::get_tipo() const { return tipo; }

// --- Arma ---
Arma::Arma(std::string p_nome, std::string p_descricao, double p_peso, int p_valor_moedas, int p_danoBonus)
    : Item(p_nome, p_descricao, p_peso, p_valor_moedas, TipoItem::Arma), danoBonus(p_danoBonus) {}

int Arma::get_dano_bonus() const { return danoBonus; }

void Arma::usar(Personagem& usuario) {
    usuario.equipar_item(shared_from_this());
}

// --- Armadura ---
Armadura::Armadura(std::string p_nome, std::string p_descricao, double p_peso, int p_valor_moedas, int p_defesaBonus)
    : Item(p_nome, p_descricao, p_peso, p_valor_moedas, TipoItem::Armadura), defesaBonus(p_defesaBonus) {}

int Armadura::get_defesa_bonus() const { return defesaBonus; }

void Armadura::usar(Personagem& usuario) {
    usuario.equipar_item(shared_from_this());
}

// --- Pocao ---
Pocao::Pocao(std::string p_nome, std::string p_descricao, double p_peso, int p_valor_moedas, int p_cura)
    : Item(p_nome, p_descricao, p_peso, p_valor_moedas, TipoItem::Pocao), cura(p_cura) {}

int Pocao::get_cura() const { return cura; }

void Pocao::usar(Personagem& usuario) {
    usuario.recuperar_vida(cura);
}

// --- Pocao Energia ---
PocaoEnergia::PocaoEnergia(std::string p_nome, std::string p_descricao, double p_peso, int p_valor_moedas, int p_energiaRestaurada)
    : Item(p_nome, p_descricao, p_peso, p_valor_moedas, TipoItem::PocaoEnergia), energiaRestaurada(p_energiaRestaurada) {}

int PocaoEnergia::get_energia_restaurada() const { return energiaRestaurada; }

void PocaoEnergia::usar(Personagem& usuario) {
    usuario.recuperar_energia(energiaRestaurada);
}

// --- Bomba Caseira ---
BombaCaseira::BombaCaseira(std::string p_nome, std::string p_descricao, double p_peso, int p_valor_moedas, int p_dano)
    : Item(p_nome, p_descricao, p_peso, p_valor_moedas, TipoItem::Bomba), dano(p_dano) {}

int BombaCaseira::get_dano() const { return dano; }

void BombaCaseira::usar(Personagem& usuario) {
    // Acessa o inimigo ativo através do Singleton GerenciadorJogo
    auto inimigo = GerenciadorJogo::get_instancia().get_inimigo_ativo();
    if (inimigo) {
        inimigo->receber_dano(dano);
        GerenciadorJogo::get_instancia().notificar(
            usuario.get_nome() + " arremessou " + nome + " em " + inimigo->get_nome() + 
            " causando " + std::to_string(dano) + " de dano!"
        );
    } else {
        std::cout << "Nenhum alvo ativo para usar a bomba!\n";
    }
}

// --- Item Especial ---
ItemEspecial::ItemEspecial(std::string p_nome, std::string p_descricao, double p_peso, int p_valor_moedas, int p_bonusStatus)
    : Item(p_nome, p_descricao, p_peso, p_valor_moedas, TipoItem::Especial), bonusStatus(p_bonusStatus) {}

int ItemEspecial::get_bonus_status() const { return bonusStatus; }

void ItemEspecial::usar(Personagem& usuario) {
    usuario.recuperar_energia(bonusStatus);
}

} // namespace RpgGame
