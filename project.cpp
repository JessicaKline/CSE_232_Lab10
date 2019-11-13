// Jessica Kline


#include <iostream>
using std::cout; using std::cin; using std::endl;
#include <fstream>
using std::ifstream;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <algorithm>

/*  bool check_difference() iterates through a password and the word it's beging         checked for similarities to. 
    It returns true if:
        -the password and the checking word are exactly the same
        -if the number of same characters in the larger of the two strings is equal to the acceptable amount of difference
*/
bool check_difference(const string &checking, const string &password, const int &difference) {
    int ctr = 0; 
    int password_size = password.size(); 
    int checking_size = checking.size();
    
    if(checking == password) return true;
    else {
        if(password_size >= checking_size) {
            // the password is larger than the checking string
            for(int x = 0; x < checking_size; x++) {
                if(password[x] == checking[x]) ctr++;
            }
            if( (password_size - ctr) == difference) return true;
            else return false;
        } else {
            // the checking string is larger than the password
            for(int x = 0; x < password_size; x++) {
                if(password[x] == checking[x]) ctr++;
            }
            
            if( (checking_size - ctr) == difference) return true;
            else return false;
        }
    }
    return false;
}

/* vector<string> similartities() checks each string in the password_list against     the password using bool check_difference(). The string is added to a new        vector<string> if check_difference returns true.
*/
vector<string> similarities(const vector<string> &password_list, const string &password, const int &difference) {
    vector <string> close;
    for(string s: password_list) {
        if(check_difference(s, password, difference)) close.push_back(s);
    }
    return close;
}

/* int main() reads a list of strings from "common_passwords.txt" into a vector<string>. The user is prompted to input their password. A list of similar passwords is collected using vector<string> similarities() begining with a difference of zero. That list is then displayed to the user
*/
int main(){
    string password = "";
    vector <string> password_list, close_passwords;
    int difference = -1;
    ifstream input;
    
    input.open("common_passwords.txt");
    
    while(input >> password){
        password_list.push_back(password);
    }
    
    cout << "Give me a password: ";
    cin >> password;

    while (close_passwords.empty()){
        difference++;
        close_passwords = similarities(password_list, password, difference);
    }
    sort(close_passwords.begin(), close_passwords.end());
    
    cout << "You provided a password of " << password << endl;
    cout << "The most similar passwords to " << password << " are: " << endl;
    for(string s: close_passwords){
        cout << s << ", ";
    }
    cout << endl << "All of which are " << difference << " character(s) different." << endl;
}
