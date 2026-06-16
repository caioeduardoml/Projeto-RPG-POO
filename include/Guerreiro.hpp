#ifndef GUERREIRO_HPP
#define GUERREIRO_HPP

#include "Personagem.hpp"

class Guerreiro : public Personagem {
public:
    Guerreiro(string p_nome, Raca* p_raca, int p_nivel);
    void subirNivel() override;
};

#endif // GUERREIRO_HPP
