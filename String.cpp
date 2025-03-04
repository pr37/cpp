#include <iostream>
#include <string>
#include <set>

using namespace std;

//Longest Substring Without Repeating Characters
//abcabbccabczaaabc ->abcz

string longest_substring_no_repeat(string s) {
    set<char> substring;
    int curr_lenght = 0;
    int last_lenght = 0;
    for(int i = 0; i < size(s);i++) {
        auto it = substring.find(s[i]);
        if(it == substring.end()) {
            substring.insert(s[i]);
            curr_lenght++;
        } else {
            if(curr_lenght>=last_lenght) {
                //keep this one
                last_lenght=curr_lenght;
            } else if (curr_lenght<last_lenght) {
                //start over
                curr_lenght = 0;
                substring = {};
            }
        }
    }
    string ret;
    for(auto s:substring) {
        ret += s;
    }
    return ret;
}

int main() {
    
    string s= "abcabbccabczaaabc";
    cout << longest_substring_no_repeat(s); 
    return 0;
}

-----------------------------

#include <iostream>
#include <string>
using namespace std;
#define swap_(a,b) a^=b; b^=a; a^=b; 
//sort  all chars in a string ascending order
void sort_string(string s) {
    for(int i=0; i<size(s);i++) {
        for(int j=i+1; j<size(s);j++) {
            if(s[i]>s[j]) {
                swap_(s[i],s[j])
            }
        }
    }
    cout << s << endl;
}


int main() {
    
    sort_string("bbccaaawer");
    return 0;
}


-------------------------------------



#include <iostream>


//palindrom check
//reverse string
//reverse words in string

class PalindromeChecker {
    public: 
        string tmp_str;
        bool check () {
            char c;
            int i,j;
            if(len(this.tmp_str) % 2 == 0) {
                for(i=0,j=len(this.tmp_str);i<len(this.tmp_str)/2;i++) {
                    if(tmp_str[i] != tmp_str[j]) {
                        return false;
                    }
                }
            } else {
                for()
            }
        }

};


int main () {

}
