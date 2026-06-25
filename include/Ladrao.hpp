#ifndef LADRAO_HPP
#define LADRAO_HPP

#include "Personagem.hpp"

namespace RpgGame {

class Ladrao : public Personagem {
public:
    Ladrao(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel);
    void subir_nivel() override;
};

} // namespace RpgGame

#endif // LADRAO_HPP
