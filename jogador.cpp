#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Jogador {
protected: 
    string nome;
    int nivel;
    float vida;

public:
    Jogador(string p_nome, int p_nivel, float p_vida) : nome(p_nome), nivel(p_nivel), vida(p_vida) {}
    
    virtual ~Jogador() = default; 

    string getNome() const { return nome; }

    virtual float atacar() = 0; 
};

class Guerreiro : public Jogador {
private:
    float forca; 
public:
    Guerreiro(string p_nome, int p_nivel, float p_vida, float p_forca) 
        : Jogador(p_nome, p_nivel, p_vida), forca(p_forca) {}

    float atacar() override {
        float dano = forca * 1.5f; 
        cout << "[Guerreiro] " << nome << " golpeia com força bruta! Dano causado: " << dano << "\n";
        return dano;
    }
};

class Mago : public Jogador {
private:
    float mana;         
    float inteligencia; 
public:
    Mago(string p_nome, int p_nivel, float p_vida, float p_mana, float p_inteligencia) 
        : Jogador(p_nome, p_nivel, p_vida), mana(p_mana), inteligencia(p_inteligencia) {}

    float atacar() override {
        if (mana >= 10.0f) {
            mana -= 10.0f;
            float dano = inteligencia * 2.0f; 
            cout << "[Mago] " << nome << " conjura chamas mágicas! (Mana restante: " << mana << ") Dano: " << dano << "\n";
            return dano;
        } else {
            float dano_base = 5.0f; 
            cout << "[Mago] " << nome << " está sem mana e ataca fracamente com o cajado! Dano base: " << dano_base << "\n";
            return dano_base;
        }
    }
};


class Druida : public Jogador {
private:
    float mana;         
    float sabedoria; 
public:
    Druida(string p_nome, int p_nivel, float p_vida, float p_mana, float p_sabedoria) 
        : Jogador(p_nome, p_nivel, p_vida), mana(p_mana), sabedoria(p_sabedoria) {}

    float atacar() override {
        if (mana >= 8.0f) {
            mana -= 8.0f;
            float dano = sabedoria * 2.5f; 
            cout << "[Druida] " << nome << " lanca uma pedra! (Mana restante: " << mana << ") Dano: " << dano << "\n";
            return dano;
        } else {
            float dano_base = 5.0f; 
            cout << "[Druida] " << nome << " está sem mana e ataca fracamente com o cajado! Dano base: " << dano_base << "\n";
            return dano_base;
        }
    }
};

class Arqueiro : public Jogador {
private:
    float destreza;         
    float agilidade; 
    int municao;
public:
    Arqueiro(string p_nome, int p_nivel, float p_vida, float p_destreza, float p_agilidade, int p_municao) 
        : Jogador(p_nome, p_nivel, p_vida), destreza(p_destreza), agilidade(p_agilidade), municao(p_municao) {}

    float atacar() override {
        if (municao >= 1) {
            municao -= 1;
            float dano = agilidade * 1.5f; 
            cout << "[Arqueiro] " << nome << " atira uma flecha! (Flechas restantes: " << municao << ") Dano: " << dano << "\n";
            return dano;
        } else {
            float dano_base = 1.5f*destreza; 
            cout << "[Arqueiro] " << nome << " está sem flechas e bate com o arco! Dano: " << dano_base << "\n";
            return dano_base;
        }
    }
};

class Ladrao : public Jogador {
private:
    float agilidade;      
    float chance_critico; 
public:
    Ladrao(string p_nome, int p_nivel, float p_vida, float p_agilidade, float p_chance_critico) 
        : Jogador(p_nome, p_nivel, p_vida), agilidade(p_agilidade), chance_critico(p_chance_critico) {}

    float atacar() override {
        float dano_base = agilidade;
        float sorte = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

        if (sorte <= chance_critico) {
            float dano_critico = dano_base * 3.0f; 
            cout << "[Ladrão] " << nome << " encontra uma brecha! ACERTO CRÍTICO! Dano: " << dano_critico << "\n";
            return dano_critico;
        } else {
            cout << "[Ladrão] " << nome << " realiza um ataque rápido! Dano: " << dano_base << "\n";
            return dano_base;
        }
    }
};


class Monstro : public Jogador {
private:
    float forca;         
    float agilidade; 
public:
    Monstro(string p_nome, int p_nivel, float p_vida, float p_forca, float p_agilidade) 
        : Jogador(p_nome, p_nivel, p_vida), forca(p_forca), agilidade(p_agilidade) {}

    float atacar() override {
        if (forca >= 8.0f) {
            forca -= 8.0f;
            float dano = forca * 2.5f; 
            cout << "[Monstro] " << nome << " ataca com suas presas! Dano: " << dano << "\n";
            return dano;
        } else {
            float dano_base = 5.0f; 
            cout << "[Monstro] " << nome << " ataca com as garras! Dano base: " << dano_base << "\n";
            return dano_base;
        }
    }
};

//classe construtor de energia
class ConstrutorEnergia : public Jogador {
private:
    float energia;
    float criatividade;
public:
    ConstrutorEnergia(string p_nome, int p_nivel, float p_vida, float p_energia, float p_criatividade) 
        : Jogador(p_nome, p_nivel, p_vida), energia(p_energia), criatividade(p_criatividade) {}

    float atacar() override {
        if (energia >= 8.0f) {
            energia -= 8.0f;
            float dano = criatividade * 2.5f; 
            cout << "[ConstrutorEnergia] " << nome << " lança uma constructo de energia! (Energia restante: " << energia << ") Dano: " << dano << "\n";
            return dano;
        } else {
            float dano_base = 5.0f; 
            cout << "[ConstrutorEnergia] " << nome << " ataca com as mãos! Dano base: " << dano_base << "\n";
            return dano_base;
        }
    }
};


int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<Jogador*> grupo;

    grupo.push_back(new Guerreiro("Guts", 15, 250.0f, 30.0f));

    grupo.push_back(new Mago("Gandalf", 20, 120.0f, 15.0f, 40.0f)); 

    grupo.push_back(new Druida("JoãoFrango", 15, 180.0f, 20.0f, 25.0f)); 

    grupo.push_back(new Arqueiro("VolinHabba", 15, 120.0f, 1.9f, 20.0f, 0)); 

    grupo.push_back(new ConstrutorEnergia("Goku", 20, 120.0f, 15.0f, 40.0f));

    grupo.push_back(new Monstro("Dragão", 20, 120.0f, 15.0f, 40.0f));

    grupo.push_back(new Ladrao("Garrett", 12, 100.0f, 22.0f, 0.35f)); 

    cout << "--- INÍCIO DO COMBATE ---\n";
    
    for (int rodada = 1; rodada <= 2; ++rodada) {
        cout << "\n=== Turno " << rodada << " ===\n";
        
        for (Jogador* jogador : grupo) {
            jogador->atacar(); 
        }
    }

    for (Jogador* jogador : grupo) {
        delete jogador;
    }
    grupo.clear();

    return 0;
}