#ifndef DRUIDA_HPP
#define DRUIDA_HPP

#include "Personagem.hpp"

namespace RpgGame {

class Druida : public Personagem {
private:
    int comunhao; // Comunhão com a natureza (0 a 100)
public:
    Druida(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel);
    void subir_nivel() override;
    void receber_dano(int dano) override;

    int get_comunhao() const;
};

} // namespace RpgGame

#endif // DRUIDA_HPP
