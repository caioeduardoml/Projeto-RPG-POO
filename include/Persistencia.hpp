#ifndef PERSISTENCIA_HPP
#define PERSISTENCIA_HPP

#include "Personagem.hpp"
#include <string>
#include <memory>

namespace RpgGame {

class Persistencia {
public:
    static void salvarJogo(std::shared_ptr<Personagem> personagem, const std::string& arquivo, int progressoBatalha = 0);
    static std::shared_ptr<Personagem> carregarJogo(const std::string& arquivo, int& progressoBatalha);
};

} // namespace RpgGame

#endif // PERSISTENCIA_HPP
