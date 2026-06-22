#include "../include/Persistencia.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "../include/Guerreiro.hpp"
#include "../include/Mago.hpp"
#include "../include/Druida.hpp"
#include "../include/Arqueiro.hpp"
#include "../include/Ladrao.hpp"
#include "../include/ConstrutorEnergia.hpp"
#include "../include/Raca.hpp"
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

Personagem* Persistencia::carregarJogo(const string& arquivo) {
    ifstream in(arquivo);
    if (!in.is_open()) {
        cerr << "Erro ao abrir arquivo para carregar!\n";
        return nullptr;
    }

    string linha;
    string nome, classe, racaStr;
    int nivel = 1;
    float xp = 0.0f, vidaMax = 100.0f, vidaAtual = 100.0f;

    while (getline(in, linha)) {
        size_t pos = linha.find(':');
        if (pos != string::npos) {
            string chave = linha.substr(0, pos);
            string valor = linha.substr(pos + 1);

            if (chave == "Nome") nome = valor;
            else if (chave == "Classe") classe = valor;
            else if (chave == "Raca") racaStr = valor;
            else if (chave == "Nivel") nivel = stoi(valor);
            else if (chave == "XP") xp = stof(valor);
            else if (chave == "VidaMax") vidaMax = stof(valor);
            else if (chave == "VidaAtual") vidaAtual = stof(valor);
        }
    }
    in.close();

    if (nome.empty() || classe.empty()) return nullptr;

    Raca* raca = nullptr;
    if (racaStr == "Humano") raca = new Humano();
    else if (racaStr == "Elfo") raca = new Elfo();
    else if (racaStr == "Anão") raca = new Anao();
    else if (racaStr == "Orc") raca = new Orc();
    else if (racaStr == "Dragão") raca = new Dragao();
    else if (racaStr != "Nenhuma") raca = new Humano(); // Default fallback

    Personagem* p = nullptr;
    if (classe == "Guerreiro") p = new Guerreiro(nome, raca, 1);
    else if (classe == "Mago") p = new Mago(nome, raca, 1);
    else if (classe == "Arqueiro") p = new Arqueiro(nome, raca, 1);
    else if (classe == "Druida") p = new Druida(nome, raca, 1);
    else if (classe == "Ladrão") p = new Ladrao(nome, raca, 1);
    else if (classe == "Construtor de Energia") p = new ConstrutorEnergia(nome, raca, 1);
    else p = new Guerreiro(nome, raca, 1);

    p->restaurarEstado(nivel, xp, vidaMax, vidaAtual);

    cout << "Jogo carregado com sucesso!\n";
    return p;
}
