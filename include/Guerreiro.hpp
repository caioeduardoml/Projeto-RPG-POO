#ifndef GUERREIRO_HPP
#define GUERREIRO_HPP

#include "Personagem.hpp"

namespace RpgGame {

class Guerreiro : public Personagem {
private:
    int furia; // as required by PDF page 4
public:
    Guerreiro(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel);
    void subir_nivel() override;
    void receber_dano(int dano) override; // specialized method as required by PDF page 4

    int get_furia() const;
};

} // namespace RpgGame

#endif // GUERREIRO_HPP
