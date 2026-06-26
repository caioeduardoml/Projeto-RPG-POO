#ifndef LADRAO_HPP
#define LADRAO_HPP

#include "Personagem.hpp"

namespace RpgGame {

class Ladrao : public Personagem {
private:
    int furtividade; // Furtividade (0 a 100)
public:
    Ladrao(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel);
    void subir_nivel() override;
    void receber_dano(int dano) override;

    int get_furtividade() const;
    void recuperar_furtividade(int quantidade);
};

} // namespace RpgGame

#endif // LADRAO_HPP
