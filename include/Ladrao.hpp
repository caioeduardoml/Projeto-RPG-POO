#ifndef LADRAO_HPP
#define LADRAO_HPP

#include "Jogador.hpp"

class Ladrao : public Jogador {
private:
    float agilidade;      
    float chance_critico; 
public:
    Ladrao(string p_nome, int p_nivel, float p_vida, float p_agilidade, float p_chance_critico);
    void subirNivel() override;
    void exibirOpcoesAtaque() const override;
    float realizarAtaque(int escolha) override;
};

#endif // LADRAO_HPP
