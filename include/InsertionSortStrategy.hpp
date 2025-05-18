#ifndef INSERTIONSORTSTRATEGY_HPP
#define INSERTIONSORTSTRATEGY_HPP

#include "SortStrategy.hpp"

class InsertionSortStrategy : public SortStrategy {
public:
    std::unique_ptr<Person> sort(const std::unique_ptr<Person>& team) const override;
};

#endif // INSERTIONSORTSTRATEGY_HPP