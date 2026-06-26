#ifndef CLERIGO_HPP
#define CLERIGO_HPP

#include "Personagem.hpp"

namespace RpgGame {

class Clerigo : public Personagem {
private:
    int fe_max;
    int fe_atual;
public:
    Clerigo(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel);
    void subir_nivel() override;
    void receber_dano(int dano) override;

    int get_fe_max() const;
    int get_fe_atual() const;
    void recuperar_fe(int quantidade);
};

} // namespace RpgGame

#endif // CLERIGO_HPP
