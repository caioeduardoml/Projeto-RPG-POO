#include "../include/MonstroFactory.hpp"

namespace RpgGame {

std::shared_ptr<Monstro> MonstroFactory::criar_monstro(const std::string& nome, int /*nivel*/) {
    if (nome == "Goblin") return std::make_shared<Goblin>();
    if (nome == "Goblin Chefao" || nome == "Goblin Chefão") return std::make_shared<GoblinChefao>();
    if (nome == "Orc Furioso" || nome == "Orc") return std::make_shared<OrcMonstro>();
    if (nome == "Lobo Mau") return std::make_shared<LoboMau>();
    if (nome == "Gigante Malvado" || nome == "Gigante Malvadão") return std::make_shared<GiganteMalvado>();
    if (nome == "Peppa Pig") return std::make_shared<PeppaPig>();

    return std::make_shared<Goblin>();
}

} // namespace RpgGame
