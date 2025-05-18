#ifndef SORTSTRATEGY_HPP
#define SORTSTRATEGY_HPP

#include "Person.hpp"
#include <memory>

class SortStrategy {
public:
    virtual ~SortStrategy() = default;

    // Pure virtual function for sorting
    virtual std::unique_ptr<Person> sort(const std::unique_ptr<Person>& team) const = 0;
};

#endif // SORTSTRATEGY_HPP