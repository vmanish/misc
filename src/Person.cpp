#include "Person.hpp"

void Person::getPerson() {
    cout << "Name? ";
    cin >> data->name;

    cout << "Age? ";
    while (!(cin >> data->age)) {
        cout << "Invalid age. Enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Likes cake or cookie? ";
    cin >> data->cake_or_cookie;
}

void Person::buildTeam(unique_ptr<Person>& team) {
    char opt;
    do {
        cout << "Enter person details:" << endl;
        auto p = make_unique<Person>("", 0, "");
        p->getPerson();

        // Prepend to the team
        p->next = move(team);
        team = move(p);

        // Done?
        cout << "Are there more mates? (y/n): ";
        cin >> opt;
        cout << endl;
    } while (opt != 'n' && opt != 'N');
}

void Person::showTeam(const unique_ptr<Person>& team) {
    if (!team) {
        cout << "Team is empty" << endl;
        return;
    }
    for (Person* pp = team.get(); pp != nullptr; pp = pp->next.get()) {
        cout << "name: " << pp->data->name
             << " age: " << pp->data->age
             << " choice: " << pp->data->cake_or_cookie << endl;
    }
}

unique_ptr<Person> Person::sortByAge(const unique_ptr<Person>& team) {
    if (!team || !team->next) {
        // Return a copy of the single node or nullptr for an empty list
        return team ? make_unique<Person>(team->data) : nullptr;
    }

    unique_ptr<Person> sorted = nullptr;

    for (Person* current = team.get(); current != nullptr; current = current->next.get()) {
        // Create a new node for the current data
        auto node = make_unique<Person>(current->data);

        // Insert node into the sorted list
        if (!sorted || node->data->age < sorted->data->age) {
            // Insert at the beginning
            node->next = move(sorted);
            sorted = move(node);
        } else {
            // Find the correct insertion point
            Person* prev = sorted.get();
            while (prev->next && prev->next->data->age <= node->data->age) {
                prev = prev->next.get();
            }
            // Insert after prev
            node->next = move(prev->next);
            prev->next = move(node);
        }
    }

    return sorted;
}