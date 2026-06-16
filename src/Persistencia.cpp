#include "../include/Persistencia.hpp"
#include <fstream>
#include <iostream>

bool Persistencia::salvarJogo(Personagem* personagem, const string& arquivo) {
    ofstream out(arquivo);
    if (!out.is_open()) {
        cerr << "Erro ao abrir arquivo para salvar!\n";
        return false;
    }

    out << "Nome:" << personagem->getNome() << "\n";
    out << "Classe:" << personagem->getClasseRPG() << "\n";
    if (personagem->getRaca()) {
        out << "Raca:" << personagem->getRaca()->getNomeRaca() << "\n";
    } else {
        out << "Raca:Nenhuma\n";
    }
    out << "Nivel:" << personagem->getNivel() << "\n";
    out << "XP:" << personagem->getExperiencia() << "\n";
    out << "VidaMax:" << personagem->getMaxVida() << "\n";
    out << "VidaAtual:" << personagem->getVida() << "\n";

    out.close();
    cout << "Jogo salvo com sucesso em " << arquivo << "!\n";
    return true;
}
