#include "person.h"
#include "misc.h"
#include <iostream>
#include <utility>
using namespace std;

Person::Person(){
    // I'm already done! 
    set_person();
}


Person::~Person(){
    delete birthdate;
    delete email;
    delete phone;
    delete college;
    delete major;
    delete state;
    // TODO: complete the method!
}

Person::Person(string f_name, string l_name, string birthdate, string email, string phone){
    // TODO: Complete this method!
    // phone and email strings are in full version
    string type;
    this->f_name = f_name;
    this->l_name = l_name;
    this->birthdate = new Date(birthdate);
    for(int i = 0; i < email.length(); i++){
        if(email[i] == ')'){
            type = email.substr(1, i-1);
            email = email.substr(i+2);
            break;
        }
    }
    this->email = new Email(type, email);
    for(int i = 0; i < phone.length(); i++){
        if(phone[i] == ')'){
            type = phone.substr(1, i-1);
            phone = phone.substr(i+2);
            break;
        }
    }
    this->phone = new Phone(type, phone);
    
    // Initialize new fields with empty values
    this->college = new College();
    this->major = new Major();
    this->state = new State();
}

// New constructor with additional fields
Person::Person(string f_name, string l_name, string birthdate, string email, string phone,
               string college_name, string major_name, string state_code){
    string type;
    this->f_name = f_name;
    this->l_name = l_name;
    this->birthdate = new Date(birthdate);
    
    for(int i = 0; i < email.length(); i++){
        if(email[i] == ')'){
            type = email.substr(1, i-1);
            email = email.substr(i+2);
            break;
        }
    }
    this->email = new Email(type, email);
    
    for(int i = 0; i < phone.length(); i++){
        if(phone[i] == ')'){
            type = phone.substr(1, i-1);
            phone = phone.substr(i+2);
            break;
        }
    }
    this->phone = new Phone(type, phone);
    
    // Set the additional fields
    this->college = new College(college_name);
    this->major = new Major(major_name);
    this->state = new State(state_code);
}

Person::Person(string filename){
    set_person(filename);
}


void Person::set_person(){
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!
    
    string temp;
    string type;

    cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    getline(cin,f_name);

    cout << "Last Name: ";
    getline(cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    getline(cin,temp);
    // pay attention to how we passed argument to the constructor of a new object created dynamically using new command
    birthdate = new Date(temp); 

    cout << "Type of email address: ";
    // code here
    getline(cin, type);
    
    cout << "Email address: ";
    // code here
    getline(cin, temp);
    email = new Email(type, temp);

    cout << "Type of phone number: ";
    // code here
    getline(cin, type);
    cout << "Phone number: ";
    // code here
    // code here
    getline(cin, temp);
    phone = new Phone(type, temp);
    
    // New prompts for additional fields
    college = new College();
    cout << "College: ";
    college->set_contact();
    
    major = new Major();
    cout << "Major: ";
    major->set_contact();
    
    state = new State();
    cout << "State: ";
    state->set_contact();
}


void Person::set_person(string filename){
    // reads a Person from a file
    // Look at person_template files as examples.     
    // Phone number in files can have '-' or not.
    // TODO: Complete this method!
    ifstream infile(filename);
    if (!infile.is_open()){
        cerr << "Error opening file!" << endl;
        return;
    }
    string type, fileline;
    getline(infile, fileline);
    f_name = fileline;
    getline(infile, fileline);
    l_name = fileline;
    getline(infile, fileline);
    birthdate = new Date(fileline);
    getline(infile,fileline);
    string myphone, mymail, mycollege, mymajor, mystate;
    for(int i = 0; i < fileline.length(); i++){
        if(fileline[i] == ')'){
            type = fileline.substr(1, i-1);
            myphone = fileline.substr(i+2);
            break;
        }
    }
    phone = new Phone(type, myphone);
    getline(infile, fileline);
    for(int i = 0; i < fileline.length(); i++){
        if(fileline[i] == ')'){
            type = fileline.substr(1, i-1);
            mymail = fileline.substr(i+2);
            break;
        }
    }
    email = new Email(type, mymail);
    
    // Initialize college, major, and state with default values
    college = new College();
    major = new Major();
    state = new State();
    
    // Try to read the additional fields if they exist
    while(getline(infile, fileline) && fileline.compare(0, 20, "--------------------") != 0) {
        if (fileline.find("College: ") == 0) {
            mycollege = fileline.substr(9); // Skip "College: "
            college = new College(mycollege);
        } 
        else if (fileline.find("Major: ") == 0) {
            mymajor = fileline.substr(7); // Skip "Major: "
            major = new Major(mymajor);
        } 
        else if (fileline.find("State: ") == 0) {
            mystate = fileline.substr(7); // Skip "State: "
            state = new State(mystate);
        }
    }
}
   

bool Person::operator==(const Person& rhs){
    // TODO: Complete this method!
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)
    return (f_name == rhs.f_name && l_name == rhs.l_name && birthdate->get_month() == rhs.birthdate->get_month() && birthdate->get_day() == rhs.birthdate->get_day() && birthdate->get_year() == rhs.birthdate->get_year());
}

bool Person::operator!=(const Person& rhs){ 
    // TODO: Complete this method!
    return !(*this == rhs);
}


void Person::print_person(){
    // Already implemented for you! Do not change!
    cout << l_name <<", " << f_name << endl;
    birthdate->print_date("Month D, YYYY");
    cout << "Phone ";
    phone->print();
    cout << "Email ";
    email->print();
    
    // Print additional fields if they are not empty
    cout << "College ";
    college->print();
    cout << "Major ";
    major->print();
    cout << "State ";
    state->print();
    
    for (int i = 0; i < myfriends.size(); i++){
        cout << codeName(myfriends[i]->f_name, myfriends[i]->l_name) << " (" << myfriends[i]->f_name << " " << myfriends[i]->l_name << ")" << endl;
    }
}

void Person::makeFriend(Person* newfriend){
    for (int i =0; i<myfriends.size(); i++){
        if (newfriend==myfriends[i] || newfriend == nullptr){
            return;
        }
    }
    myfriends.push_back(newfriend);
}

void Person::print_friends (){
    vector<pair<string,Person*>> person_and_code;
    for (int i =0 ;i < myfriends.size(); i++){
        string individual_code = codeName (myfriends[i]->f_name, myfriends[i]->l_name);
        person_and_code.push_back({individual_code, myfriends[i]});
    }

    if (person_and_code.size()>1){ //only sort if there is more than one friend
        for (int i = 0; i < person_and_code.size()-1; i++){ //selection sort
            int current_min = i;
            for (int j = i+1; j<person_and_code.size(); j++){ 
                if (person_and_code[current_min].first.substr(0,2) > person_and_code[j].first.substr(0,2)){
                    current_min = j;
                }
            }
            pair<string,Person*> temp = person_and_code[current_min];
            person_and_code[current_min] = person_and_code[i];
            person_and_code[i] = temp;
        }

    }

    cout << f_name << ", " << l_name << endl;
    cout << "--------------------------------" << endl;

    for (int i =0; i<person_and_code.size(); i++){
        cout << person_and_code[i].second->f_name << ", " << person_and_code[i].second->l_name << endl;
    }
}
