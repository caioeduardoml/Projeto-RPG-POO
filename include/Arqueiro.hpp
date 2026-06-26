#ifndef ARQUEIRO_HPP
#define ARQUEIRO_HPP

#include "Personagem.hpp"

namespace RpgGame {

class Arqueiro : public Personagem {
private:
    int esquiva; // Chance de esquiva em porcentagem (ex: 15 = 15%)
public:
    Arqueiro(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel);
    void subir_nivel() override;
    void receber_dano(int dano) override;

    int get_esquiva() const;
};

} // namespace RpgGame

#endif // ARQUEIRO_HPP
