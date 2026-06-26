#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <string>
#include <vector>
#include <algorithm>

namespace RpgGame {

class CombateObserver {
public:
    virtual ~CombateObserver() = default;
    /**
     * @brief Método chamado quando um evento notificado pelo Subject ocorre.
     * @param log Mensagem descritiva do evento.
     */
    virtual void aoAcontecerEvento(const std::string& log) = 0;
};

class Subject {
private:
    std::vector<CombateObserver*> observers;
public:
    virtual ~Subject() = default;

    /**
     * @brief Registra um novo observer na lista.
     * @param obs Ponteiro para o observer.
     */
    void registrarObserver(CombateObserver* obs) {
        if (obs) {
            observers.push_back(obs);
        }
    }

    /**
     * @brief Remove um observer específico da lista.
     * @param obs Ponteiro para o observer a ser removido.
     */
    void removerObserver(CombateObserver* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

    /**
     * @brief Notifica todos os observers registrados sobre um evento.
     * @param log Mensagem do evento.
     */
    void notificar(const std::string& log) {
        for (auto* obs : observers) {
            if (obs) {
                obs->aoAcontecerEvento(log);
            }
        }
    }
};

} // namespace RpgGame

#endif // OBSERVER_HPP
