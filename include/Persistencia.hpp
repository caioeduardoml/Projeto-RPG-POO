#ifndef PERSISTENCIA_HPP
#define PERSISTENCIA_HPP

#include "Personagem.hpp"
#include <string>

using namespace std;

class Persistencia {
public:
    static bool salvarJogo(Personagem* personagem, const string& arquivo);
    static Personagem* carregarJogo(const string& arquivo);
};

#endif // PERSISTENCIA_HPP
