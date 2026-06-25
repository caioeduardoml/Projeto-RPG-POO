#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace RpgGame {

/**
 * @brief Exceção base para o jogo RPG Manager.
 */
class RPGException : public std::runtime_error {
public:
    explicit RPGException(const std::string& msg) : std::runtime_error(msg) {}
};

/**
 * @brief Exceção lançada para falhas na criação ou regras de personagens.
 */
class PersonagemException : public RPGException {
public:
    explicit PersonagemException(const std::string& msg) : RPGException("Erro em Personagem: " + msg) {}
};

/**
 * @brief Exceção lançada para falhas no uso de habilidades.
 */
class HabilidadeException : public RPGException {
public:
    explicit HabilidadeException(const std::string& msg) : RPGException("Erro em Habilidade: " + msg) {}
};

/**
 * @brief Exceção lançada para restrições e falhas de inventário (ex: peso, classe).
 */
class InventarioException : public RPGException {
public:
    explicit InventarioException(const std::string& msg) : RPGException("Erro no Inventario: " + msg) {}
};

/**
 * @brief Exceção lançada para ações inválidas no combate.
 */
class CombateException : public RPGException {
public:
    explicit CombateException(const std::string& msg) : RPGException("Erro no Combate: " + msg) {}
};

/**
 * @brief Exceção lançada para falhas na leitura ou salvamento de arquivos.
 */
class PersistenciaException : public RPGException {
public:
    explicit PersistenciaException(const std::string& msg) : RPGException("Erro de Persistencia: " + msg) {}
};

} // namespace RpgGame

#endif // EXCEPTIONS_HPP
