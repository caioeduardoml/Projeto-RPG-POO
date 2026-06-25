#include "../include/Inventario.hpp"
#include "../include/Exceptions.hpp"
#include <iostream>
#include <algorithm>

namespace RpgGame {

Inventario::Inventario(double p_capacidade) 
    : capacidade_peso_max(p_capacidade), peso_atual(0.0f) {}

bool Inventario::adicionar_item(std::shared_ptr<Item> item) {
    if (!item) return false;
    if (peso_atual + item->get_peso() > capacidade_peso_max) {
        throw InventarioException("Inventário cheio! Não é possível adicionar " + item->get_nome() + ".");
    }
    itens.push_back(item);
    peso_atual += item->get_peso();
    return true;
}

void Inventario::remover_item(std::shared_ptr<Item> item) {
    auto it = std::find(itens.begin(), itens.end(), item);
    if (it != itens.end()) {
        peso_atual -= (*it)->get_peso();
        itens.erase(it);
    }
}

void Inventario::remover_item(const std::string& nome_item) {
    auto it = std::find_if(itens.begin(), itens.end(), [&](const std::shared_ptr<Item>& item) {
        return item && item->get_nome() == nome_item;
    });
    if (it != itens.end()) {
        peso_atual -= (*it)->get_peso();
        itens.erase(it);
    }
}

void Inventario::listar_itens() const {
    std::cout << "--- Inventário (" << peso_atual << "/" << capacidade_peso_max << " kg) ---\n";
    if (itens.empty()) {
        std::cout << "Vazio.\n";
        return;
    }
    for (size_t i = 0; i < itens.size(); ++i) {
        if (itens[i]) {
            std::cout << i+1 << ". " << itens[i]->get_nome() << " - " << itens[i]->get_descricao() 
                      << " (" << itens[i]->get_peso() << " kg)\n";
        }
    }
}

double Inventario::get_peso_atual() const { return peso_atual; }
double Inventario::get_capacidade_peso_max() const { return capacidade_peso_max; }

std::vector<std::shared_ptr<Item>> Inventario::get_itens_por_tipo(TipoItem tipo) const {
    std::vector<std::shared_ptr<Item>> filtrados;
    for (const auto& item : itens) {
        if (item && item->get_tipo() == tipo) {
            filtrados.push_back(item);
        }
    }
    return filtrados;
}

std::shared_ptr<Item> Inventario::buscar_item(const std::string& nome) const {
    for (const auto& item : itens) {
        if (item && item->get_nome() == nome) {
            return item;
        }
    }
    return nullptr;
}

std::shared_ptr<Item> Inventario::get_item(int indice) const {
    if (indice >= 0 && indice < static_cast<int>(itens.size())) {
        return itens[indice];
    }
    return nullptr;
}

int Inventario::get_quantidade_itens() const {
    return itens.size();
}

} // namespace RpgGame
