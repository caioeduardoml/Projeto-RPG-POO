#ifndef CONSTRUTORENERGIA_HPP
#define CONSTRUTORENERGIA_HPP

#include "Personagem.hpp"

class ConstrutorEnergia : public Personagem {
public:
    ConstrutorEnergia(string p_nome, Raca* p_raca, int p_nivel);
    void subirNivel() override;
};

#endif // CONSTRUTORENERGIA_HPP
