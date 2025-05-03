
#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>
// TODO: You may need to add other libraries here!


/* 
Class attribute:
type would return the name you want to give to this contact. "Work", "Home" and "Office"
get_contact would return the string of email/ phone 
set_contact would prompt the user to enter their contact 
example print() output:
    Email::print() example: "Email (Work): julia@wh.com"
    Phone::print() example: "Phone (Home): 310-192-2011"
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
    //other attributes
public:
    Email(std::string type, std::string email_addr);  
    void print() override;                  
    std::string get_contact(std::string style = "full") override; 
    void set_contact() override;
};  

class Phone: public Contact{
private:
    std::string phone_num;
    //other attributes 
public:
    Phone(std::string type, std::string phone_number);  
    void print() override;                   
    std::string get_contact(std::string style = "full") override; 
    void set_contact() override;        
};

#endif
