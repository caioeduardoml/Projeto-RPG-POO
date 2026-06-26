#ifndef CONSTRUTORENERGIA_HPP
#define CONSTRUTORENERGIA_HPP

#include "Personagem.hpp"

namespace RpgGame {

class ConstrutorEnergia : public Personagem {
private:
    int barreira_energia; // Barreira de energia protetora (0 a 100)
public:
    ConstrutorEnergia(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel);
    void subir_nivel() override;
    void receber_dano(int dano) override;

    int get_barreira_energia() const;
    void recarregar_barreira(int quantidade);
};

} // namespace RpgGame

#endif // CONSTRUTORENERGIA_HPP
