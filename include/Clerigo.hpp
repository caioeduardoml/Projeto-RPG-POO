#ifndef CLERIGO_HPP
#define CLERIGO_HPP

#include "Personagem.hpp"

class Clerigo : public Personagem {
public:
    Clerigo(string p_nome, Raca* p_raca, int p_nivel);
    void subirNivel() override;
};

#endif // CLERIGO_HPP
