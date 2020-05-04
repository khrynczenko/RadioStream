#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include "Observer.hpp"
#include <vector>
#include <memory>

class Subject {
   public:
    void attach(std::shared_ptr<Observer> observer);
    void notify(const std::any& data, radiostream::Event e);

   private:
    std::vector<std::shared_ptr<Observer>> observers_;
};

#endif
