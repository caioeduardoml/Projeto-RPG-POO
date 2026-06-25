#ifndef CONSTRUTORENERGIA_HPP
#define CONSTRUTORENERGIA_HPP

#include "Personagem.hpp"

namespace RpgGame {

class ConstrutorEnergia : public Personagem {
public:
    ConstrutorEnergia(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel);
    void subir_nivel() override;
};

} // namespace RpgGame

#endif // CONSTRUTORENERGIA_HPP
