#ifndef HABILIDADE_HPP
#define HABILIDADE_HPP

#include <string>

using namespace std;

class Entidade; // Forward declaration

class Habilidade {
protected:
    string nome;
    string descricao;
    float custoEnergia;

public:
    Habilidade(string p_nome, string p_descricao, float p_custoEnergia);
    virtual ~Habilidade() = default;

    string getNome() const;
    string getDescricao() const;
    float getCustoEnergia() const;

    virtual void usar(Entidade* usuario, Entidade* alvo) = 0;
};

class HabilidadeOfensiva : public Habilidade {
private:
    float danoBase;
public:
    HabilidadeOfensiva(string p_nome, string p_descricao, float p_custoEnergia, float p_danoBase);
    void usar(Entidade* usuario, Entidade* alvo) override;
};

class HabilidadeDefensiva : public Habilidade {
private:
    float aumentoDefesa;
public:
    HabilidadeDefensiva(string p_nome, string p_descricao, float p_custoEnergia, float p_aumentoDefesa);
    void usar(Entidade* usuario, Entidade* alvo) override;
};

class HabilidadeSuporte : public Habilidade {
private:
    float curaBase;
public:
    HabilidadeSuporte(string p_nome, string p_descricao, float p_custoEnergia, float p_curaBase);
    void usar(Entidade* usuario, Entidade* alvo) override;
};

#endif // HABILIDADE_HPP
