#include "InsertionSortStrategy.hpp"

std::unique_ptr<Person> InsertionSortStrategy::sort(const std::unique_ptr<Person>& team) const {
    if (!team || !team->next) {
        return team ? std::make_unique<Person>(team->data) : nullptr;
    }

    std::unique_ptr<Person> sorted = nullptr;

    for (Person* current = team.get(); current != nullptr; current = current->next.get()) {
        auto node = std::make_unique<Person>(current->data);

        if (!sorted || node->data->age < sorted->data->age) {
            node->next = std::move(sorted);
            sorted = std::move(node);
        } else {
            Person* prev = sorted.get();
            while (prev->next && prev->next->data->age <= node->data->age) {
                prev = prev->next.get();
            }
            node->next = std::move(prev->next);
            prev->next = std::move(node);
        }
    }

    return sorted;
}