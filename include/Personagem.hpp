#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include "Entidade.hpp"
#include "Inventario.hpp"
#include "Raca.hpp"
#include "Habilidade.hpp"
#include <vector>
#include <map>

using namespace std;

class Arma;
class Armadura;

class Personagem : public Entidade {
protected:
    string classeRPG;
    Raca* raca;
    float experiencia;
    float expProximoNivel;
    Inventario inventario;
    vector<Habilidade*> habilidades;

    float forca;
    float inteligencia;

    Arma* armaEquipada;
    std::map<std::string, Armadura*> armadurasEquipadas;

public:
    Personagem(string p_nome, string p_classeRPG, Raca* p_raca, int p_nivel, float p_vidaBase, float p_forca, float p_inteligencia);
    ~Personagem() override;

    string getClasseRPG() const;
    Raca* getRaca() const;
    float getExperiencia() const;
    Inventario& getInventario();

    void adicionarHabilidade(Habilidade* habilidade);
    void listarHabilidades() const;
    Habilidade* escolherHabilidade(int indice) const;

    void ganharExperiencia(float exp);
    virtual void subirNivel() = 0; // Pure virtual, must be implemented by concrete classes

    void restaurarEstado(int p_nivel_salvo, float p_xp, float p_vidaMax, float p_vidaAtual);

    void equiparArma(Arma* arma);
    void equiparArmadura(Armadura* armadura);
    void desequiparArma();
    void desequiparArmadura(const string& slot);
    float getDanoTotal() const;
    float getDefesaTotal() const;
    void exibirEquipamentos() const;

    void receberDano(float dano) override;
    void exibirStatus() const override;

    // Sobrecarga de operador << solicitada na especificação
    friend ostream& operator<<(ostream& os, const Personagem& p);
};

#endif // PERSONAGEM_HPP
