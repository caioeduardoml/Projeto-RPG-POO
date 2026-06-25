#include "../include/Persistencia.hpp"
#include "../include/PersonagemFactory.hpp"
#include "../include/Exceptions.hpp"
#include <fstream>
#include <iostream>

namespace RpgGame {

void Persistencia::salvarJogo(std::shared_ptr<Personagem> personagem, const std::string& arquivo, int progressoBatalha) {
    if (!personagem) return;
    std::ofstream out(arquivo);
    if (!out.is_open()) {
        throw PersistenciaException("Erro ao abrir arquivo para salvar!");
    }

    out << "Nome:" << personagem->get_nome() << "\n";
    out << "Classe:" << personagem->get_classe_rpg() << "\n";
    out << "Raca:" << personagem->get_raca() << "\n";
    out << "Nivel:" << personagem->get_nivel() << "\n";
    out << "XP:" << personagem->get_experiencia() << "\n";
    out << "VidaMax:" << personagem->get_pontos_vida_max() << "\n";
    out << "VidaAtual:" << personagem->get_pontos_vida_atual() << "\n";
    out << "ProgressoBatalha:" << progressoBatalha << "\n";

    out.close();
}

std::shared_ptr<Personagem> Persistencia::carregarJogo(const std::string& arquivo, int& progressoBatalha) {
    std::ifstream in(arquivo);
    if (!in.is_open()) {
        throw PersistenciaException("Erro ao abrir arquivo para carregar!");
    }

    std::string linha;
    std::string nome, classe, racaStr;
    int nivel = 1;
    int xp = 0, vidaMax = 100, vidaAtual = 100;
    int prog = 0;

    while (std::getline(in, linha)) {
        size_t pos = linha.find(':');
        if (pos != std::string::npos) {
            std::string chave = linha.substr(0, pos);
            std::string valor = linha.substr(pos + 1);

            if (chave == "Nome") nome = valor;
            else if (chave == "Classe") classe = valor;
            else if (chave == "Raca") racaStr = valor;
            else if (chave == "Nivel") nivel = std::stoi(valor);
            else if (chave == "XP") xp = std::stoi(valor);
            else if (chave == "VidaMax") vidaMax = std::stoi(valor);
            else if (chave == "VidaAtual") vidaAtual = std::stoi(valor);
            else if (chave == "ProgressoBatalha") prog = std::stoi(valor);
        }
    }
    in.close();

    progressoBatalha = prog;

    if (nome.empty() || classe.empty()) {
        throw PersistenciaException("Arquivo de savegame corrompido!");
    }

    // Usar o padrão Factory
    auto p = PersonagemFactory::criar_personagem(nome, classe, racaStr, 1);
    p->restaurar_estado(nivel, xp, vidaMax, vidaAtual);

    return p;
}

} // namespace RpgGame
