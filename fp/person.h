#ifndef PERSON_H
#define PERSON_H

#include "date.h"
#include "contact.h"
#include "fstream"
#include <string>
#include <vector>

class Person{
    friend class Network;

private:
    std::string f_name;
    std::string l_name;
    Date *birthdate;
    Email *email;
    Phone *phone;
    // New additional information
    std::string college;
    std::string major;
    std::string state;
    // the following to attributes are used in the linked list.
    Person* next;
    Person* prev;
    std::vector<Person*> myfriends;

public: 
    Person();
    ~Person();
    Person(std::string filename);
    Person(std::string f_name, std::string l_name, std::string birthdate, std::string email, std::string phone);
    Person(std::string f_name, std::string l_name, std::string birthdate, std::string email, std::string phone,
           std::string college, std::string major, std::string state);
    void print_person();
    void set_person();
    void set_person(std::string filename);
    bool operator==(const Person& rhs);
    bool operator!=(const Person& rhs);
    void makeFriend(Person* newfriend);
    void print_friends();
    
    // Getters for new fields
    std::string get_college() const { return college; }
    std::string get_major() const { return major; }
    std::string get_state() const { return state; }
    
    // Setters for new fields
    void set_college(const std::string& college) { this->college = college; }
    void set_major(const std::string& major) { this->major = major; }
    void set_state(const std::string& state) { this->state = state; }
};

#endif
