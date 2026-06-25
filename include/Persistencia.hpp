#ifndef PERSISTENCIA_HPP
#define PERSISTENCIA_HPP

#include "Personagem.hpp"
#include <string>

using namespace std;

class Persistencia {
public:
    /**
     * @brief Salva o estado atual do jogo.
     * @throws PersistenciaException Em caso de erro na abertura ou gravação do arquivo.
     */
    static void salvarJogo(Personagem* personagem, const string& arquivo, int progressoBatalha = 0);

    /**
     * @brief Carrega um jogo salvo.
     * @throws PersistenciaException Em caso de falha ao abrir o arquivo ou dados corrompidos.
     */
    static Personagem* carregarJogo(const string& arquivo, int& progressoBatalha);
};

#endif // PERSISTENCIA_HPP
