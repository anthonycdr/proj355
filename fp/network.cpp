
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <regex>
#include <cstdlib> 

using namespace std;

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // TODO: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
    loadDB(fileName);

}

Network::~Network(){ 
	Person* current = head;
        while (current!=nullptr){
            Person* temp = current;
            current = current -> next;
            delete temp;
            }
        head = nullptr;
        tail = nullptr;
        count = 0;
}

Person* Network::search(Person* searchEntry){
    // Searches the Network for searchEntry
    // if found, returns a pointer to it, else returns NULL
    // TODO: Complete this method
    Person* traverse = head;
    if (head==nullptr){
        return nullptr;
    }
    while (*traverse!=*searchEntry){
        traverse = traverse->next;
        if (traverse == nullptr){
            return nullptr;
        }
    }
    return traverse;

}


Person* Network::search(string fname, string lname){
    // New == for Person, only based on fname and lname
    // if found, returns a pointer to it, else returns NULL
    // TODO: Complete this method
    // Note: two ways to implement this, 1st making a new Person with fname and lname and and using search(Person*), 2nd using fname and lname directly. 
    Person* traverse = head;
    if (head==nullptr){
        return nullptr;
    }
    while (traverse->f_name!=fname || traverse->l_name!=lname){
        traverse = traverse->next;
        if (traverse == nullptr){
            return nullptr;
        }
    }
    return traverse;
}


void Network::loadDB(string filename){
    // TODO: Complete this method
    std::ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open the file!" << endl;
        return;
    }

    string fname, lname, bdate, email, phone; // Assuming these are the fields
    string buff;
    vector<vector<pair<string, string>>> People_friend_list; //since cant add the friends vector unless each Person is first initialized into network
    while (getline(file, fname)) {
        vector <pair<string,string>> temp;
        string divider;
        getline(file,lname);
        getline(file, bdate);
        getline(file, phone);
	    getline(file, email);
    
        while (getline(file, buff) && buff.compare(0,20, "--------------------") != 0){
            int index = 0;
            for (int i =0; i< buff.length(); i++){
                if (buff[i] == ','){
                    index = i;
                    break;
                }
            }
            string friend_first = buff.substr(0,index);
            string friend_last = buff.substr(index+1);
            temp.push_back({friend_first, friend_last});
        }
        Person* newPerson = new Person(fname, lname, bdate, email, phone);
        People_friend_list.push_back(temp);
        push_back(newPerson); // Add person to the network
    }
    file.close();
    Person* traverse = head;
    for (int i = 0; i<People_friend_list.size(); i++){
        vector <Person*> friends_vector;
        for (int j = 0 ; j<People_friend_list[i].size(); j++){
            Person* newFriend = search (People_friend_list[i][j].first, People_friend_list[i][j].second);
            if (newFriend!=nullptr){
                friends_vector.push_back(newFriend);
            }
        }
        traverse->myfriends = friends_vector;
        traverse = traverse->next;    
        }     
}

void Network::saveDB(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        return;
    }

    Person* ptr = head;
    while (ptr != NULL) {
        file << ptr->l_name << ", "<< ptr->f_name << endl;
        file << ptr->birthdate->get_month_name() << " "
             << ptr->birthdate->get_day() << ", "
             << ptr->birthdate->get_year() << endl;

	    file << "Phone " << ptr->phone->get_contact() << endl;
             
        file << "Email " << ptr->email->get_contact() << endl;

        for (int i = 0; i<ptr->myfriends.size(); i++){
            file << codeName(ptr->myfriends[i]->f_name, ptr->myfriends[i]->l_name) << " (" << ptr->myfriends[i]->f_name << " " << ptr->myfriends[i]->l_name << ")" << endl;
        }

        file << "--------------------" << endl;

        ptr = ptr->next;
    }

    file.close();
}


