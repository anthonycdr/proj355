
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
    // the following to attributes are used in the linked list.
    Person* next;
    Person* prev;
    std::vector<Person*> myfriends;

public: 
    Person();
    ~Person();
    Person(std::string filename);
    Person(std::string f_name, std::string l_name, std::string birthdate, std::string email, std::string phone);
	void print_person();
	void set_person();
	void set_person(std::string filename);
    bool operator==(const Person& rhs);
    bool operator!=(const Person& rhs);
    void makeFriend(Person* newfriend);
    void print_friends();
};


#endif
