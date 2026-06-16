#ifndef DRUIDA_HPP
#define DRUIDA_HPP

#include "Jogador.hpp"

class Druida : public Jogador {
private:
    float sabedoria; 
public:
    Druida(string p_nome, int p_nivel, float p_vida, float p_sabedoria);
    void subirNivel() override;
    void exibirOpcoesAtaque() const override;
    float realizarAtaque(int escolha) override;
};

#endif // DRUIDA_HPP
