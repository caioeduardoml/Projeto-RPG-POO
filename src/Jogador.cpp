#include "../include/Jogador.hpp"
#include <iostream>

Jogador::Jogador(string p_nome, int p_nivel, float p_vida, float p_maxEnergia, float p_defesa) 
    : nome(p_nome), nivel(p_nivel), vida(p_vida), maxVida(p_vida), energia(10.0f), maxEnergia(p_maxEnergia), defesa(p_defesa) {}

string Jogador::getNome() const {
    return nome;
}

float Jogador::getVida() const {
    return vida;
}

float Jogador::getMaxVida() const {
    return maxVida;
}

void Jogador::receberDano(float dano) {
    float danoLiquido = dano - defesa;
    if (danoLiquido < 0) {
        danoLiquido = 0;
    }
    
    vida -= danoLiquido;
    if (vida < 0) vida = 0;
    
    if (danoLiquido > 0) {
        cout << "[" << nome << " recebe " << danoLiquido << " de dano! (Bloqueou " << (dano > defesa ? defesa : dano) << ")]\n";
    } else {
        cout << "[" << nome << " bloqueou todo o dano!]\n";
    }
}

bool Jogador::isVivo() const {
    return vida > 0;
}

void Jogador::recuperarEnergia(float quantidade) {
    energia += quantidade;
    if (energia > maxEnergia) {
        energia = maxEnergia;
    }
}

void Jogador::exibirStatus() const {
    cout << "[" << nome << " Nv." << nivel << "] | Vida: " << vida << "/" << maxVida 
         << " | Energia: " << energia << "/" << maxEnergia 
         << " | Defesa: " << defesa << "\n";
}
