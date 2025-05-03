#include "date.h"

#include <iostream>
#include <map>
using namespace std;

map <int, string> Months {
    {1,"January"}, {2, "February"}, {3,"March"},
        {4, "April"}, {5, "May"}, {6, "June"},
        {7, "July"}, {8,"August"}, {9, "September"},
        {10,"October"}, {11,"November"}, {12, "December"}
};

int string_to_num(string s) {
    int n = 0;
    for (int i = 0; i < s.length(); i++) {
        n = n * 10 + (s[i] - '0');
    }
    return n;
}
  
Date:: Date(string date){
    int pos = 0;
    int arr[3]; 
    int count = 0;
    for(int i = 0; i < date.length(); i++){
        if(date[i] == '/' && count < 2){
            arr[count] =  string_to_num(date.substr(pos,i-pos));
            pos = i + 1;
            count++;
        }
    }
    arr[count] = string_to_num(date.substr(pos));
    month = arr[0]; 
    day = arr[1];
    year = arr[2];
}

void Date::print_date(string str){
    cout << Months[month] << " " << day << ", " << year << endl; // print date in the format "Month day, year"`

}

int Date::get_month() const{
    return month;}

string Date::get_month_name() const{
    return Months[month];}
    
 int Date::get_day() const{
    return day;}
    
 int Date::get_year() const{
    return year;}
    
   

