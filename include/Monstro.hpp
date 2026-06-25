#ifndef MONSTRO_HPP
#define MONSTRO_HPP

#include "Entidade.hpp"
#include "ComportamentoAtaque.hpp"
#include <memory>

namespace RpgGame {

class Monstro : public Entidade {
protected:
    int forca;
    int inteligencia;
    std::shared_ptr<ComportamentoAtaque> comportamento_ataque; // Strategy Pattern

public:
    Monstro(std::string p_nome, int p_nivel, int p_vida, int p_forca, int p_inteligencia);
    ~Monstro() override = default;

    int get_forca() const;
    int get_inteligencia() const;
    
    void receber_dano(int dano) override;
    
    virtual int realizar_ataque() const;
    void set_comportamento_ataque(std::shared_ptr<ComportamentoAtaque> comp);
};

class Goblin : public Monstro {
public:
    Goblin();
};

class GoblinChefao : public Monstro {
public:
    GoblinChefao();
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

class PeppaPig : public Monstro {
public:
    PeppaPig();
};

} // namespace RpgGame

#endif // MONSTRO_HPP
