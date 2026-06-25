#include "../include/Raca.hpp"

namespace RpgGame {

Raca::Raca(std::string p_nomeRaca, int p_bonusVida, int p_bonusForca, int p_bonusInteligencia)
    : nomeRaca(p_nomeRaca), bonusVida(p_bonusVida), bonusForca(p_bonusForca), bonusInteligencia(p_bonusInteligencia) {}

std::string Raca::get_nome_raca() const { return nomeRaca; }
int Raca::get_bonus_vida() const { return bonusVida; }
int Raca::get_bonus_forca() const { return bonusForca; }
int Raca::get_bonus_inteligencia() const { return bonusInteligencia; }

Humano::Humano() : Raca("Humano", 10, 5, 5) {}
Elfo::Elfo() : Raca("Elfo", -5, 2, 10) {}
Anao::Anao() : Raca("Anão", 20, 10, -5) {}
Orc::Orc() : Raca("Orc", 15, 15, -10) {}
Dragao::Dragao() : Raca("Dragão", 30, 30, -10) {}

} // namespace RpgGame
