#include <iostream>
#include <vector>
#include <algorithm>

#define STEK_SIZE 100
#define swap_(a,b) a^=b; b^=a; a^=b;

using namespace std;

//v.erase(iter)
//v.push_back(val)
//v.size() vs v.capacity()  - actual size vs koliko bi jos moglo da stane
//v.begin() v.end()

//vektor razlikuje se sto se automatksi dodaje memorija za nove elemente


void print_sorted_vector(vector<int> x) {
    cout << "Size of" << x.size() << endl;
    for(int i=0; i<x.size();i++) {
        for(int j=i;j<x.size();j++) {
            if(x[i]>x[j]) {
                swap_(x[i],x[j])
            }
        }
    }
    for(int i = 0;i<x.size();i++)  
        cout << x[i] << " ";
}

void print_reverse_vector(vector<int> x) {
    for(int i=x.size()-1,j=0;i>(x.size()-1)/2;i--,j++) {
        swap_(x[i],x[j])
    }
    for(int i = 0;i<x.size();i++)  
        cout << x[i] << " ";
}

bool check_if_palindrome(vector<int>x) {
    for(int i=x.size()-1,j=0;i>(x.size()-1)/2;i--,j++) {
        if(x[i] != x[j]) {
            cout<<"f"<<endl;
            return false;
        }
    }
    return true;
}

void put_zeroes_at_the_back(vector<int>x) {
    for(int i =0;i<x.size()-1;i++) {
        if(x[i] == 0) {
            x.erase(x.begin()+1);
            x.push_back(0);
        }
    }
    for(int i = 0;i<x.size();i++)  
        cout << x[i] << " ";
}

int main() {

 vector<int> x = {1,0,3,0,4};
 //print_sorted_vector(x);
 //cout <<endl<< x.capacity() << endl;
 //print_reverse_vector(x);
 //check_if_palindrome(x);
 put_zeroes_at_the_back(x);
}

