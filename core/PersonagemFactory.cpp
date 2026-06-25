#include "../include/PersonagemFactory.hpp"
#include "../include/Guerreiro.hpp"
#include "../include/Mago.hpp"
#include "../include/Arqueiro.hpp"
#include "../include/Clerigo.hpp"
#include "../include/Druida.hpp"
#include "../include/Ladrao.hpp"
#include "../include/ConstrutorEnergia.hpp"

namespace RpgGame {

std::shared_ptr<Personagem> PersonagemFactory::criar_personagem(const std::string& nome, const std::string& classe, const std::string& racaStr, int nivel) {
    std::shared_ptr<Raca> raca = nullptr;
    if (racaStr == "Humano") raca = std::make_shared<Humano>();
    else if (racaStr == "Elfo") raca = std::make_shared<Elfo>();
    else if (racaStr == "Anão" || racaStr == "Anao") raca = std::make_shared<Anao>();
    else if (racaStr == "Orc") raca = std::make_shared<Orc>();
    else if (racaStr == "Dragão" || racaStr == "Dragao") raca = std::make_shared<Dragao>();
    else raca = std::make_shared<Humano>();

    if (classe == "Guerreiro") return std::make_shared<Guerreiro>(nome, raca, nivel);
    if (classe == "Mago") return std::make_shared<Mago>(nome, raca, nivel);
    if (classe == "Arqueiro") return std::make_shared<Arqueiro>(nome, raca, nivel);
    if (classe == "Clérigo" || classe == "Clerigo") return std::make_shared<Clerigo>(nome, raca, nivel);
    if (classe == "Druida") return std::make_shared<Druida>(nome, raca, nivel);
    if (classe == "Ladrão" || classe == "Ladrao") return std::make_shared<Ladrao>(nome, raca, nivel);
    if (classe == "Construtor de Energia" || classe == "ConstrutorEnergia" || classe == "Construtor de energia") return std::make_shared<ConstrutorEnergia>(nome, raca, nivel);

    return std::make_shared<Guerreiro>(nome, raca, nivel);
}

} // namespace RpgGame
