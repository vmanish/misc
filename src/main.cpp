int main() {
    unique_ptr<Person> team = nullptr;
    Person::buildTeam(team);
    cout << "Original team:" << endl;
    Person::showTeam(team);
    Person::sortByAge(team);
    cout << "Sorted team by age:" << endl;
    Person::showTeam(team);
    return 0;
}