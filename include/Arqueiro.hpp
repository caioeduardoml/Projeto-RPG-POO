#ifndef ARQUEIRO_HPP
#define ARQUEIRO_HPP

#include "Jogador.hpp"

class Arqueiro : public Jogador {
private:
    float destreza;         
    float agilidade; 
public:
    Arqueiro(string p_nome, int p_nivel, float p_vida, float p_destreza, float p_agilidade);
    void subirNivel() override;
    void exibirOpcoesAtaque() const override;
    float realizarAtaque(int escolha) override;
};

#endif // ARQUEIRO_HPP
