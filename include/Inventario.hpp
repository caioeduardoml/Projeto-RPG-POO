#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include "Item.hpp"
#include <vector>
#include <memory>

namespace RpgGame {

class Inventario {
private:
    std::vector<std::shared_ptr<Item>> itens;
    double capacidade_peso_max;
    double peso_atual;

public:
    Inventario(double p_capacidade);
    ~Inventario() = default; // std::shared_ptr handles memory automatically!

    bool adicionar_item(std::shared_ptr<Item> item);
    void remover_item(std::shared_ptr<Item> item);
    void remover_item(const std::string& nome_item);
    
    void listar_itens() const;
    double get_peso_atual() const;
    double get_capacidade_peso_max() const;
    
    std::vector<std::shared_ptr<Item>> get_itens_por_tipo(TipoItem tipo) const;
    std::shared_ptr<Item> buscar_item(const std::string& nome) const;
    
    std::shared_ptr<Item> get_item(int indice) const;
    int get_quantidade_itens() const;
};

} // namespace RpgGame

#endif // INVENTARIO_HPP
