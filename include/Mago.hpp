#ifndef MAGO_HPP
#define MAGO_HPP

#include "Personagem.hpp"

namespace RpgGame {

class Mago : public Personagem {
private:
    int mana_max; // as required by PDF page 4
    int mana_atual; // as required by PDF page 4
public:
    Mago(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel);
    void subir_nivel() override;
    void receber_dano(int dano) override; // specialized method as required by PDF page 4

    int get_mana_max() const;
    int get_mana_atual() const;
    void recuperar_mana(int quantidade);
};

} // namespace RpgGame

#endif // MAGO_HPP
