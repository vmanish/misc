#include "Person.hpp"

int main() {
    unique_ptr<Person> team = nullptr;
    unique_ptr<Person> sortedTeam = nullptr;
    Person::buildTeam(team);
    cout << "Original team:" << endl;
    Person::showTeam(team);
    sortedTeam = Person::sortByAge(team);
    cout << "Sorted team by age:" << endl;
    Person::showTeam(sortedTeam);
    return 0;
}