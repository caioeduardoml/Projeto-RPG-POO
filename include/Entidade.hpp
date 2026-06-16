#ifndef ENTIDADE_HPP
#define ENTIDADE_HPP

#include <string>
#include <iostream>

using namespace std;

class Entidade {
protected:
    string nome;
    int nivel;
    float vida;
    float maxVida;
    float energia;
    float maxEnergia;

public:
    Entidade(string p_nome, int p_nivel, float p_vida, float p_energia = 50.0f);
    virtual ~Entidade() = default;

    string getNome() const;
    int getNivel() const;
    float getVida() const;
    float getMaxVida() const;

    virtual void receberDano(float dano) = 0;
    virtual void recuperarVida(float quantidade);
    virtual void recuperarEnergia(float quantidade);
    virtual bool gastarEnergia(float quantidade);
    bool isVivo() const;

    virtual void exibirStatus() const;
};

#endif // ENTIDADE_HPP
