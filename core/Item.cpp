#include "../include/Item.hpp"
#include "../include/Entidade.hpp"
#include "../include/Personagem.hpp"
#include <iostream>

// --- Item ---
Item::Item(string p_nome, string p_descricao, float p_peso, TipoItem p_tipo)
    : nome(p_nome), descricao(p_descricao), peso(p_peso), tipo(p_tipo) {}

string Item::getNome() const { return nome; }
string Item::getDescricao() const { return descricao; }
float Item::getPeso() const { return peso; }
TipoItem Item::getTipo() const { return tipo; }

// --- Arma ---
Arma::Arma(string p_nome, string p_descricao, float p_peso, float p_danoBonus)
    : Item(p_nome, p_descricao, p_peso, TipoItem::Arma), danoBonus(p_danoBonus) {}

float Arma::getDanoBonus() const { return danoBonus; }

void Arma::usar(Entidade* usuario, Entidade* /*alvo*/) {
    Personagem* p = dynamic_cast<Personagem*>(usuario);
    if (p) {
        p->equiparArma(this);
    } else {
        cout << usuario->getNome() << " equipou a arma " << nome << " (+ " << danoBonus << " Dano)\n";
    }
}

// --- Armadura ---
Armadura::Armadura(string p_nome, string p_descricao, float p_peso, float p_defesaBonus)
    : Item(p_nome, p_descricao, p_peso, TipoItem::Armadura), defesaBonus(p_defesaBonus) {}

float Armadura::getDefesaBonus() const { return defesaBonus; }

void Armadura::usar(Entidade* usuario, Entidade* /*alvo*/) {
    Personagem* p = dynamic_cast<Personagem*>(usuario);
    if (p) {
        p->equiparArmadura(this);
    } else {
        cout << usuario->getNome() << " equipou a armadura " << nome << " (+ " << defesaBonus << " Defesa)\n";
    }
}

// --- Pocao ---
Pocao::Pocao(string p_nome, string p_descricao, float p_peso, float p_cura)
    : Item(p_nome, p_descricao, p_peso, TipoItem::Pocao), cura(p_cura) {}

float Pocao::getCura() const { return cura; }

void Pocao::usar(Entidade* usuario, Entidade* /*alvo*/) {
    cout << usuario->getNome() << " bebeu " << nome << "!\n";
    usuario->recuperarVida(cura);
    cout << "+ " << cura << " Vida recuperada!\n";
}

// --- Pocao Energia ---
PocaoEnergia::PocaoEnergia(string p_nome, string p_descricao, float p_peso, float p_energiaRestaurada)
    : Item(p_nome, p_descricao, p_peso, TipoItem::PocaoEnergia), energiaRestaurada(p_energiaRestaurada) {}

float PocaoEnergia::getEnergiaRestaurada() const { return energiaRestaurada; }

void PocaoEnergia::usar(Entidade* usuario, Entidade* /*alvo*/) {
    cout << usuario->getNome() << " bebeu " << nome << "!\n";
    usuario->recuperarEnergia(energiaRestaurada);
    cout << "+ " << energiaRestaurada << " Energia recuperada!\n";
}

// --- Bomba Caseira ---
BombaCaseira::BombaCaseira(string p_nome, string p_descricao, float p_peso, float p_dano)
    : Item(p_nome, p_descricao, p_peso, TipoItem::Bomba), dano(p_dano) {}

float BombaCaseira::getDano() const { return dano; }

void BombaCaseira::usar(Entidade* usuario, Entidade* alvo) {
    cout << usuario->getNome() << " arremessou " << nome << " em " << alvo->getNome() << "!\n";
    alvo->receberDano(dano);
}

// --- Item Especial ---
ItemEspecial::ItemEspecial(string p_nome, string p_descricao, float p_peso, float p_bonusStatus)
    : Item(p_nome, p_descricao, p_peso, TipoItem::Especial), bonusStatus(p_bonusStatus) {}

float ItemEspecial::getBonusStatus() const { return bonusStatus; }

void ItemEspecial::usar(Entidade* usuario, Entidade* /*alvo*/) {
    cout << usuario->getNome() << " ativou o " << nome << "!\n";
    usuario->recuperarEnergia(bonusStatus);
    cout << "+ " << bonusStatus << " de Energia restaurada pelo item especial!\n";
}

