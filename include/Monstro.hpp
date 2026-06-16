#ifndef MONSTRO_HPP
#define MONSTRO_HPP

#include "Jogador.hpp"

class Monstro : public Jogador {
protected:
    float forca;         
    float agilidade; 
public:
    Monstro(string p_nome, int p_nivel, float p_vida, float p_forca, float p_agilidade, float p_defesa);
    void subirNivel() override;
    void exibirOpcoesAtaque() const override; 
    float realizarAtaque(int escolha) override; 
};

class Goblin : public Monstro {
public:
    Goblin();
};

class Orc : public Monstro {
public:
    Orc();
};

class Dragao : public Monstro {
public:
    Dragao();
};

#endif // MONSTRO_HPP
