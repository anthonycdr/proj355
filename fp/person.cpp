#include "person.h"
#include "misc.h"
#include <iostream>
#include <utility>
#include <sstream>
using namespace std;

Person::Person(){
    // I'm already done! 
    set_person();
}


Person::~Person(){
    delete birthdate;
    delete email;
    delete phone;
    // Fields like college, major, interests will be handled automatically
}

Person::Person(string f_name, string l_name, string birthdate, string email, string phone){
    // Existing constructor
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
    
    // Initialize new fields with default values
    this->college = "";
    this->major = "";
    // interests vector is already empty by default
}

// New constructor with additional parameters
Person::Person(string f_name, string l_name, string birthdate, string email, string phone,
       string college, string major, const vector<string>& interests){
    
    // Reuse existing constructor initialization
    Person(f_name, l_name, birthdate, email, phone);
    
    // Set the new fields
    this->college = college;
    this->major = major;
    this->interests = interests;
}

Person::Person(string filename){
    set_person(filename);
}


void Person::set_person(){
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    
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
    getline(cin, type);
    
    cout << "Email address: ";
    getline(cin, temp);
    email = new Email(type, temp);

    cout << "Type of phone number: ";
    getline(cin, type);
    cout << "Phone number: ";
    getline(cin, temp);
    phone = new Phone(type, temp);
    
    // Prompt for new information
    cout << "College (leave blank if none): ";
    getline(cin, college);
    
    cout << "Major (leave blank if none): ";
    getline(cin, major);
    
    cout << "Interests (comma separated, leave blank if none): ";
    string interests_str;
    getline(cin, interests_str);
    
    // Parse interests from comma-separated string
    interests.clear();
    stringstream ss(interests_str);
    string interest;
    while(getline(ss, interest, ',')) {
        // Trim leading/trailing spaces
        size_t start = interest.find_first_not_of(" \t");
        size_t end = interest.find_last_not_of(" \t");
        if (start != string::npos && end != string::npos) {
            interest = interest.substr(start, end - start + 1);
            if (!interest.empty()) {
                interests.push_back(interest);
            }
        }
    }
}


void Person::set_person(string filename){
    // reads a Person from a file
    // Look at person_template files as examples.     
    // Phone number in files can have '-' or not.
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
    string myphone, mymail;
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
    
    // Try to read new fields if they exist in the file
    college = "";
    major = "";
    interests.clear();
    
    // Read college if available
    if (getline(infile, fileline) && fileline.compare(0, 20, "--------------------") != 0) {
        college = fileline;
        
        // Read major if available
        if (getline(infile, fileline) && fileline.compare(0, 20, "--------------------") != 0) {
            major = fileline;
            
            // Read interests if available
            if (getline(infile, fileline) && fileline.compare(0, 20, "--------------------") != 0) {
                stringstream ss(fileline);
                string interest;
                while(getline(ss, interest, ',')) {
                    // Trim leading/trailing spaces
                    size_t start = interest.find_first_not_of(" \t");
                    size_t end = interest.find_last_not_of(" \t");
                    if (start != string::npos && end != string::npos) {
                        interest = interest.substr(start, end - start + 1);
                        if (!interest.empty()) {
                            interests.push_back(interest);
                        }
                    }
                }
            }
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
    // Modified to include new fields
    cout << l_name <<", " << f_name << endl;
    birthdate->print_date("Month D, YYYY");
    cout << "Phone ";
    phone->print();
    cout << "Email ";
    email->print();
    
    // Print new fields if they're not empty
    if (!college.empty()) {
        cout << "College: " << college << endl;
    }
    if (!major.empty()) {
        cout << "Major: " << major << endl;
    }
    if (!interests.empty()) {
        cout << "Interests: ";
        for (size_t i = 0; i < interests.size(); i++) {
            cout << interests[i];
            if (i < interests.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    
    // Print friends
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