void Network::printDB(){
    // Leave me alone! I know how to print! 
    // Note: Notice that we don't need to update this even after adding to Personattributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of people: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}



void Network::push_front(Person* newEntry){
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Person* newEntry){
    // Adds a new Person (newEntry) to the back of LL
    // TODO: Complete this method
    newEntry->next = NULL;
    newEntry->prev = tail;

    if (tail != NULL)
        tail->next = newEntry;
    else
        head = newEntry;

    tail = newEntry;
    count++;
} 



bool Network::remove(string fname, string lname){
    // TODO: Complete this method
    Person* traverse = head;
    if (head==nullptr){
        return false;
    }
    while (traverse->f_name!=fname || traverse->l_name!=lname){
        traverse = traverse->next;
        if (traverse == nullptr){
            return false;
        }
    }
    Person* individual = head; //removing the selected individual from others friend vector
    for (int i = 0; i<count;i++){
        for (int j = 0; j<individual->myfriends.size(); j++){
            if (individual->myfriends[j]==traverse){
                individual->myfriends.erase(individual->myfriends.begin()+j);
                break;
            }
        }
        individual = individual->next;
    }


    if (traverse -> next == nullptr){ //deleting last element
        if (traverse -> prev == nullptr){ //if only one elem
            head = nullptr;
            tail = nullptr;
            delete traverse;
            return true;
        }
        ((traverse ->prev)->next) = nullptr;
        tail = traverse-> prev;
        delete traverse;
        return true;
    }
    if (traverse == head){ //for deleting head
        head = traverse -> next;
        head->prev = nullptr;
        delete traverse;
        return true;
    }
    (traverse -> prev)->next = traverse -> next;
    (traverse -> next)-> prev = traverse -> prev;
    delete traverse;
    return true;

}


void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Remove a person \n";
        cout << "5. Print people with last name  \n";
        cout << "6. Connect \n";
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            // TODO: Complete me!
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            // Save the network database into the file with the given name,
            // with each person saved in the format the save as printing out the person info,
            // and people are delimited similar to "networkDB.txt" format
            getline(cin, fileName);
            saveDB(fileName);
            ofstream check(fileName);
            if (check.is_open()) {
            	check.close();
                saveDB(fileName);
    		cout << "Network saved in " << fileName << endl;
} 		
	     else {
    		 cout << "Could not open the file: " << fileName << endl;
	}
           
        }
        else if (opt==2){
        	Person* current = head; // loading should erase all elements of current LL
        	while (current!=nullptr){
            		Person* temp = current;
            		current = current -> next;
            		delete temp;
            	}
        	head = nullptr;
        	tail = nullptr;
        	count = 0;
            // TODO: Complete me!
            cout << "Loading network database \n";
            // TODO: print all the files in this same directory that have "networkDB.txt" format
            system("ls > file_list.txt");
            ifstream infile("file_list.txt");
            regex match (".+\\.txt$");
            string file;
            while (getline (infile, file)){
            	if (file == "file_list.txt"){
            		continue;
            		}
            	if (regex_match(file, match)){
            	cout << file << endl;  
            	}
            }
            system("rm file_list.txt");
            infile.close();
            
            // print format: one filename one line.
            // This step just shows all the available .txt file to load.
            string filename;
            cout << "Enter the name of the load file: "; 
            cin >> filename;
            // If file with name FILENAME does not exist: 
            if (!(ifstream(filename))){
                cout << "File " << filename << " does not exist!" << endl;
            }
            else{
            	loadDB(filename);
                    // If file is loaded successfully, also print the count of people in it: 
                cout << "Network loaded from " << filename << " with " << count << " people \n";
            }
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            // Add a new Person ONLY if it does not exists!
            cout << "Adding a new person \n";

            Person* newp = new Person();

            Person* exists = search(newp);
            if (exists != NULL){
                delete newp;
            }
            else {
                push_front(newp); 
            }
        }
        else if (opt == 4){
            // TODO: Complete me!
            // if found, cout << "Remove Successful! \n";
            // if not found: cout << "Person not found! \n";
            string fi_name, la_name;
            cout << "Enter the first name to remove: " << endl;
            getline(cin, fi_name);
	    cout << "Enter the last name to remove: " << endl;
	    getline(cin, la_name);
            bool result = remove (fi_name, la_name);
            if (result){
                cout << "Remove Successful! \n";
                cout << "Removing a person \n";
                cout << "First name: " << fi_name << endl;
                cout << "Last name: " << la_name << endl;
            }
            else{
                cout << "Person not found! \n";
            }
        }
        else if (opt==5){
            // TODO: Complete me!
            // print the people with the given last name
            // if not found: cout << "Person not found! \n";
            cout << "Print people with last name \n";
            cout << "Last name: ";
            string la_name1;
            getline(cin,la_name1);

            bool found = false;
            Person* traverse = head;
            while(traverse != NULL){
                if (traverse->l_name == la_name1){
                    cout << traverse->f_name << endl;
                    cout << traverse->l_name << endl;
                    cout << traverse->birthdate->get_month() << "/" << traverse->birthdate->get_day() << "/" << traverse->birthdate->get_year() <<endl;
                    cout << traverse->email->get_contact() << endl;
                    cout << traverse -> phone->get_contact()<<endl;
                    cout << "--------------------" << endl;
                    found = true;
                }
                traverse = traverse->next;
            }
            if (found == false)
                cout << "Person not found! \n";

        }

        else if (opt==6){
            cout <<"Make friends:\n";
            cout <<"Person 1\n";
            cout << "First Name: ";
            string first, last;
            getline (cin, first);
            cout << "Last Name: ";
            getline (cin, last);
            Person* Person1 = search (first, last);
            if (Person1){
                cout << "Person 2\n";
                cout << "First Name: ";
                getline (cin, first);
                cout << "Last Name: ";
                getline (cin, last);
                Person* Person2 = search (first, last);
                if (Person2){
                    cout << endl << Person1->l_name << ", " << Person1->f_name << endl;
                    cout << Person1->birthdate->get_month_name() << " " << Person1->birthdate->get_day() << ", " << Person1->birthdate->get_year() << endl;
                    cout << "Phone " << Person1->phone->get_contact() << endl;
                    cout << "Email " << Person1->email->get_contact() << endl;
                    cout << endl;
                    cout << endl << Person2->l_name << ", " << Person2->f_name << endl;
                    cout << Person2->birthdate->get_month_name() << " " << Person2->birthdate->get_day() << ", " << Person2->birthdate->get_year() << endl;
                    cout << "Phone " << Person2->phone->get_contact() << endl;
                    cout << "Email " << Person2->email->get_contact() << endl;
                    Person1->makeFriend(Person2);
                    Person2->makeFriend(Person1);
                }
                else{
                    cout << endl << "Person not found\n";
                }

            }
            else{
                cout << endl<<"Person not found\n";
            }


        }

        
        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}
