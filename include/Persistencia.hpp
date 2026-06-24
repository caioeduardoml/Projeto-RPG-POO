#ifndef PERSISTENCIA_HPP
#define PERSISTENCIA_HPP

#include "Personagem.hpp"
#include <string>

using namespace std;

class Persistencia {
public:
    static bool salvarJogo(Personagem* personagem, const string& arquivo, int progressoBatalha = 0);
    static Personagem* carregarJogo(const string& arquivo, int& progressoBatalha);
};

#endif // PERSISTENCIA_HPP
