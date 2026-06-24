#include "../include/Entidade.hpp"

Entidade::Entidade(string p_nome, int p_nivel, float p_vida, float p_energia)
    : nome(p_nome), nivel(p_nivel), vida(p_vida), maxVida(p_vida), energia(p_energia), maxEnergia(p_energia) {}

string Entidade::getNome() const {
    return nome;
}

int Entidade::getNivel() const {
    return nivel;
}

float Entidade::getVida() const {
    return vida;
}

float Entidade::getMaxVida() const {
    return maxVida;
}

void Entidade::recuperarVida(float quantidade) {
    vida += quantidade;
    if (vida > maxVida) {
        vida = maxVida;
    }
}

void Entidade::recuperarEnergia(float quantidade) {
    energia += quantidade;
    if (energia > maxEnergia) {
        energia = maxEnergia;
    }
}

bool Entidade::gastarEnergia(float quantidade) {
    if (energia >= quantidade) {
        energia -= quantidade;
        return true;
    }
    return false;
}

bool Entidade::isVivo() const {
    return vida > 0;
}

void Entidade::exibirStatus() const {
    cout << "[" << nome << " Nv." << nivel << "] | Vida: " << vida << "/" << maxVida 
         << " | Energia: " << energia << "/" << maxEnergia << "\n";
}

bool Entidade::operator==(const Entidade& outra) const {
    return this->nome == outra.nome && this->nivel == outra.nivel;
}

bool Entidade::operator<(const Entidade& outra) const {
    return this->nivel < outra.nivel;
}

