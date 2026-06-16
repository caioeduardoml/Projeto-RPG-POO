#ifndef MAGO_HPP
#define MAGO_HPP

#include "Jogador.hpp"

class Mago : public Jogador {
private:
    float inteligencia; 
public:
    Mago(string p_nome, int p_nivel, float p_vida, float p_inteligencia);
    void subirNivel() override;
    void exibirOpcoesAtaque() const override;
    float realizarAtaque(int escolha) override;
};

#endif // MAGO_HPP
