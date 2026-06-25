#include "../include/Personagem.hpp"
#include "../include/Item.hpp"
#include "../include/Exceptions.hpp"
#include "../include/GerenciadorJogo.hpp"
#include <iostream>
#include <algorithm>

namespace RpgGame {

Personagem::Personagem(std::string p_nome, std::string p_classe_rpg, std::shared_ptr<Raca> p_raca, int p_nivel, int p_vidaBase, int p_forca, int p_inteligencia)
    : Entidade(p_nome, p_nivel, p_vidaBase + (p_raca ? p_raca->get_bonus_vida() : 0), 50),
      raca(p_raca ? p_raca->get_nome_raca() : "Nenhuma"),
      classe_rpg(p_classe_rpg),
      experiencia(0),
      exp_proximo_nivel(100 * p_nivel),
      inventario(50.0), // 50kg de capacidade inicial
      objeto_raca(p_raca),
      forca(p_forca + (p_raca ? p_raca->get_bonus_forca() : 0)),
      inteligencia(p_inteligencia + (p_raca ? p_raca->get_bonus_inteligencia() : 0)),
      armaEquipada(nullptr) {
    if (p_vidaBase < 0 || p_forca < 0 || p_inteligencia < 0) {
        throw PersonagemException("Atributos base não podem ser negativos!");
    }
}

std::string Personagem::get_classe_rpg() const { return classe_rpg; }
std::string Personagem::get_raca() const { return raca; }
std::shared_ptr<Raca> Personagem::get_objeto_raca() const { return objeto_raca; }
int Personagem::get_experiencia() const { return experiencia; }
int Personagem::get_exp_proximo_nivel() const { return exp_proximo_nivel; }
Inventario& Personagem::get_inventario() { return inventario; }

void Personagem::adicionar_habilidade(std::unique_ptr<Habilidade> habilidade) {
    habilidades.push_back(std::move(habilidade));
}

void Personagem::listar_habilidades() const {
    std::cout << "--- Habilidades de " << nome << " ---\n";
    for (size_t i = 0; i < habilidades.size(); ++i) {
        if (habilidades[i]) {
            std::cout << i+1 << ". " << habilidades[i]->get_nome() << " - " << habilidades[i]->get_descricao() 
                      << " " << habilidades[i]->get_efeito_str() << "\n";
        }
    }
}

Habilidade* Personagem::escolher_habilidade(int indice) const {
    if (indice >= 0 && indice < static_cast<int>(habilidades.size())) {
        return habilidades[indice].get();
    }
    return nullptr;
}

void Personagem::ganhar_experiencia(int exp_ganha) {
    experiencia += exp_ganha;
    std::string log = nome + " ganhou " + std::to_string(exp_ganha) + " XP!";
    GerenciadorJogo::get_instancia().notificar(log);
    
    while (experiencia >= exp_proximo_nivel) {
        experiencia -= exp_proximo_nivel;
        nivel++;
        exp_proximo_nivel = 100 * nivel;
        subir_nivel(); // Template Method hook call
        recuperar_energia(energia_max);
    }
}

void Personagem::receber_dano(int dano) {
    int defesa = get_defesa_total();
    int danoLiquido = dano - defesa;
    if (danoLiquido < 0) danoLiquido = 0;
    pontos_vida_atual -= danoLiquido;
    if (pontos_vida_atual < 0) pontos_vida_atual = 0;
    
    std::string log = "[" + nome + " recebe " + std::to_string(danoLiquido) + 
                      " de dano! (Defesa bloqueou " + std::to_string(dano - danoLiquido) + ")]";
    GerenciadorJogo::get_instancia().notificar(log);
}

void Personagem::exibir_status() const {
    Entidade::exibir_status();
    std::cout << "| Classe: " << classe_rpg << " | Raça: " << raca
              << " | XP: " << experiencia << "/" << exp_proximo_nivel << "\n"
              << "| Dano Total: " << get_dano_total() << " | Defesa Total: " << get_defesa_total() << "\n";
}

std::ostream& operator<<(std::ostream& os, const Personagem& p) {
    os << "[" << p.nome << " Nv." << p.nivel << " " << p.classe_rpg << "] Vida: " << p.pontos_vida_atual << "/" << p.pontos_vida_max;
    return os;
}

void Personagem::restaurar_estado(int p_nivel_salvo, int p_xp, int p_vidaMax, int p_vidaAtual) {
    while (this->nivel < p_nivel_salvo) {
        this->nivel++;
        this->exp_proximo_nivel = 100 * this->nivel;
        this->subir_nivel();
    }
    this->experiencia = p_xp;
    this->pontos_vida_max = p_vidaMax;
    this->pontos_vida_atual = p_vidaAtual;
}

void Personagem::equipar_item(std::shared_ptr<Item> item) {
    if (!item) return;

    if (item->get_tipo() == TipoItem::Arma) {
        auto arma = std::dynamic_pointer_cast<Arma>(item);
        if (arma) {
            if (armaEquipada) {
                inventario.adicionar_item(armaEquipada);
            }
            armaEquipada = arma;
            inventario.remover_item(item);
            std::string log = ">>> " + nome + " equipou " + arma->get_nome() + "!";
            GerenciadorJogo::get_instancia().notificar(log);
        }
    } else if (item->get_tipo() == TipoItem::Armadura) {
        auto armadura = std::dynamic_pointer_cast<Armadura>(item);
        if (armadura) {
            // Usa o primeiro nome/palavra para determinar o slot
            std::string slot = armadura->get_nome().substr(0, armadura->get_nome().find(' '));
            if (armadurasEquipadas.find(slot) != armadurasEquipadas.end()) {
                inventario.adicionar_item(armadurasEquipadas[slot]);
            }
            armadurasEquipadas[slot] = armadura;
            inventario.remover_item(item);
            std::string log = ">>> " + nome + " equipou " + armadura->get_nome() + " no slot [" + slot + "]!";
            GerenciadorJogo::get_instancia().notificar(log);
        }
    }
}

void Personagem::desequipar_item(std::string nome_item) {
    if (armaEquipada && (armaEquipada->get_nome() == nome_item || nome_item == "Arma" || nome_item == "arma")) {
        inventario.adicionar_item(armaEquipada);
        std::string log = ">>> " + nome + " desequipou " + armaEquipada->get_nome() + "!";
        GerenciadorJogo::get_instancia().notificar(log);
        armaEquipada = nullptr;
        return;
    }

    for (auto const& [slot, armadura] : armadurasEquipadas) {
        if (armadura && (armadura->get_nome() == nome_item || slot == nome_item)) {
            inventario.adicionar_item(armadura);
            std::string log = ">>> " + nome + " desequipou " + armadura->get_nome() + " do slot [" + slot + "]!";
            GerenciadorJogo::get_instancia().notificar(log);
            armadurasEquipadas.erase(slot);
            return;
        }
    }
}

void Personagem::usar_item(std::string nome_item) {
    auto item = inventario.buscar_item(nome_item);
    if (!item) {
        throw InventarioException("Item " + nome_item + " não encontrado no inventário!");
    }

    std::string log = "----------------------------------------\n" + nome + " usou o item " + item->get_nome() + ".";
    GerenciadorJogo::get_instancia().notificar(log);
    
    item->usar(*this);

    // Se for consumível, remove do inventário
    if (item->get_tipo() == TipoItem::Pocao || 
        item->get_tipo() == TipoItem::PocaoEnergia || 
        item->get_tipo() == TipoItem::Bomba ||
        item->get_tipo() == TipoItem::Especial) {
        inventario.remover_item(item);
    }
}

void Personagem::atacar(Entidade& alvo, int index_habilidade) {
    if (index_habilidade == 0) {
        // Ataque básico
        std::string log = nome + " realiza um ataque básico!";
        GerenciadorJogo::get_instancia().notificar(log);
        int dano = get_dano_total();
        alvo.receber_dano(dano);
        
        // Recupera 15 de energia por realizar ataque básico
        recuperar_energia(15);
        GerenciadorJogo::get_instancia().notificar(nome + " recuperou 15 de energia pelo ataque básico.");
    } else {
        Habilidade* hab = escolher_habilidade(index_habilidade - 1);
        if (hab) {
            gastar_energia(hab->get_custo_energia());
            hab->usar(this, &alvo);
        } else {
            throw CombateException("Habilidade inválida!");
        }
    }
}

int Personagem::get_dano_total() const {
    int dano = forca;
    if (armaEquipada) {
        dano += armaEquipada->get_dano_bonus();
    }
    return dano;
}

int Personagem::get_defesa_total() const {
    int def = 0;
    for (auto const& [key, val] : armadurasEquipadas) {
        if (val) {
            def += val->get_defesa_bonus();
        }
    }
    return def;
}

int Personagem::get_forca() const { return forca; }
int Personagem::get_inteligencia() const { return inteligencia; }

void Personagem::exibir_equipamentos() const {
    std::cout << "\n--- Equipamentos de " << nome << " ---\n";
    std::cout << "[Arma]: " << (armaEquipada ? armaEquipada->get_nome() : "Nenhuma") << "\n";
    for (auto const& [slot, armadura] : armadurasEquipadas) {
        if (armadura) {
            std::cout << "[" << slot << "]: " << armadura->get_nome() << "\n";
        }
    }
}

Personagem& Personagem::operator+(int exp) {
    this->ganhar_experiencia(exp);
    return *this;
}

Personagem& Personagem::operator+(std::shared_ptr<Item> item) {
    if (item) {
        this->inventario.adicionar_item(item);
    }
    return *this;
}

} // namespace RpgGame
