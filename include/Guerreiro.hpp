#ifndef GUERREIRO_HPP
#define GUERREIRO_HPP

#include "Jogador.hpp"

class Guerreiro : public Jogador {
private:
    float forca; 
public:
    Guerreiro(string p_nome, int p_nivel, float p_vida, float p_forca);
    void subirNivel() override;
    void exibirOpcoesAtaque() const override;
    float realizarAtaque(int escolha) override;
};

#endif // GUERREIRO_HPP
