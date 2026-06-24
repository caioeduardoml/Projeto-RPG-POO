#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

using namespace std;

enum class TipoItem {
    Arma,
    Armadura,
    Pocao,
    PocaoEnergia,
    Bomba,
    Especial
};

class Item {
protected:
    string nome;
    string descricao;
    float peso;
    TipoItem tipo;

public:
    Item(string p_nome, string p_descricao, float p_peso, TipoItem p_tipo);
    virtual ~Item() = default;

    string getNome() const;
    string getDescricao() const;
    float getPeso() const;
    TipoItem getTipo() const;

    virtual void usar(class Entidade* usuario, class Entidade* alvo) = 0; // Método polimórfico
};

class Arma : public Item {
private:
    float danoBonus;
public:
    Arma(string p_nome, string p_descricao, float p_peso, float p_danoBonus);
    float getDanoBonus() const;
    void usar(class Entidade* usuario, class Entidade* alvo) override;
};

class Armadura : public Item {
private:
    float defesaBonus;
public:
    Armadura(string p_nome, string p_descricao, float p_peso, float p_defesaBonus);
    float getDefesaBonus() const;
    void usar(class Entidade* usuario, class Entidade* alvo) override;
};

class Pocao : public Item {
private:
    float cura;
public:
    Pocao(string p_nome, string p_descricao, float p_peso, float p_cura);
    float getCura() const;
    void usar(class Entidade* usuario, class Entidade* alvo) override;
};

class PocaoEnergia : public Item {
private:
    float energiaRestaurada;
public:
    PocaoEnergia(string p_nome, string p_descricao, float p_peso, float p_energiaRestaurada);
    float getEnergiaRestaurada() const;
    void usar(class Entidade* usuario, class Entidade* alvo) override;
};

class BombaCaseira : public Item {
private:
    float dano;
public:
    BombaCaseira(string p_nome, string p_descricao, float p_peso, float p_dano);
    float getDano() const;
    void usar(class Entidade* usuario, class Entidade* alvo) override;
};

class ItemEspecial : public Item {
private:
    float bonusStatus;
public:
    ItemEspecial(string p_nome, string p_descricao, float p_peso, float p_bonusStatus);
    float getBonusStatus() const;
    void usar(class Entidade* usuario, class Entidade* alvo) override;
};

#endif // ITEM_HPP
