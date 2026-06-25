#ifndef DRUIDA_HPP
#define DRUIDA_HPP

#include "Personagem.hpp"

namespace RpgGame {

class Druida : public Personagem {
public:
    Druida(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel);
    void subir_nivel() override;
};

} // namespace RpgGame

#endif // DRUIDA_HPP
