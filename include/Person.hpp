#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
#include <limits>
#include <utility>
#include <memory>
#include <string>

using namespace std;


class PersonData {
    public:
        std::string name;
        int age;
        std::string cake_or_cookie;
    
        PersonData(const std::string& name, int age, const std::string& cake_or_cookie)
            : name(name), age(age), cake_or_cookie(cake_or_cookie) {}
    };

class Person {
public:
    std::shared_ptr<PersonData> data;
    std::unique_ptr<Person> next;

    Person(const std::string& name, int age, const std::string& cake_or_cookie)
        : data(std::make_shared<PersonData>(name, age, cake_or_cookie)), next(nullptr) {}

    // Constructor to initialize Person with shared_ptr<PersonData>
    Person(shared_ptr<PersonData> data) : data(data), next(nullptr) {}

    void getPerson();
    static void buildTeam(std::unique_ptr<Person>& team);
    static void showTeam(const std::unique_ptr<Person>& team);
    static std::unique_ptr<Person> sortByAge(const std::unique_ptr<Person>& team);
};

#endif // PERSON_HPP