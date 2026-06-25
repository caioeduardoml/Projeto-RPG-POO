#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <string>
#include <vector>
#include <algorithm>

namespace RpgGame {

class CombateObserver {
public:
    virtual ~CombateObserver() = default;
    virtual void aoAcontecerEvento(const std::string& log) = 0;
};

class Subject {
private:
    std::vector<CombateObserver*> observers;
public:
    virtual ~Subject() = default;
    void registrarObserver(CombateObserver* obs) {
        if (obs) {
            observers.push_back(obs);
        }
    }
    void removerObserver(CombateObserver* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }
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
