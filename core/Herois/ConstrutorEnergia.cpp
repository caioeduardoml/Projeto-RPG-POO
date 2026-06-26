#include "../../include/ConstrutorEnergia.hpp"
#include "../../include/GerenciadorJogo.hpp"
#include <iostream>
#include <memory>

namespace RpgGame {

ConstrutorEnergia::ConstrutorEnergia(std::string p_nome, std::shared_ptr<Raca> p_raca, int p_nivel)
    : Personagem(p_nome, "Construtor de Energia", p_raca, p_nivel, 150, 20, 20), barreira_energia(30) {
    adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Kamehameha", "Ataque massivo de energia", 50, 100));
}

void ConstrutorEnergia::subir_nivel() {
    pontos_vida_max += 50;
    pontos_vida_atual = pontos_vida_max;
    forca += 10;
    inteligencia += 10;
    barreira_energia += 15;
    if (barreira_energia > 100) barreira_energia = 100;
    
    std::string msg = nome + " subiu para o nível " + std::to_string(nivel) + "!\n" +
                      "Vida máxima aumentada para " + std::to_string(pontos_vida_max) + 
                      " e Barreira de Energia aumentada para " + std::to_string(barreira_energia) + "%.";
    GerenciadorJogo::get_instancia().notificar(msg);

    if (nivel == 2) {
        adicionar_habilidade(std::make_unique<HabilidadeDefensiva>("Escudo de Energia", "Escudo que protege contra ataques", 0, 50));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Escudo de Energia! <<<");
    } else if (nivel == 3) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Golpe de Energia", "Golpe de energia", 50, 50));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Golpe de Energia! <<<");
    } else if (nivel == 4) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Sobrecarga", "Explosão de energia massiva", 70, 150));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Sobrecarga! <<<");
    } else if (nivel == 5) {
        adicionar_habilidade(std::make_unique<HabilidadeSuporte>("Bateria Infinita", "Restaura muita energia", 0, 200));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Bateria Infinita! <<<");
    } else if (nivel == 6) {
        adicionar_habilidade(std::make_unique<HabilidadeOfensiva>("Genki Dama", "Ataque supremo de energia", 100, 300));
        GerenciadorJogo::get_instancia().notificar(">>> Nova Habilidade Desbloqueada: Genki Dama! <<<");
    }
}

void ConstrutorEnergia::receber_dano(int dano) {
    // Especialização: Barreira de Energia mitiga dano fixo igual a metade da barreira. A barreira diminui 5 por golpe.
    int defesa = get_defesa_total();
    int danoLiquido = dano - defesa;
    if (danoLiquido < 0) danoLiquido = 0;

    int mitigado = 0;
    if (barreira_energia > 0 && danoLiquido > 0) {
        mitigado = barreira_energia / 2;
        if (mitigado > danoLiquido) mitigado = danoLiquido;
        danoLiquido -= mitigado;
        barreira_energia -= 5;
        if (barreira_energia < 0) barreira_energia = 0;
    }

    pontos_vida_atual -= danoLiquido;
    if (pontos_vida_atual < 0) pontos_vida_atual = 0;

    std::string log = "[" + nome + " recebe " + std::to_string(danoLiquido) + 
                      " de dano! (Mitigado por Barreira: " + std::to_string(mitigado) + " | Barreira restante: " + std::to_string(barreira_energia) + ")]";
    GerenciadorJogo::get_instancia().notificar(log);
}

int ConstrutorEnergia::get_barreira_energia() const { return barreira_energia; }
void ConstrutorEnergia::recarregar_barreira(int quantidade) {
    barreira_energia += quantidade;
    if (barreira_energia > 100) barreira_energia = 100;
}

} // namespace RpgGame
