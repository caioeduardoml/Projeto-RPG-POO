#ifndef BATALHA_HPP
#define BATALHA_HPP

#include "Personagem.hpp"
#include "Monstro.hpp"

class Batalha {
private:
    Personagem* heroi;
    Monstro* monstro;

    class Item* gerarDropAleatorio();

public:
    Batalha(Personagem* p_heroi, Monstro* p_monstro);
    
    // Executa a batalha e retorna true se o herói venceu
    bool iniciar();
};

#endif // BATALHA_HPP
