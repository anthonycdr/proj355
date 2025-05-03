#include "contact.h"
// TODO: Add needed libraries! 

using namespace std;

Email::Email(string type, string email_addr){
    // TODO: Complete me!
    this->type = type;
    this->email_addr = email_addr;
}


void Email::set_contact(){
    // TODO: Do not change the prompts!
	
    cout << "Enter the type of email address: ";
    cin >> type;
    cout << "Enter email address: ";
    cin >> email_addr;
}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    if (style=="full")
	    return "(" + type + "): " + email_addr;
    else 
        return email_addr;
}


void Email::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}


Phone::Phone(string type, string num){
    // TODO: It is possible that num includes "-" or not, manage it!
    // TODO: Complete this method!
    // Note: We don't want to use C++11! stol is not valid!
    this->type = type;
    phone_num = "";

    for (int i = 0; i < num.length(); i++) {
        char digit = num[i];
        if (digit != '-') {
            this->phone_num += digit;
        }
    }
}


void Phone::set_contact(){
    // TODO: Complete this method
    // Use the same prompts as given!
	cout <<"Enter the type of phone number: ";
    cin >> type;
	cout << "Enter the phone number: ";
    cin >> phone_num;
}


string Phone::get_contact(string style){
    // TODO: Complete this method, get hint from Email 
    if (style=="full"){
        return "(" + type + "): " + phone_num.substr(0,3) + "-" + phone_num.substr(3,3) + "-" +
            phone_num.substr(6,4); 
    }
    else 
        return phone_num.substr(0,3) + "-" + phone_num.substr(3,3) + "-" + phone_num.substr(6,4); 
}


void Phone::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}

// Implementation for College Contact
College::College(string college_name){
    this->type = "College";
    this->college_name = college_name;
}

void College::set_contact(){
    cout << "Enter college name: ";
    cin.ignore(); // To handle previous newline
    getline(cin, college_name);
}

string College::get_contact(string style){
    if (style=="full")
	    return college_name;
    else 
        return college_name;
}

void College::print(){
	cout << "College: " << get_contact() << endl;
}

// Implementation for Major Contact
Major::Major(string major_name){
    this->type = "Major";
    this->major_name = major_name;
}

void Major::set_contact(){
    cout << "Enter major name: ";
    cin.ignore(); // To handle previous newline
    getline(cin, major_name);
}

string Major::get_contact(string style){
    if (style=="full")
	    return major_name;
    else 
        return major_name;
}

void Major::print(){
	cout << "Major: " << get_contact() << endl;
}

// Implementation for State Contact
State::State(string state_code){
    this->type = "State";
    this->state_code = state_code;
}

void State::set_contact(){
    cout << "Enter state code: ";
    cin >> state_code;
}

string State::get_contact(string style){
    if (style=="full")
	    return state_code;
    else 
        return state_code;
}

void State::print(){
	cout << "State: " << get_contact() << endl;
}
