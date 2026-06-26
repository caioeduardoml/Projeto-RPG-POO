#include "../../include/Ladrao.hpp"
#include "../../include/GerenciadorJogo.hpp"
#include <iostream>
#include <memory>

namespace RpgGame {

Ladrao::Ladrao(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel)
    : Personagem(p_nome, "Ladrão", p_raca, p_nivel, 100, 12, 12), furtividade(100) {
    adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Ataque Furtivo", "Causa dano extra se não for detectado", 10, 30));
}

void Ladrao::subir_nivel() {
    pontos_vida_max += 12;
    pontos_vida_atual = pontos_vida_max;
    forca += 3;
    inteligencia += 3;
    furtividade = 100; // Restaura a furtividade máxima
    
    std::string msg = nome + " subiu para o nível " + std::to_string(nivel) + "!\n" +
                      "Vida máxima aumentada para " + std::to_string(pontos_vida_max) + 
                      " e Furtividade restaurada para " + std::to_string(furtividade) + "%.";
    GerenciadorJogo::get_instancia().notificar(msg);

    if (nivel == 2) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Ataque olhos fechado", "Causa dano extra se não for detectado", 10, 60));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Ataque olhos fechado! <<<");
    } else if (nivel == 3) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Ataque com punho", "Causa dano extra se não for detectado", 10, 50));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Ataque com punho! <<<");
    } else if (nivel == 4) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Facada nas Costas", "Ataque fatal e preciso", 20, 80));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Facada nas Costas! <<<");
    } else if (nivel == 5) {
        adicionar_habilidade(std::make_unique<HabilidadeDefensiva>("Evasão Perfeita", "Desvia de ataques com extrema facilidade", 15, 100));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Evasão Perfeita! <<<");
    } else if (nivel == 6) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Roubo de Vida", "Ataca o inimigo e recupera vida", 25, 120));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Roubo de Vida! <<<");
    }
}

void Ladrao::receber_dano(int dano) {
    // Especialização: Se furtivo (furtividade > 0), reduz o dano em 30% e consome 25 de furtividade
    int defesa = get_defesa_total();
    int danoLiquido = dano - defesa;
    if (danoLiquido < 0) danoLiquido = 0;

    int mitigado = 0;
    if (furtividade > 0 && danoLiquido > 0) {
        mitigado = static_cast<int>(danoLiquido * 0.3f);
        furtividade -= 25;
        if (furtividade < 0) furtividade = 0;
        danoLiquido -= mitigado;
    }

    pontos_vida_atual -= danoLiquido;
    if (pontos_vida_atual < 0) pontos_vida_atual = 0;

    std::string log = "[" + nome + " recebe " + std::to_string(danoLiquido) + 
                      " de dano! (Mitigado por Furtividade: " + std::to_string(mitigado) + " | Furtividade restante: " + std::to_string(furtividade) + ")]";
    GerenciadorJogo::get_instancia().notificar(log);
}

int Ladrao::get_furtividade() const { return furtividade; }
void Ladrao::recuperar_furtividade(int quantidade) {
    furtividade += quantidade;
    if (furtividade > 100) furtividade = 100;
}

} // namespace RpgGame
