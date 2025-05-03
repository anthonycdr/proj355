#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>

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

// New classes
class College: public Contact{
private:
    std::string college_name;
public:
    College(std::string college_name);  
    College() { college_name = ""; }
    void print() override;                  
    std::string get_contact(std::string style = "full") override; 
    void set_contact() override;
};

class Major: public Contact{
private:
    std::string major_name;
public:
    Major(std::string major_name);  
    Major() { major_name = ""; }
    void print() override;                  
    std::string get_contact(std::string style = "full") override; 
    void set_contact() override;
};

class State: public Contact{
private:
    std::string state_code;
public:
    State(std::string state_code);  
    State() { state_code = ""; }
    void print() override;                  
    std::string get_contact(std::string style = "full") override; 
    void set_contact() override;
};

#endif
