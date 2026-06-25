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
    float getEnergia() const;
    float getMaxEnergia() const;

    virtual void receberDano(float dano) = 0;
    virtual void recuperarVida(float quantidade);
    virtual void recuperarEnergia(float quantidade);
    /**
     * @brief Tenta gastar energia da entidade.
     * @param quantidade A quantidade a gastar.
     * @throws HabilidadeException Se a entidade não tiver energia suficiente.
     */
    virtual void gastarEnergia(float quantidade);
    bool isVivo() const;

    virtual void exibirStatus() const;

    bool operator==(const Entidade& outra) const;
    bool operator<(const Entidade& outra) const;
};

#endif // ENTIDADE_HPP
