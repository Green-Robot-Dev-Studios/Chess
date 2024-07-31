#include "subject.hpp"

void Subject::notifyObservers() {
    for(auto p: observers) {
        if(auto observer = p.lock()) {
            observer->notify();
        }
    }
}

void Subject::attach(std::shared_ptr<Observer> o) {
    observers.emplace_back(o);
}

Subject::~Subject() {}