#ifndef PERSONAGEM_FACTORY_HPP
#define PERSONAGEM_FACTORY_HPP

#include "Personagem.hpp"
#include "Raca.hpp"
#include <memory>
#include <string>

namespace RpgGame {

class PersonagemFactory {
public:
    static std::shared_ptr<Personagem> criar_personagem(const std::string& nome, const std::string& classe, const std::string& raca, int nivel);
};

} // namespace RpgGame

#endif // PERSONAGEM_FACTORY_HPP
