#ifndef MAGO_HPP
#define MAGO_HPP

#include "Personagem.hpp"

class Mago : public Personagem {
public:
    Mago(string p_nome, Raca* p_raca, int p_nivel);
    void subirNivel() override;
};

#endif // MAGO_HPP
