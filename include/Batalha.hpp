#ifndef BATALHA_HPP
#define BATALHA_HPP

#include "Personagem.hpp"
#include "Monstro.hpp"
#include <memory>

namespace RpgGame {

class Batalha {
private:
    std::shared_ptr<Personagem> heroi;
    std::shared_ptr<Monstro> monstro;

public:
    Batalha(std::shared_ptr<Personagem> p_heroi, std::shared_ptr<Monstro> p_monstro);
    
    // Gera um item de drop aleatorio usando gerador Mersenne Twister (C++17)
    [[nodiscard]] static std::shared_ptr<Item> gerar_drop_aleatorio();

    // Executa a batalha e retorna true se o herói venceu
    bool iniciar();
};

} // namespace RpgGame

#endif // BATALHA_HPP
