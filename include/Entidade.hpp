#ifndef ENTIDADE_HPP
#define ENTIDADE_HPP

#include <string>
#include <iostream>

namespace RpgGame {

class Entidade {
protected:
    std::string nome;
    int nivel;
    int pontos_vida_atual;
    int pontos_vida_max;
    int energia_atual;
    int energia_max;

public:
    Entidade(std::string p_nome, int p_nivel, int p_vida, int p_energia = 50);
    virtual ~Entidade() = default;

    std::string get_nome() const;
    int get_nivel() const;
    int get_pontos_vida_atual() const;
    int get_pontos_vida_max() const;
    int get_energia_atual() const;
    int get_energia_max() const;

    virtual void receber_dano(int dano) = 0;
    virtual void recuperar_vida(int quantidade);
    virtual void recuperar_energia(int quantidade);
    virtual void gastar_energia(int quantidade);
    bool is_vivo() const;

    virtual void exibir_status() const;

    bool operator==(const Entidade& outra) const;
    bool operator<(const Entidade& outra) const;
};

} // namespace RpgGame

#endif // ENTIDADE_HPP
