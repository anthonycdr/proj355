#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <regex>
#include <cstdlib> 
#include <sstream>
#include <algorithm>

using namespace std;

// Only showing the modified methods to keep the file shorter

void Network::loadDB(string filename){
    // Modified to handle additional fields
    std::ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open the file!" << endl;
        return;
    }

    string fname, lname, bdate, email, phone, college, major, interests;
    string buff;
    vector<vector<pair<string, string>>> People_friend_list;
    
    while (getline(file, fname)) {
        vector <pair<string,string>> temp;
        string divider;
        getline(file, lname);
        getline(file, bdate);
        getline(file, phone);
        getline(file, email);
        
        if (opt==1){
            // Save the network database
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            getline(cin, fileName);
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
            // Load the network database
            Person* current = head;
            while (current != nullptr){
                Person* temp = current;
                current = current->next;
                delete temp;
            }
            head = nullptr;
            tail = nullptr;
            count = 0;
            
            cout << "Loading network database \n";
            // List available text files
            system("ls > file_list.txt");
            ifstream infile("file_list.txt");
            regex match(".+\\.txt$");
            string file;
            while (getline(infile, file)){
                if (file == "file_list.txt"){
                    continue;
                }
                if (regex_match(file, match)){
                    cout << file << endl;  
                }
            }
            system("rm file_list.txt");
            infile.close();
            
            string filename;
            cout << "Enter the name of the load file: "; 
            cin >> filename;
            
            if (!(ifstream(filename))){
                cout << "File " << filename << " does not exist!" << endl;
            }
            else{
                loadDB(filename);
                cout << "Network loaded from " << filename << " with " << count << " people \n";
            }
        }
        else if (opt == 3){
            // Add a new person
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
            // Remove a person
            string fi_name, la_name;
            cout << "Enter the first name to remove: " << endl;
            getline(cin, fi_name);
            cout << "Enter the last name to remove: " << endl;
            getline(cin, la_name);
            bool result = remove(fi_name, la_name);
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
            // Print people with last name
            cout << "Print people with last name \n";
            cout << "Last name: ";
            string la_name1;
            getline(cin, la_name1);

            bool found = false;
            Person* traverse = head;
            while(traverse != NULL){
                if (traverse->l_name == la_name1){
                    cout << traverse->f_name << endl;
                    cout << traverse->l_name << endl;
                    cout << traverse->birthdate->get_month() << "/" << traverse->birthdate->get_day() << "/" << traverse->birthdate->get_year() << endl;
                    cout << traverse->email->get_contact() << endl;
                    cout << traverse->phone->get_contact() << endl;
                    cout << "--------------------" << endl;
                    found = true;
                }
                traverse = traverse->next;
            }
            if (found == false)
                cout << "Person not found! \n";
        }
        else if (opt==6){
            // Connect people as friends
            cout << "Make friends:\n";
            cout << "Person 1\n";
            cout << "First Name: ";
            string first, last;
            getline(cin, first);
            cout << "Last Name: ";
            getline(cin, last);
            Person* Person1 = search(first, last);
            if (Person1){
                cout << "Person 2\n";
                cout << "First Name: ";
                getline(cin, first);
                cout << "Last Name: ";
                getline(cin, last);
                Person* Person2 = search(first, last);
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
                cout << endl << "Person not found\n";
            }
        }
        else if (opt==7){
            // Smart search
            cout << "Smart Search\n";
            cout << "Enter search term (name, phone, email, etc.): ";
            string query;
            getline(cin, query);
            
            vector<Person*> results = wiseSearch(query);
            
            if (results.empty()) {
                cout << "No results found for \"" << query << "\"" << endl;
            } else {
                cout << "Found " << results.size() << " results for \"" << query << "\":" << endl;
                cout << "-----------------------------------------" << endl;
                
                for (Person* p : results) {
                    p->print_person();
                    cout << "-----------------------------------------" << endl;
                }
            }
        }
        else if (opt==8){
            // Recommendations
            cout << "Get Recommendations\n";
            cout << "Enter the person's information:\n";
            cout << "First Name: ";
            string first, last;
            getline(cin, first);
            cout << "Last Name: ";
            getline(cin, last);
            
            Person* person = search(first, last);
            if (!person) {
                cout << "Person not found!" << endl;
            } else {
                cout << "Recommendation options:\n";
                cout << "1. By shared interests\n";
                cout << "2. By same college\n";
                cout << "Enter option (1-2): ";
                
                int rec_opt;
                cin >> rec_opt;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                vector<Person*> recommendations;
                
                if (rec_opt == 1) {
                    recommendations = recommendByInterests(person);
                    cout << "\nPeople with shared interests:\n";
                } else if (rec_opt == 2) {
                    recommendations = recommendByCollege(person);
                    cout << "\nPeople from the same college (" << person->get_college() << "):\n";
                } else {
                    cout << "Invalid option!" << endl;
                    continue;
                }
                
                if (recommendations.empty()) {
                    cout << "No recommendations found." << endl;
                } else {
                    cout << "-----------------------------------------" << endl;
                    for (Person* p : recommendations) {
                        p->print_person();
                        cout << "-----------------------------------------" << endl;
                    }
                }
            }
        }
        else {
            cout << "Nothing matched!\n";
        }
         Try to read new fields if they exist
        college = "";
        major = "";
        interests = "";
        
        // We'll read lines until we hit the divider or friends section
        if (getline(file, buff) && buff.compare(0, 20, "--------------------") != 0) {
            // This is either college or a friend entry
            if (buff.find(',') == string::npos && buff.find('(') == string::npos) {
                // This is likely the college field
                college = buff;
                
                // Try to read major
                if (getline(file, buff) && buff.compare(0, 20, "--------------------") != 0) {
                    if (buff.find(',') == string::npos && buff.find('(') == string::npos) {
                        // This is likely the major field
                        major = buff;
                        
                        // Try to read interests
                        if (getline(file, buff) && buff.compare(0, 20, "--------------------") != 0) {
                            if (buff.find(',') != string::npos && buff.find('(') == string::npos) {
                                // This is likely the interests field
                                interests = buff;
                                getline(file, buff); // Get the next line after interests
                            }
                        }
                    }
                }
            }
        }
        
        // Process any remaining lines as friends until we hit the divider
        while (buff.compare(0, 20, "--------------------") != 0) {
            int index = buff.find(',');
            if (index != string::npos) {
                string friend_first = buff.substr(0, index);
                string friend_last = buff.substr(index + 1);
                temp.push_back({friend_first, friend_last});
            } else {
                // Check if it has the format "code (First Last)"
                int openParen = buff.find('(');
                int closeParen = buff.find(')');
                if (openParen != string::npos && closeParen != string::npos) {
                    string fullname = buff.substr(openParen + 1, closeParen - openParen - 1);
                    int spacePos = fullname.find(' ');
                    if (spacePos != string::npos) {
                        string friend_first = fullname.substr(0, spacePos);
                        string friend_last = fullname.substr(spacePos + 1);
                        temp.push_back({friend_first, friend_last});
                    }
                }
            }
            
            if (!getline(file, buff)) {
                break;
            }
        }
        
        // Create a new person with all fields
        Person* newPerson = new Person(fname, lname, bdate, email, phone);
        
        // Set the additional fields
        newPerson->set_college(college);
        newPerson->set_major(major);
        
        // Parse interests if any
        if (!interests.empty()) {
            stringstream ss(interests);
            string interest;
            while (getline(ss, interest, ',')) {
                // Trim leading/trailing spaces
                size_t start = interest.find_first_not_of(" \t");
                size_t end = interest.find_last_not_of(" \t");
                if (start != string::npos && end != string::npos) {
                    interest = interest.substr(start, end - start + 1);
                    if (!interest.empty()) {
                        newPerson->add_interest(interest);
                    }
                }
            }
        }
        
        People_friend_list.push_back(temp);
        push_back(newPerson); // Add person to the network
    }
    file.close();
    
    // Connect friends
    Person* traverse = head;
    for (int i = 0; i < People_friend_list.size(); i++) {
        vector<Person*> friends_vector;
        for (int j = 0; j < People_friend_list[i].size(); j++) {
            Person* newFriend = search(People_friend_list[i][j].first, People_friend_list[i][j].second);
            if (newFriend != nullptr) {
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
        file << ptr->f_name << endl;
        file << ptr->l_name << endl;
        file << ptr->birthdate->get_month() << "/"
             << ptr->birthdate->get_day() << "/"
             << ptr->birthdate->get_year() << endl;

        file << "(" << ptr->phone->get_contact("full") << endl;
        file << "(" << ptr->email->get_contact("full") << endl;
        
        // Save new fields if they're not empty
        if (!ptr->get_college().empty()) {
            file << ptr->get_college() << endl;
        }
        if (!ptr->get_major().empty()) {
            file << ptr->get_major() << endl;
        }
        if (!ptr->get_interests().empty()) {
            for (size_t i = 0; i < ptr->get_interests().size(); i++) {
                file << ptr->get_interests()[i];
                if (i < ptr->get_interests().size() - 1) {
                    file << ", ";
                }
            }
            file << endl;
        }

        // Save friends
        for (int i = 0; i < ptr->myfriends.size(); i++) {
            file << codeName(ptr->myfriends[i]->f_name, ptr->myfriends[i]->l_name) << " (" 
                 << ptr->myfriends[i]->f_name << " " << ptr->myfriends[i]->l_name << ")" << endl;
        }

        file << "--------------------" << endl;
        ptr = ptr->next;
    }

    file.close();
}

// New method for wise search
vector<Person*> Network::wiseSearch(string query) {
    vector<Person*> results;
    // Convert query to lowercase for case-insensitive search
    transform(query.begin(), query.end(), query.begin(), ::tolower);
    
    Person* ptr = head;
    while (ptr != NULL) {
        // Check first name
        string fname_lower = ptr->f_name;
        transform(fname_lower.begin(), fname_lower.end(), fname_lower.begin(), ::tolower);
        if (fname_lower.find(query) != string::npos) {
            results.push_back(ptr);
            ptr = ptr->next;
            continue;
        }
        
        // Check last name
        string lname_lower = ptr->l_name;
        transform(lname_lower.begin(), lname_lower.end(), lname_lower.begin(), ::tolower);
        if (lname_lower.find(query) != string::npos) {
            results.push_back(ptr);
            ptr = ptr->next;
            continue;
        }
        
        // Check phone (remove dashes for comparison)
        string phone = ptr->phone->get_contact("brief");
        string phone_clean;
        for (char c : phone) {
            if (c != '-') {
                phone_clean += c;
            }
        }
        if (phone_clean.find(query) != string::npos || phone.find(query) != string::npos) {
            results.push_back(ptr);
            ptr = ptr->next;
            continue;
        }
        
        // Check email
        string email = ptr->email->get_contact("brief");
        transform(email.begin(), email.end(), email.begin(), ::tolower);
        if (email.find(query) != string::npos) {
            results.push_back(ptr);
            ptr = ptr->next;
            continue;
        }
        
        // Check birth year
        string birth_year = to_string(ptr->birthdate->get_year());
        if (birth_year.find(query) != string::npos) {
            results.push_back(ptr);
            ptr = ptr->next;
            continue;
        }
        
        // Check birth month
        string birth_month = to_string(ptr->birthdate->get_month());
        if (birth_month.find(query) != string::npos) {
            results.push_back(ptr);
            ptr = ptr->next;
            continue;
        }
        
        // Check birth day
        string birth_day = to_string(ptr->birthdate->get_day());
        if (birth_day.find(query) != string::npos) {
            results.push_back(ptr);
            ptr = ptr->next;
            continue;
        }
        
        // Check college
        string college = ptr->get_college();
        transform(college.begin(), college.end(), college.begin(), ::tolower);
        if (!college.empty() && college.find(query) != string::npos) {
            results.push_back(ptr);
            ptr = ptr->next;
            continue;
        }
        
        // Check major
        string major = ptr->get_major();
        transform(major.begin(), major.end(), major.begin(), ::tolower);
        if (!major.empty() && major.find(query) != string::npos) {
            results.push_back(ptr);
            ptr = ptr->next;
            continue;
        }
        
        // Check interests
        bool found_in_interests = false;
        for (const string& interest : ptr->get_interests()) {
            string interest_lower = interest;
            transform(interest_lower.begin(), interest_lower.end(), interest_lower.begin(), ::tolower);
            if (interest_lower.find(query) != string::npos) {
                results.push_back(ptr);
                found_in_interests = true;
                break;
            }
        }
        
        if (found_in_interests) {
            ptr = ptr->next;
            continue;
        }
        
        ptr = ptr->next;
    }
    
    return results;
}

// New method to recommend based on shared interests
vector<Person*> Network::recommendByInterests(Person* person) {
    vector<Person*> recommendations;
    
    if (person->get_interests().empty()) {
        return recommendations; // No interests to base recommendations on
    }
    
    // Vector to store person and count of shared interests
    vector<pair<Person*, int>> candidates;
    
    Person* ptr = head;
    while (ptr != NULL) {
        // Skip the person themselves
        if (ptr == person) {
            ptr = ptr->next;
            continue;
        }
        
        // Skip if they're already friends
        bool already_friends = false;
        for (Person* friend_ptr : person->myfriends) {
            if (ptr == friend_ptr) {
                already_friends = true;
                break;
            }
        }
        
        if (already_friends) {
            ptr = ptr->next;
            continue;
        }
        
        // Count shared interests
        int shared_count = 0;
        for (const string& my_interest : person->get_interests()) {
            for (const string& their_interest : ptr->get_interests()) {
                // Case-insensitive comparison
                string my_lower = my_interest;
                string their_lower = their_interest;
                transform(my_lower.begin(), my_lower.end(), my_lower.begin(), ::tolower);
                transform(their_lower.begin(), their_lower.end(), their_lower.begin(), ::tolower);
                
                if (my_lower == their_lower) {
                    shared_count++;
                    break; // Only count each interest once
                }
            }
        }
        
        if (shared_count > 0) {
            candidates.push_back(make_pair(ptr, shared_count));
        }
        
        ptr = ptr->next;
    }
    
    // Sort by number of shared interests (descending)
    sort(candidates.begin(), candidates.end(), 
         [](const pair<Person*, int>& a, const pair<Person*, int>& b) {
             return a.second > b.second;
         });
    
    // Extract the persons from the sorted list
    for (const auto& candidate : candidates) {
        recommendations.push_back(candidate.first);
    }
    
    return recommendations;
}

// New method to recommend based on same college
vector<Person*> Network::recommendByCollege(Person* person) {
    vector<Person*> recommendations;
    
    if (person->get_college().empty()) {
        return recommendations; // No college to base recommendations on
    }
    
    string my_college = person->get_college();
    transform(my_college.begin(), my_college.end(), my_college.begin(), ::tolower);
    
    Person* ptr = head;
    while (ptr != NULL) {
        // Skip the person themselves
        if (ptr == person) {
            ptr = ptr->next;
            continue;
        }
        
        // Skip if they're already friends
        bool already_friends = false;
        for (Person* friend_ptr : person->myfriends) {
            if (ptr == friend_ptr) {
                already_friends = true;
                break;
            }
        }
        
        if (already_friends) {
            ptr = ptr->next;
            continue;
        }
        
        // Check if they attended the same college
        string their_college = ptr->get_college();
        transform(their_college.begin(), their_college.end(), their_college.begin(), ::tolower);
        
        if (!their_college.empty() && their_college == my_college) {
            recommendations.push_back(ptr);
        }
        
        ptr = ptr->next;
    }
    
    return recommendations;
}

void Network::showMenu(){
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
        cout << "7. Smart search \n";  // New menu option
        cout << "8. Get recommendations \n";  // New menu option
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

        //
