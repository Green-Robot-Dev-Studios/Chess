#include "subject.hpp"

void Subject::notifyObservers() {
    for(auto p: observers) {
        p->notify();
    }
}

void Subject::attach(std::shared_ptr<Observer> o) {
    observers.push_back(o);
}

Subject::~Subject() {}