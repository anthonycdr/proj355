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
    std::vector<std::string> interests;
    // the following to attributes are used in the linked list.
    Person* next;
    Person* prev;
    std::vector<Person*> myfriends;

public: 
    Person();
    ~Person();
    Person(std::string filename);
    Person(std::string f_name, std::string l_name, std::string birthdate, std::string email, std::string phone);
    // New constructor with additional parameters
    Person(std::string f_name, std::string l_name, std::string birthdate, std::string email, std::string phone,
           std::string college, std::string major, const std::vector<std::string>& interests);
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
    const std::vector<std::string>& get_interests() const { return interests; }
    
    // Setters for new fields
    void set_college(const std::string& college) { this->college = college; }
    void set_major(const std::string& major) { this->major = major; }
    void add_interest(const std::string& interest) { interests.push_back(interest); }
    void set_interests(const std::vector<std::string>& interests) { this->interests = interests; }
};

#endif
