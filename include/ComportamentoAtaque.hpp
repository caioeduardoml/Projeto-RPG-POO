#ifndef COMPORTAMENTO_ATAQUE_HPP
#define COMPORTAMENTO_ATAQUE_HPP

#include <string>

namespace RpgGame {

class ComportamentoAtaque {
public:
    virtual ~ComportamentoAtaque() = default;

    /**
     * @brief Retorna o nome do ataque executado.
     */
    virtual std::string get_nome_ataque() const = 0;

    /**
     * @brief Calcula o dano do ataque com base nos atributos do atacante.
     * @param forca Força física do atacante.
     * @param inteligencia Inteligência mágica do atacante.
     * @return Dano total calculado.
     */
    virtual int calcular_dano(int forca, int inteligencia) = 0;
};

class AtaqueFisicoFeroz : public ComportamentoAtaque {
public:
    std::string get_nome_ataque() const override { return "Ataque Físico Feroz"; }
    int calcular_dano(int forca, int /*inteligencia*/) override {
        return static_cast<int>(forca * 1.5f);
    }
};

class AtaqueMagicoArcano : public ComportamentoAtaque {
public:
    std::string get_nome_ataque() const override { return "Ataque Mágico Arcano"; }
    int calcular_dano(int /*forca*/, int inteligencia) override {
        return static_cast<int>(inteligencia * 2.0f);
    }
};

} // namespace RpgGame

#endif // COMPORTAMENTO_ATAQUE_HPP
