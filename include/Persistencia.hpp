#ifndef PERSISTENCIA_HPP
#define PERSISTENCIA_HPP

#include "Personagem.hpp"
#include <string>

using namespace std;

class Persistencia {
public:
    static bool salvarJogo(Personagem* personagem, const string& arquivo);
    // Para simplificar, o carregarJogo retornaria os dados brutos ou instanciaria
    // mas devido ao acoplamento com subclasses, faremos uma versão simples que
    // só informa que salvou (pois instanciar subclasses dinamicamente requer um Factory)
};

#endif // PERSISTENCIA_HPP
