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
    static GerenciadorJogo& get_instancia();
    
    // Deletar construtor de cópia e operador de atribuição para garantir Singleton
    GerenciadorJogo(const GerenciadorJogo&) = delete;
    GerenciadorJogo& operator=(const GerenciadorJogo&) = delete;

    std::shared_ptr<Personagem> get_heroi() const;
    void set_heroi(std::shared_ptr<Personagem> p_heroi);

    std::shared_ptr<Monstro> get_monstro_atual() const;
    void set_monstro_atual(std::shared_ptr<Monstro> p_monstro);

    std::shared_ptr<Entidade> get_inimigo_ativo() const;

    int get_progresso_batalha() const;
    void set_progresso_batalha(int progresso);

    void iniciar_desafio_arena();
};

} // namespace RpgGame

#endif // GERENCIADOR_JOGO_HPP
