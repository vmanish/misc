#ifndef MERGESORTSTRATEGY_HPP
#define MERGESORTSTRATEGY_HPP

#include "SortStrategy.hpp"

class MergeSortStrategy : public SortStrategy {
public:
    MergeSortStrategy() = default;
    ~MergeSortStrategy() override = default;

    std::unique_ptr<Person> sort(const std::unique_ptr<Person>& team) const override;

private:
    std::unique_ptr<Person> mergeSort(std::unique_ptr<Person> head) const;
    std::unique_ptr<Person> merge(std::unique_ptr<Person> left, std::unique_ptr<Person> right) const;
    std::unique_ptr<Person> split(std::unique_ptr<Person>& head) const;
};

#endif // MERGESORTSTRATEGY_HPP