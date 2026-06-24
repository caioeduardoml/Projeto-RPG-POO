#include "../include/Raca.hpp"

Raca::Raca(string p_nomeRaca, float p_bonusVida, float p_bonusForca, float p_bonusInteligencia)
    : nomeRaca(p_nomeRaca), bonusVida(p_bonusVida), bonusForca(p_bonusForca), bonusInteligencia(p_bonusInteligencia) {}

string Raca::getNomeRaca() const { return nomeRaca; }
float Raca::getBonusVida() const { return bonusVida; }
float Raca::getBonusForca() const { return bonusForca; }
float Raca::getBonusInteligencia() const { return bonusInteligencia; }

Humano::Humano() : Raca("Humano", 10.0f, 5.0f, 5.0f) {}
Elfo::Elfo() : Raca("Elfo", -5.0f, 2.0f, 10.0f) {}
Anao::Anao() : Raca("Anão", 20.0f, 10.0f, -5.0f) {}
Orc::Orc() : Raca("Orc", 15.0f, 15.0f, -10.0f) {}
Dragao::Dragao() : Raca("Dragao", 30.0f, 30.0f, -10.0f) {}

