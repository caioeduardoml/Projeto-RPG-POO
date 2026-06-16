#ifndef DRUIDA_HPP
#define DRUIDA_HPP

#include "Personagem.hpp"

class Druida : public Personagem {
public:
    Druida(string p_nome, Raca* p_raca, int p_nivel);
    void subirNivel() override;
};

#endif // DRUIDA_HPP
