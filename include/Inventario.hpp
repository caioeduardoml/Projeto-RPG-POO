#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include "Item.hpp"
#include <vector>

using namespace std;

class Inventario {
private:
    vector<Item*> itens;
    float capacidadePeso;
    float pesoAtual;

public:
    Inventario(float p_capacidade);
    ~Inventario();

    /**
     * @brief Adiciona um item ao inventário.
     * @param item O item a ser adicionado.
     * @throws InventarioException Se o inventário estiver cheio (capacidade excedida).
     */
    void adicionarItem(Item* item);
    bool removerItem(Item* item);
    
    void listarItens() const;
    float getPesoAtual() const;
    float getCapacidade() const;
    
    vector<Item*> getItensPorTipo(TipoItem tipo) const;
    Item* buscarItem(const string& nome) const;
    
    Item* getItem(int indice) const;
    int getQuantidadeItens() const;
};

#endif // INVENTARIO_HPP
