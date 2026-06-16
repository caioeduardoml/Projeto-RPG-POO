#ifndef RACA_HPP
#define RACA_HPP

#include <string>

using namespace std;

class Raca {
protected:
    string nomeRaca;
    float bonusVida;
    float bonusForca;
    float bonusInteligencia;

public:
    Raca(string p_nomeRaca, float p_bonusVida, float p_bonusForca, float p_bonusInteligencia);
    virtual ~Raca() = default;

    string getNomeRaca() const;
    float getBonusVida() const;
    float getBonusForca() const;
    float getBonusInteligencia() const;
};

class Humano : public Raca {
public:
    Humano();
};

class Elfo : public Raca {
public:
    Elfo();
};

class Anao : public Raca {
public:
    Anao();
};

class Orc : public Raca {
public:
    Orc();
};

class Dragao : public Raca {
public:
    Dragao();
};

#endif // RACA_HPP
