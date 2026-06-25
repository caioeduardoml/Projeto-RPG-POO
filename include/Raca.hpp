#ifndef RACA_HPP
#define RACA_HPP

#include <string>

namespace RpgGame {

class Raca {
protected:
    std::string nomeRaca;
    int bonusVida;
    int bonusForca;
    int bonusInteligencia;

public:
    Raca(std::string p_nomeRaca, int p_bonusVida, int p_bonusForca, int p_bonusInteligencia);
    virtual ~Raca() = default;

    std::string get_nome_raca() const;
    int get_bonus_vida() const;
    int get_bonus_forca() const;
    int get_bonus_inteligencia() const;
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

} // namespace RpgGame

#endif // RACA_HPP
