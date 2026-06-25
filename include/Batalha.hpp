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

    std::shared_ptr<Item> gerar_drop_aleatorio();

public:
    Batalha(std::shared_ptr<Personagem> p_heroi, std::shared_ptr<Monstro> p_monstro);
    
    // Executa a batalha e retorna true se o herói venceu
    bool iniciar();
};

} // namespace RpgGame

#endif // BATALHA_HPP
