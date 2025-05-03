#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>

/* 
Class attribute:
type would return the name you want to give to this contact. "Work", "Home" and "Office"
get_contact would return the string of email/ phone 
set_contact would prompt the user to enter their contact 
*/
class Contact {
protected:
	std::string type;        
public:
	virtual void print() = 0;
    virtual std::string get_contact(std::string style="full") = 0;
	virtual void set_contact() = 0;
};

class Email: public Contact{
private:
    std::string email_addr;
public:
    Email(std::string type, std::string email_addr);  
    void print() override;                  
    std::string get_contact(std::string style = "full") override; 
    void set_contact() override;
};  

class Phone: public Contact{
private:
    std::string phone_num;
public:
    Phone(std::string type, std::string phone_number);  
    void print() override;                   
    std::string get_contact(std::string style = "full") override; 
    void set_contact() override;        
};

// New contact types for college, major, and state
class College: public Contact{
private:
    std::string college_name;
public:
    College(std::string type, std::string college_name);
    College() { type = "Attended"; college_name = ""; }
    void print() override;                  
    std::string get_contact(std::string style = "full") override; 
    void set_contact() override;
};

class Major: public Contact{
private:
    std::string major_name;
public:
    Major(std::string type, std::string major_name);
    Major() { type = "Field"; major_name = ""; }
    void print() override;                  
    std::string get_contact(std::string style = "full") override; 
    void set_contact() override;
};

class State: public Contact{
private:
    std::string state_code;
public:
    State(std::string type, std::string state_code);
    State() { type = "Residence"; state_code = ""; }
    void print() override;                  
    std::string get_contact(std::string style = "full") override; 
    void set_contact() override;
};

#endif
