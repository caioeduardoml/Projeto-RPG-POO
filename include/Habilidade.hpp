#ifndef HABILIDADE_HPP
#define HABILIDADE_HPP

#include <string>

namespace RpgGame {

class Entidade; // Forward declaration

class Habilidade {
protected:
    std::string nome;
    std::string descricao;
    int custo_energia;

public:
    Habilidade(std::string p_nome, std::string p_descricao, int p_custo_energia);
    virtual ~Habilidade() = default;

    std::string get_nome() const;
    std::string get_descricao() const;
    int get_custo_energia() const;
    virtual std::string get_efeito_str() const { return ""; }

    virtual void usar(Entidade* usuario, Entidade* alvo) = 0;
};

class HabilidadeOfensiva : public Habilidade {
private:
    int dano_base;
public:
    HabilidadeOfensiva(std::string p_nome, std::string p_descricao, int p_custo_energia, int p_dano_base);
    void usar(Entidade* usuario, Entidade* alvo) override;
    std::string get_efeito_str() const override;
};

class HabilidadeDefensiva : public Habilidade {
private:
    int aumento_defesa;
public:
    HabilidadeDefensiva(std::string p_nome, std::string p_descricao, int p_custo_energia, int p_aumento_defesa);
    void usar(Entidade* usuario, Entidade* alvo) override;
    std::string get_efeito_str() const override;
};

class HabilidadeSuporte : public Habilidade {
private:
    int cura_base;
public:
    HabilidadeSuporte(std::string p_nome, std::string p_descricao, int p_custo_energia, int p_cura_base);
    void usar(Entidade* usuario, Entidade* alvo) override;
    std::string get_efeito_str() const override;
};

} // namespace RpgGame

#endif // HABILIDADE_HPP
