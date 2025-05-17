      void getPerson() {
        cout << "Name? "; cin >> name; cout << endl;
        cout << "Age? ";
        while (!(cin >> age)) {
            cout << "Invalid age. Enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << endl;
        cout << "Likes cake or cookie? "; cin >> cake_or_cookie; cout << endl;
    }
     
     
     
     
     static void buildTeam(unique_ptr<Person>& team) {
        char opt;
        do {
            cout << "Enter person details:" << endl;
            auto p = make_unique<Person>();
            p->getPerson();

            // Prepend to the team
            p->next = move(team);
            team = move(p);

            // Done?
            cout << "Are there more? (y/n): ";
            cin >> opt;
            cout << endl;
        } while (opt != 'n' && opt != 'N');
    }

    static void showTeam(const unique_ptr<Person>& team) {
        if (!team) {
            cout << "Team is empty" << endl;
            return;
        }
        for (Person* pp = team.get(); pp != nullptr; pp = pp->next.get()) {
            cout << "name:" << pp->name << " age:" << pp->age << " choice:" << pp->cake_or_cookie << endl;
        }
    }
 
 
 static void sortByAge(unique_ptr<Person>& team) {
        if (!team || !team->next) {
            return; // Empty or single-node list is sorted
        }

        unique_ptr<Person> sorted = nullptr; // New sorted list
        unique_ptr<Person> current = move(team); // Original list

        while (current) {
            // Take the next node
            unique_ptr<Person> node = move(current);
            current = move(node->next);

            // Insert node into sorted list
            if (!sorted || node->age < sorted->age) {
                // Insert at the beginning
                node->next = move(sorted);
                sorted = move(node);
            } else {
                // Find insertion point
                Person* prev = sorted.get();
                while (prev->next && prev->next->age <= node->age) {
                    prev = prev->next.get();
                }
                // Insert after prev
                node->next = move(prev->next);
                prev->next = move(node);
            }
        }

        team = move(sorted);
    }