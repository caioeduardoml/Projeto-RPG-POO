#ifndef LADRAO_HPP
#define LADRAO_HPP

#include "Personagem.hpp"

class Ladrao : public Personagem {
public:
    Ladrao(string p_nome, Raca* p_raca, int p_nivel);
    void subirNivel() override;
};

#endif // LADRAO_HPP
