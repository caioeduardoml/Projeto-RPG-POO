#include "../include/Entidade.hpp"
#include "../include/Exceptions.hpp"
#include <iostream>

namespace RpgGame {

Entidade::Entidade(std::string p_nome, int p_nivel, int p_vida, int p_energia)
    : nome(p_nome), nivel(p_nivel), pontos_vida_atual(p_vida), pontos_vida_max(p_vida), 
      energia_atual(p_energia), energia_max(p_energia) {}

std::string Entidade::get_nome() const {
    return nome;
}

int Entidade::get_nivel() const {
    return nivel;
}

int Entidade::get_pontos_vida_atual() const {
    return pontos_vida_atual;
}

int Entidade::get_pontos_vida_max() const {
    return pontos_vida_max;
}

int Entidade::get_energia_atual() const {
    return energia_atual;
}

int Entidade::get_energia_max() const {
    return energia_max;
}

void Entidade::recuperar_vida(int quantidade) {
    pontos_vida_atual += quantidade;
    if (pontos_vida_atual > pontos_vida_max) {
        pontos_vida_atual = pontos_vida_max;
    }
}

void Entidade::recuperar_energia(int quantidade) {
    energia_atual += quantidade;
    if (energia_atual > energia_max) {
        energia_atual = energia_max;
    }
}

void Entidade::gastar_energia(int quantidade) {
    if (energia_atual >= quantidade) {
        energia_atual -= quantidade;
        return;
    }
    throw HabilidadeException("Energia insuficiente!");
}

bool Entidade::is_vivo() const {
    return pontos_vida_atual > 0;
}

void Entidade::exibir_status() const {
    std::cout << "[" << nome << " Nv." << nivel << "] | Vida: " << pontos_vida_atual << "/" << pontos_vida_max 
              << " | Energia: " << energia_atual << "/" << energia_max << "\n";
}

bool Entidade::operator==(const Entidade& outra) const {
    return this->nome == outra.nome && this->nivel == outra.nivel;
}

bool Entidade::operator<(const Entidade& outra) const {
    return this->nivel < outra.nivel;
}

} // namespace RpgGame
