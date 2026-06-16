#ifndef ARQUEIRO_HPP
#define ARQUEIRO_HPP

#include "Personagem.hpp"

class Arqueiro : public Personagem {
public:
    Arqueiro(string p_nome, Raca* p_raca, int p_nivel);
    void subirNivel() override;
};

#endif // ARQUEIRO_HPP
