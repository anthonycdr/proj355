
#ifndef NETWORK_H
#define NETWORK_H

#include "person.h"
#include "date.h"
// You may need to add more libraries 
#include <stdlib.h>
#include <string>
class Network{

    private:
        Person* head;
        Person* tail;
        int count; 
        Person* search(Person* searchEntry);
        Person* search(std::string fname, std::string lname);

    public:
        Network();
        Network(std::string fileName);
        ~Network();
        void loadDB(std::string filename); 
        void saveDB(std::string filename);
        void printDB();
        void push_front(Person* newEntry);
        void push_back(Person* newEntry);
        bool remove(std::string fname, std::string lname);
        void showMenu();
     
};

#endif
