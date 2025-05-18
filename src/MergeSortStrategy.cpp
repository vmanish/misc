#include "MergeSortStrategy.hpp"

std::unique_ptr<Person> MergeSortStrategy::sort(const std::unique_ptr<Person>& team) const {
    if (!team || !team->next) {
        return team ? std::make_unique<Person>(team->data) : nullptr;
    }
    return mergeSort(std::make_unique<Person>(*team));
}

std::unique_ptr<Person> MergeSortStrategy::mergeSort(std::unique_ptr<Person> head) const {
    if (!head || !head->next) {
        return head;
    }

    auto middle = split(head);
    auto left = mergeSort(std::move(head));
    auto right = mergeSort(std::move(middle));

    return merge(std::move(left), std::move(right));
}

std::unique_ptr<Person> MergeSortStrategy::merge(std::unique_ptr<Person> left, std::unique_ptr<Person> right) const {
    std::unique_ptr<Person> result = nullptr;
    Person* tail = nullptr;

    while (left && right) {
        std::unique_ptr<Person> node;
        if (left->data->age <= right->data->age) {
            node = std::move(left);
            left = std::move(node->next);
        } else {
            node = std::move(right);
            right = std::move(node->next);
        }

        if (!result) {
            result = std::move(node);
            tail = result.get();
        } else {
            tail->next = std::move(node);
            tail = tail->next.get();
        }
    }

    if (left) {
        tail->next = std::move(left);
    } else if (right) {
        tail->next = std::move(right);
    }

    return result;
}

std::unique_ptr<Person> MergeSortStrategy::split(std::unique_ptr<Person>& head) const {
    if (!head || !head->next) {
        return nullptr;
    }

    Person* slow = head.get();
    Person* fast = head->next.get();

    while (fast && fast->next) {
        slow = slow->next.get();
        fast = fast->next->next.get();
    }

    auto middle = std::move(slow->next);
    slow->next = nullptr;

    return middle;
}