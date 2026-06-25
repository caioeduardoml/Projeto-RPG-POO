#ifndef CLERIGO_HPP
#define CLERIGO_HPP

#include "Personagem.hpp"

namespace RpgGame {

class Clerigo : public Personagem {
public:
    Clerigo(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel);
    void subir_nivel() override;
};

} // namespace RpgGame

#endif // CLERIGO_HPP
