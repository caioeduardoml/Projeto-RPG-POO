#ifndef MONSTRO_HPP
#define MONSTRO_HPP

#include "Entidade.hpp"

class Monstro : public Entidade {
protected:
    float forca;
    float inteligencia;

public:
    Monstro(string p_nome, int p_nivel, float p_vida, float p_forca, float p_inteligencia);
    ~Monstro() override = default;

    float getForca() const;
    float getInteligencia() const;
    
    void receberDano(float dano) override;
    
    virtual float realizarAtaque() const;
};

class Goblin : public Monstro {
public:
    Goblin();
};

class OrcMonstro : public Monstro {
public:
    OrcMonstro();
};

class GiganteMalvado : public Monstro {
public:
    GiganteMalvado();
};

class LoboMau : public Monstro {
public:
    LoboMau();
};

#endif // MONSTRO_HPP
