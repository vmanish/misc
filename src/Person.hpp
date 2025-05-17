#include <iostream>
#include <string>
#include <memory>
#include <limits>

using namespace std;

class Person {
public:
    Person() : name("joe"), age(10), cake_or_cookie("cake") {}

    Person(const string& n, int a, const string& c) : name(n), age(a), cake_or_cookie(c) {}

    void getPerson();
    static void buildTeam(unique_ptr<Person>& team);

    static void showTeam(const unique_ptr<Person>& team) ;
    static void sortByAge(unique_ptr<Person>& team) ;

private:
    string name;
    int age;
    string cake_or_cookie;
    unique_ptr<Person> next;
};

