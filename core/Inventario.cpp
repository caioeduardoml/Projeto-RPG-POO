#include "../include/Inventario.hpp"
#include <iostream>
#include <algorithm>

Inventario::Inventario(float p_capacidade) : capacidadePeso(p_capacidade), pesoAtual(0.0f) {}

Inventario::~Inventario() {
    for (Item* item : itens) {
        delete item;
    }
    itens.clear();
}

bool Inventario::adicionarItem(Item* item) {
    if (pesoAtual + item->getPeso() > capacidadePeso) {
        cout << "Inventário cheio! Não é possível adicionar " << item->getNome() << ".\n";
        return false;
    }
    itens.push_back(item);
    pesoAtual += item->getPeso();
    return true;
}

bool Inventario::removerItem(Item* item) {
    auto it = find(itens.begin(), itens.end(), item);
    if (it != itens.end()) {
        pesoAtual -= (*it)->getPeso();
        itens.erase(it);
        return true;
    }
    return false;
}

void Inventario::listarItens() const {
    cout << "--- Inventário (" << pesoAtual << "/" << capacidadePeso << " kg) ---\n";
    if (itens.empty()) {
        cout << "Vazio.\n";
        return;
    }
    for (size_t i = 0; i < itens.size(); ++i) {
        cout << i+1 << ". " << itens[i]->getNome() << " - " << itens[i]->getDescricao() 
             << " (" << itens[i]->getPeso() << " kg)\n";
    }
}

float Inventario::getPesoAtual() const { return pesoAtual; }
float Inventario::getCapacidade() const { return capacidadePeso; }

vector<Item*> Inventario::getItensPorTipo(TipoItem tipo) const {
    vector<Item*> filtrados;
    for (Item* item : itens) {
        if (item->getTipo() == tipo) {
            filtrados.push_back(item);
        }
    }
    return filtrados;
}

Item* Inventario::buscarItem(const string& nome) const {
    for (Item* item : itens) {
        if (item->getNome() == nome) {
            return item;
        }
    }
    return nullptr;
}

Item* Inventario::getItem(int indice) const {
    if (indice >= 0 && indice < static_cast<int>(itens.size())) {
        return itens[indice];
    }
    return nullptr;
}

int Inventario::getQuantidadeItens() const {
    return itens.size();
}
