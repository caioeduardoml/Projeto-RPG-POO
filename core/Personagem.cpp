#include "../include/Personagem.hpp"
#include "../include/Item.hpp"
#include <iostream>

Personagem::Personagem(string p_nome, string p_classeRPG, Raca* p_raca, int p_nivel, float p_vidaBase, float p_forca, float p_inteligencia)
    : Entidade(p_nome, p_nivel, p_vidaBase + (p_raca ? p_raca->getBonusVida() : 0.0f)), 
      classeRPG(p_classeRPG), raca(p_raca), experiencia(0.0f), expProximoNivel(100.0f * p_nivel), 
      inventario(50.0f), // 50kg de capacidade inicial
      forca(p_forca + (p_raca ? p_raca->getBonusForca() : 0.0f)),
      inteligencia(p_inteligencia + (p_raca ? p_raca->getBonusInteligencia() : 0.0f)),
      armaEquipada(nullptr) {}

Personagem::~Personagem() {
    delete raca;
    for (Habilidade* hab : habilidades) {
        delete hab;
    }
    habilidades.clear();
    
    if (armaEquipada) {
        delete armaEquipada;
    }
    for (auto const& [key, val] : armadurasEquipadas) {
        delete val;
    }
    armadurasEquipadas.clear();
}

string Personagem::getClasseRPG() const { return classeRPG; }
Raca* Personagem::getRaca() const { return raca; }
float Personagem::getExperiencia() const { return experiencia; }
Inventario& Personagem::getInventario() { return inventario; }

void Personagem::adicionarHabilidade(Habilidade* habilidade) {
    habilidades.push_back(habilidade);
}

void Personagem::listarHabilidades() const {
    cout << "--- Habilidades de " << nome << " ---\n";
    for (size_t i = 0; i < habilidades.size(); ++i) {
        cout << i+1 << ". " << habilidades[i]->getNome() << " - " << habilidades[i]->getDescricao() 
             << " " << habilidades[i]->getEfeitoStr() << "\n";
    }
}

Habilidade* Personagem::escolherHabilidade(int indice) const {
    if (indice >= 0 && indice < static_cast<int>(habilidades.size())) {
        return habilidades[indice];
    }
    return nullptr;
}

void Personagem::ganharExperiencia(float exp) {
    experiencia += exp;
    cout << nome << " ganhou " << exp << " XP!\n";
    while (experiencia >= expProximoNivel) {
        experiencia -= expProximoNivel;
        nivel++;
        expProximoNivel = 100.0f * nivel;
        subirNivel();
    }
}

void Personagem::receberDano(float dano) {
    float defesa = getDefesaTotal();
    float danoLiquido = dano - defesa;
    if (danoLiquido < 0) danoLiquido = 0;
    vida -= danoLiquido;
    if (vida < 0) vida = 0;
    cout << "[" << nome << " recebe " << danoLiquido << " de dano! (Defesa bloqueou " << (dano - danoLiquido) << ")]\n";
}

void Personagem::exibirStatus() const {
    Entidade::exibirStatus();
    cout << "| Classe: " << classeRPG << " | Raça: " << (raca ? raca->getNomeRaca() : "Nenhuma") 
         << " | XP: " << experiencia << "/" << expProximoNivel << "\n"
         << "| Dano Total: " << getDanoTotal() << " | Defesa Total: " << getDefesaTotal() << "\n";
}

ostream& operator<<(ostream& os, const Personagem& p) {
    os << "[" << p.nome << " Nv." << p.nivel << " " << p.classeRPG << "] Vida: " << p.vida << "/" << p.maxVida;
    return os;
}

void Personagem::restaurarEstado(int p_nivel_salvo, float p_xp, float p_vidaMax, float p_vidaAtual) {
    while (this->nivel < p_nivel_salvo) {
        this->nivel++;
        this->expProximoNivel = 100.0f * this->nivel;
        this->subirNivel();
    }
    this->experiencia = p_xp;
    this->maxVida = p_vidaMax;
    this->vida = p_vidaAtual;
}

void Personagem::equiparArma(Arma* arma) {
    if (armaEquipada) {
        inventario.adicionarItem(armaEquipada);
    }
    armaEquipada = arma;
    inventario.removerItem(arma);
    cout << ">>> " << nome << " equipou " << arma->getNome() << "!\n";
}

void Personagem::equiparArmadura(Armadura* armadura) {
    string slot = armadura->getNome().substr(0, armadura->getNome().find(' '));
    if (armadurasEquipadas.find(slot) != armadurasEquipadas.end()) {
        inventario.adicionarItem(armadurasEquipadas[slot]);
    }
    armadurasEquipadas[slot] = armadura;
    inventario.removerItem(armadura);
    cout << ">>> " << nome << " equipou " << armadura->getNome() << "!\n";
}

void Personagem::desequiparArma() {
    if (armaEquipada) {
        inventario.adicionarItem(armaEquipada);
        cout << ">>> " << nome << " desequipou " << armaEquipada->getNome() << "!\n";
        armaEquipada = nullptr;
    }
}

void Personagem::desequiparArmadura(const string& slot) {
    if (armadurasEquipadas.find(slot) != armadurasEquipadas.end()) {
        inventario.adicionarItem(armadurasEquipadas[slot]);
        cout << ">>> " << nome << " desequipou " << armadurasEquipadas[slot]->getNome() << "!\n";
        armadurasEquipadas.erase(slot);
    }
}

float Personagem::getDanoTotal() const {
    float dano = forca;
    if (armaEquipada) {
        dano += armaEquipada->getDanoBonus();
    }
    return dano;
}

float Personagem::getDefesaTotal() const {
    float def = 0;
    for (auto const& [key, val] : armadurasEquipadas) {
        def += val->getDefesaBonus();
    }
    return def;
}

void Personagem::exibirEquipamentos() const {
    cout << "\n--- Equipamentos de " << nome << " ---\n";
    cout << "[Arma]: " << (armaEquipada ? armaEquipada->getNome() : "Nenhuma") << "\n";
    for (auto const& [slot, armadura] : armadurasEquipadas) {
        cout << "[" << slot << "]: " << armadura->getNome() << "\n";
    }
}

Personagem& Personagem::operator+(float exp) {
    this->ganharExperiencia(exp);
    return *this;
}

Personagem& Personagem::operator+(Item* item) {
    if (item) {
        this->inventario.adicionarItem(item);
    }
    return *this;
}

