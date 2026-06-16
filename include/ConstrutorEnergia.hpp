#ifndef CONSTRUTORENERGIA_HPP
#define CONSTRUTORENERGIA_HPP

#include "Jogador.hpp"

class ConstrutorEnergia : public Jogador {
private:
    float criatividade;
public:
    ConstrutorEnergia(string p_nome, int p_nivel, float p_vida, float p_criatividade);
    void subirNivel() override;
    void exibirOpcoesAtaque() const override;
    float realizarAtaque(int escolha) override;
};

#endif // CONSTRUTORENERGIA_HPP
