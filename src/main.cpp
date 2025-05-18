#include "Person.hpp"
#include "MergeSortStrategy.hpp"
#include "InsertionSortStrategy.hpp"

int main() {
    unique_ptr<Person> team = nullptr;
    Person::buildTeam(team);

    cout << "Original team:" << endl;
    Person::showTeam(team);

    // Configure sorting strategy
    unique_ptr<SortStrategy> sortStrategy = make_unique<MergeSortStrategy>();
    // Uncomment the following line to use InsertionSortStrategy instead
    // unique_ptr<SortStrategy> sortStrategy = make_unique<InsertionSortStrategy>();

    auto sortedTeam = sortStrategy->sort(team);

    cout << "Sorted team by age:" << endl;
    Person::showTeam(sortedTeam);

    return 0;
}