#ifndef COMPORTAMENTO_ATAQUE_HPP
#define COMPORTAMENTO_ATAQUE_HPP

#include <string>

namespace RpgGame {

class ComportamentoAtaque {
public:
    virtual ~ComportamentoAtaque() = default;
    virtual std::string get_nome_ataque() const = 0;
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
