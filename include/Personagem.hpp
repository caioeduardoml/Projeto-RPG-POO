#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include "Entidade.hpp"
#include "Inventario.hpp"
#include "Raca.hpp"
#include "Habilidade.hpp"
#include <vector>
#include <map>
#include <memory>

namespace RpgGame {

class Arma;
class Armadura;

class Personagem : public Entidade {
private:
    std::string raca; // name of the race as required by PDF page 4
    std::string classe_rpg; // as required by PDF page 4
    int experiencia; // as required by PDF page 4
    Inventario inventario; // as required by PDF page 4 (Composition)
    std::vector<std::unique_ptr<Habilidade>> habilidades; // as required by PDF page 4 (Polymorphic aggregation)

protected:
    std::shared_ptr<Raca> objeto_raca; // internal reference to the Raca object for bonuses
    int exp_proximo_nivel;
    int forca;
    int inteligencia;

    std::shared_ptr<Arma> armaEquipada;
    std::map<std::string, std::shared_ptr<Armadura>> armadurasEquipadas;

public:
    Personagem(std::string p_nome, std::string p_classe_rpg, std::shared_ptr<Raca> p_raca, int p_nivel, int p_vidaBase, int p_forca, int p_inteligencia);
    ~Personagem() override = default; // std::unique_ptr and std::shared_ptr handle deletions automatically!

    /**
     * @brief Retorna a classe de RPG do personagem.
     */
    std::string get_classe_rpg() const;
    std::string get_raca() const;
    std::shared_ptr<Raca> get_objeto_raca() const;
    int get_experiencia() const;
    int get_exp_proximo_nivel() const;

    /**
     * @brief Retorna a referência do inventário do personagem.
     */
    Inventario& get_inventario();
    std::shared_ptr<Arma> get_arma_equipada() const { return armaEquipada; }
    const std::map<std::string, std::shared_ptr<Armadura>>& get_armaduras_equipadas() const { return armadurasEquipadas; }

    /**
     * @brief Adiciona uma nova habilidade ao personagem.
     * @param habilidade Ponteiro único da Habilidade.
     */
    void adicionar_habilidade(std::unique_ptr<Habilidade> habilidade);
    void listar_habilidades() const;
    Habilidade* escolher_habilidade(int indice) const;

    /**
     * @brief Concede experiência ao personagem e checa por level up.
     * @param exp_ganha Quantidade de XP ganha.
     */
    void ganhar_experiencia(int exp_ganha); // as required by PDF page 4
    virtual void subir_nivel() = 0; // Pure virtual hook for Template Method

    /**
     * @brief Restaura o estado salvo de um personagem.
     */
    void restaurar_estado(int p_nivel_salvo, int p_xp, int p_vidaMax, int p_vidaAtual);

    void equipar_item(std::shared_ptr<Item> item); // as required by PDF page 4
    void desequipar_item(std::string nome_item); // as required by PDF page 4
    void usar_item(std::string nome_item); // as required by PDF page 4

    int get_dano_total() const;
    int get_defesa_total() const;
    int get_forca() const;
    int get_inteligencia() const;
    void exibir_equipamentos() const;

    void receber_dano(int dano) override;
    void exibir_status() const override;

    /**
     * @brief Executa um ataque usando uma habilidade específica.
     * @param alvo Entidade inimiga.
     * @param index_habilidade Índice da habilidade a ser usada.
     */
    void atacar(Entidade& alvo, int index_habilidade);

    friend std::ostream& operator<<(std::ostream& os, const Personagem& p);

    /**
     * @brief Sobrecarga do operador + para conceder experiência.
     */
    Personagem& operator+(int exp);

    /**
     * @brief Sobrecarga do operador + para adicionar um item ao inventário.
     */
    Personagem& operator+(std::shared_ptr<Item> item);
};

} // namespace RpgGame

#endif // PERSONAGEM_HPP
