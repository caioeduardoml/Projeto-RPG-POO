#ifndef GERENCIADOR_JOGO_HPP
#define GERENCIADOR_JOGO_HPP

#include "Personagem.hpp"
#include "Monstro.hpp"
#include "Observer.hpp"
#include <memory>

namespace RpgGame {

class GerenciadorJogo : public Subject {
private:
    static std::unique_ptr<GerenciadorJogo> instancia;
    std::shared_ptr<Personagem> heroi;
    std::shared_ptr<Monstro> monstro_atual;
    int progresso_batalha;

    GerenciadorJogo();

public:
    /**
     * @brief Retorna a instância única (Singleton) do gerenciador de jogo.
     * @return GerenciadorJogo& Referência para a instância.
     */
    static GerenciadorJogo& get_instancia();
    // Deletar construtor de cópia e operador de atribuição para garantir Singleton
    GerenciadorJogo(const GerenciadorJogo&) = delete;
    GerenciadorJogo& operator=(const GerenciadorJogo&) = delete;

    /**
     * @brief Obtém o herói atual.
     * @return std::shared_ptr<Personagem> Ponteiro para o herói.
     */
    std::shared_ptr<Personagem> get_heroi() const;

    /**
     * @brief Define o herói do jogo.
     * @param p_heroi Ponteiro para o herói.
     */
    void set_heroi(std::shared_ptr<Personagem> p_heroi);

    std::shared_ptr<Monstro> get_monstro_atual() const;
    void set_monstro_atual(std::shared_ptr<Monstro> p_monstro);

    std::shared_ptr<Entidade> get_inimigo_ativo() const;

    int get_progresso_batalha() const;
    void set_progresso_batalha(int progresso);

    /**
     * @brief Inicia uma nova batalha na arena com base no progresso.
     * @throws CombateException caso o jogador já tenha vencido todos os desafios.
     */
    void iniciar_desafio_arena();
};

} // namespace RpgGame

#endif // GERENCIADOR_JOGO_HPP
