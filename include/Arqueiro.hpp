#ifndef ARQUEIRO_HPP
#define ARQUEIRO_HPP

#include "Personagem.hpp"

namespace RpgGame {

class Arqueiro : public Personagem {
public:
    Arqueiro(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel);
    void subir_nivel() override;
};

} // namespace RpgGame

#endif // ARQUEIRO_HPP
