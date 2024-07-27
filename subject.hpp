#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.hpp"
#include <memory>
#include <vector>

class Subject {
    std::vector<std::shared_ptr<Observer>> observers;
public:
    void notifyObservers();
    void attach(std::shared_ptr<Observer> o);
    virtual ~Subject() = 0;
};

#endif
