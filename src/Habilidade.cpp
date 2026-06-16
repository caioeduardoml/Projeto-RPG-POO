#include "../include/Habilidade.hpp"
#include "../include/Entidade.hpp"
#include <iostream>

// --- Habilidade ---
Habilidade::Habilidade(string p_nome, string p_descricao, float p_custoEnergia)
    : nome(p_nome), descricao(p_descricao), custoEnergia(p_custoEnergia) {}

string Habilidade::getNome() const { return nome; }
string Habilidade::getDescricao() const { return descricao; }
float Habilidade::getCustoEnergia() const { return custoEnergia; }

// --- Habilidade Ofensiva ---
HabilidadeOfensiva::HabilidadeOfensiva(string p_nome, string p_descricao, float p_custoEnergia, float p_danoBase)
    : Habilidade(p_nome, p_descricao, p_custoEnergia), danoBase(p_danoBase) {}

void HabilidadeOfensiva::usar(Entidade* usuario, Entidade* alvo) {
    cout << usuario->getNome() << " usa " << nome << " em " << alvo->getNome() << "!\n";
    alvo->receberDano(danoBase); // Em um sistema completo, somaria com atributos do usuário
}

// --- Habilidade Defensiva ---
HabilidadeDefensiva::HabilidadeDefensiva(string p_nome, string p_descricao, float p_custoEnergia, float p_aumentoDefesa)
    : Habilidade(p_nome, p_descricao, p_custoEnergia), aumentoDefesa(p_aumentoDefesa) {}

void HabilidadeDefensiva::usar(Entidade* usuario, Entidade* /*alvo*/) {
    // Para simplificar, curamos a vida do usuário ou aplicamos um buff.
    // Como Entidade base não tem método de adicionar defesa temporária, vamos imprimir.
    cout << usuario->getNome() << " usa " << nome << " e aumenta sua defesa! (Apenas cosmético nesta versão)\n";
}

// --- Habilidade Suporte ---
HabilidadeSuporte::HabilidadeSuporte(string p_nome, string p_descricao, float p_custoEnergia, float p_curaBase)
    : Habilidade(p_nome, p_descricao, p_custoEnergia), curaBase(p_curaBase) {}

void HabilidadeSuporte::usar(Entidade* usuario, Entidade* alvo) {
    cout << usuario->getNome() << " usa " << nome << " em " << alvo->getNome() << "!\n";
    alvo->recuperarVida(curaBase);
    cout << alvo->getNome() << " recuperou " << curaBase << " pontos de vida.\n";
}
