#include <iostream>
#include <string>
using namespace std;

class Jogador {
public:
    string nome;
    int nivel;
    int hp;
    int hp_maximo;
    
    // Construtor
    Jogador(string Nome, int Nivel, int hp_max) {
        nome = Nome;
        nivel = Nivel;
        hp_maximo = hp_max;
        hp = hp_maximo;
    }
    
    void exibirStatus() {
        cout << "Nome: " << nome << endl;
        cout << "Nível: " << nivel << endl;
        cout << "HP: " << hp << "/" << hp_maximo << endl;
        cout << "--------------------" << endl;
    }
    
    bool estaVivo() {
        return hp > 0;
    }
    
    void receberDano(int dano) {
        hp -= dano;
        if (hp < 0) hp = 0;
        cout << nome << " recebeu " << dano << " de dano!" << endl;
        cout << "HP atual: " << hp << "/" << hp_maximo << endl;
        if (!estaVivo()) {
            cout << nome << " morreu!" << endl;
        }
    }
    
    void curar(int quantidade) {
        hp += quantidade;
        if (hp > hp_maximo) hp = hp_maximo;
        cout << nome << " recuperou " << quantidade << " de HP!" << endl;
        cout << "HP atual: " << hp << "/" << hp_maximo << endl;
    }
};

int main() {
    
    // Criando jogador
    Jogador jogador("Caio Bonitao", 999, 999999);
    jogador.exibirStatus();
    
    cout << "Vivo? " << (jogador.estaVivo() ? "Sim" : "Não") << endl;
    cout << endl;
    
    jogador.receberDano(999);
    jogador.exibirStatus();
    
    jogador.curar(99);
    jogador.exibirStatus();
    
    jogador.receberDano(99999);
    jogador.exibirStatus();
    
    cout << "Vivo? " << (jogador.estaVivo() ? "Sim" : "Não") << endl;
    
    return 0;
}