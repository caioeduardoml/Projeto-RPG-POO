#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <memory>

namespace RpgGame {

enum class TipoItem {
    Arma,
    Armadura,
    Pocao,
    PocaoEnergia,
    Bomba,
    Especial
};

class Personagem; // Forward declaration

class Item : public std::enable_shared_from_this<Item> {
protected:
    std::string nome;
    std::string descricao;
    double peso;
    int valor_moedas;
    TipoItem tipo;

public:
    /**
     * @brief Construtor padrão da classe Item.
     * @param p_nome Nome do item.
     * @param p_descricao Descrição textual.
     * @param p_peso Peso em Kg.
     * @param p_valor_moedas Valor de compra/venda.
     * @param p_tipo Tipo enumerado (Arma, Poção, etc).
     */
    Item(std::string p_nome, std::string p_descricao, double p_peso, int p_valor_moedas, TipoItem p_tipo);
    virtual ~Item() = default;

    std::string get_nome() const;
    std::string get_descricao() const;
    double get_peso() const;
    int get_valor_moedas() const;
    TipoItem get_tipo() const;

    /**
     * @brief Método virtual puro que aplica os efeitos do item no personagem.
     * @param usuario Personagem que utilizará o item.
     */
    virtual void usar(Personagem& usuario) = 0;
};

class Arma : public Item {
private:
    int danoBonus;
public:
    Arma(std::string p_nome, std::string p_descricao, double p_peso, int p_valor_moedas, int p_danoBonus);
    int get_dano_bonus() const;
    void usar(Personagem& usuario) override;
};

class Armadura : public Item {
private:
    int defesaBonus;
public:
    Armadura(std::string p_nome, std::string p_descricao, double p_peso, int p_valor_moedas, int p_defesaBonus);
    int get_defesa_bonus() const;
    void usar(Personagem& usuario) override;
};

class Pocao : public Item {
private:
    int cura;
public:
    Pocao(std::string p_nome, std::string p_descricao, double p_peso, int p_valor_moedas, int p_cura);
    int get_cura() const;
    void usar(Personagem& usuario) override;
};

class PocaoEnergia : public Item {
private:
    int energiaRestaurada;
public:
    PocaoEnergia(std::string p_nome, std::string p_descricao, double p_peso, int p_valor_moedas, int p_energiaRestaurada);
    int get_energia_restaurada() const;
    void usar(Personagem& usuario) override;
};

class BombaCaseira : public Item {
private:
    int dano;
public:
    BombaCaseira(std::string p_nome, std::string p_descricao, double p_peso, int p_valor_moedas, int p_dano);
    int get_dano() const;
    void usar(Personagem& usuario) override;
};

class ItemEspecial : public Item {
private:
    int bonusStatus;
public:
    ItemEspecial(std::string p_nome, std::string p_descricao, double p_peso, int p_valor_moedas, int p_bonusStatus);
    int get_bonus_status() const;
    void usar(Personagem& usuario) override;
};

} // namespace RpgGame

#endif // ITEM_HPP
