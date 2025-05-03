// Updated loadDB method to handle new contact types
void Network::loadDB(string filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open the file!" << endl;
        return;
    }

    string fname, lname, bdate, email, phone;
    string buff;
    vector<vector<pair<string, string>>> People_friend_list;
    
    while (getline(file, fname)) {
        vector<pair<string,string>> temp;
        string college = "", major = "", state = "";
        
        getline(file, lname);
        getline(file, bdate);
        getline(file, phone);
        getline(file, email);
        
        // Read lines until we find the divider "--------------------"
        while (getline(file, buff) && buff.compare(0, 20, "--------------------") != 0) {
            // Check if this is a college, major, or state line
            if (buff.find("College: ") == 0) {
                college = buff.substr(9); // Skip "College: "
            } 
            else if (buff.find("Major: ") == 0) {
                major = buff.substr(7); // Skip "Major: "
            } 
            else if (buff.find("State: ") == 0) {
                state = buff.substr(7); // Skip "State: "
            } 
            // Otherwise, it's a friend entry
            else {
                // Parse friends line
                size_t openParen = buff.find('(');
                size_t closeParen = buff.find(')');
                
                if (openParen != string::npos && closeParen != string::npos) {
                    string fullname = buff.substr(openParen + 1, closeParen - openParen - 1);
                    size_t spacePos = fullname.find(' ');
                    
                    if (spacePos != string::npos) {
                        string friend_first = fullname.substr(0, spacePos);
                        string friend_last = fullname.substr(spacePos + 1);
                        temp.push_back({friend_first, friend_last});
                    }
                }
            }
        }
        
        // Create the person with additional fields
        Person* newPerson = new Person(fname, lname, bdate, email, phone, 
                                      college, major, state);
        
        People_friend_list.push_back(temp);
        push_back(newPerson);
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

// Updated saveDB method to save contact types
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

        file << ptr->phone->get_contact("full") << endl;
        file << ptr->email->get_contact("full") << endl;
        
        // Save the additional fields if not empty
        if (ptr->college->get_contact("brief") != "") {
            file << "College: " << ptr->college->get_contact("brief") << endl;
        }
        if (ptr->major->get_contact("brief") != "") {
            file << "Major: " << ptr->major->get_contact("brief") << endl;
        }
        if (ptr->state->get_contact("brief") != "") {
            file << "State: " << ptr->state->get_contact("brief") << endl;
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

// Updated wiseSearch to use contact types
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
        
        // Check email
        string email = ptr->email->get_contact("brief");
        transform(email.begin(), email.end(), email.begin(), ::tolower);
        if (email.find(query) != string::npos) {
            results.push_back(ptr);
            ptr = ptr->next;
            continue;
        }
        
        // Check phone
        string phone = ptr->phone->get_contact("brief");
        if (phone.find(query) != string::npos) {
            results.push_back(ptr);
            ptr = ptr->next;
            continue;
        }
        
        // Check college
        string college = ptr->college->get_contact("brief");
        transform(college.begin(), college.end(), college.begin(), ::tolower);
        if (!college.empty() && college.find(query) != string::npos) {
            results.push_back(ptr);
            ptr = ptr->next;
            continue;
        }
        
        // Check major
        string major = ptr->major->get_contact("brief");
        transform(major.begin(), major.end(), major.begin(), ::tolower);
        if (!major.empty() && major.find(query) != string::npos) {
            results.push_back(ptr);
            ptr = ptr->next;
            continue;
        }
        
        // Check state
        string state = ptr->state->get_contact("brief");
        transform(state.begin(), state.end(), state.begin(), ::tolower);
        if (!state.empty() && state.find(query) != string::npos) {
            results.push_back(ptr);
            ptr = ptr->next;
            continue;
        }
        
        ptr = ptr->next;
    }
    
    return results;
}

// Updated code for option 5 (Print people with last name)
else if (opt==5){
    cout << "Print people with last name \n";
    cout << "Last name: ";
    string la_name1;
    getline(cin,la_name1);
    bool found = false;
    Person* traverse = head;
    while(traverse != NULL){
        if (traverse->l_name == la_name1){
            traverse->print_person(); // This will now print all contact info including college, major, state
            cout << "--------------------" << endl;
            found = true;
        }
        traverse = traverse->next;
    }
    if (found == false)
        cout << "Person not found! \n";
}
