#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <string>

using namespace std;

class Jogador {
protected: 
    string nome;
    int nivel;
    float vida;
    float maxVida;
    float energia;
    float maxEnergia;
    float defesa;

public:
    Jogador(string p_nome, int p_nivel, float p_vida, float p_maxEnergia, float p_defesa);
    virtual ~Jogador() = default; 

    string getNome() const;
    float getVida() const;
    float getMaxVida() const;
    
    void receberDano(float dano);
    bool isVivo() const;
    void recuperarEnergia(float quantidade);

    virtual void subirNivel() = 0;

    virtual void exibirStatus() const;
    virtual void exibirOpcoesAtaque() const = 0; 
    virtual float realizarAtaque(int escolha) = 0; 
};

#endif // JOGADOR_HPP
