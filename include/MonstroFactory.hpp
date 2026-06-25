#ifndef MONSTRO_FACTORY_HPP
#define MONSTRO_FACTORY_HPP

#include "Monstro.hpp"
#include <memory>
#include <string>

namespace RpgGame {

class MonstroFactory {
public:
    static std::shared_ptr<Monstro> criar_monstro(const std::string& nome, int nivel = 1);
};

} // namespace RpgGame

#endif // MONSTRO_FACTORY_HPP
