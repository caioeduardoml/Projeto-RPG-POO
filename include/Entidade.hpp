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
    /**
     * @brief Construtor padrão da classe Entidade.
     * @param p_nome Nome da entidade.
     * @param p_nivel Nível inicial.
     * @param p_vida Pontos de vida base.
     * @param p_energia Energia inicial (padrão 50).
     */
    Entidade(std::string p_nome, int p_nivel, int p_vida, int p_energia = 50);
    virtual ~Entidade() = default;

    std::string get_nome() const;
    int get_nivel() const;
    int get_pontos_vida_atual() const;
    int get_pontos_vida_max() const;
    int get_energia_atual() const;
    int get_energia_max() const;

    /**
     * @brief Aplica dano à entidade. Deve ser implementado pelas subclasses.
     * @param dano Valor bruto de dano a ser recebido.
     */
    virtual void receber_dano(int dano) = 0;

    /**
     * @brief Recupera uma quantidade específica de vida.
     */
    virtual void recuperar_vida(int quantidade);

    /**
     * @brief Recupera uma quantidade específica de energia.
     */
    virtual void recuperar_energia(int quantidade);

    /**
     * @brief Gasta energia da entidade. Lança exceção se não houver suficiente.
     * @throws HabilidadeException Se energia for insuficiente.
     */
    virtual void gastar_energia(int quantidade);

    /**
     * @brief Verifica se a entidade continua viva (vida > 0).
     */
    bool is_vivo() const;

    virtual void exibir_status() const;

    bool operator==(const Entidade& outra) const;
    bool operator<(const Entidade& outra) const;
};

} // namespace RpgGame

#endif // ENTIDADE_HPP
