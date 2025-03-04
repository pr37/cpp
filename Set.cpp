// Set: unique elements in some sorted order,fast insertion, deletion and search operations O(log n).
#include <iostream>
#include <set>

using namespace std;

set<int> unite_two_sets(set<int> *s1, set<int> *s2) {
    set<int> res = *s1;
    res.insert(s2->begin(),s2->end());
    return res;
}

set<int> intersection_set(set<int> s1, set<int> s2) {
    //std::set_intersection
    set<int>ret;
    for(auto x : s1) {
        for(auto y : s2) {
            if (x==y) {
                ret.insert(x);
            }
        }
    }
    return ret;
}

void print_set(set<int> s) {
    cout << endl;
    for(auto x : s) {
        cout << x << " ";
    }
}

int main() {
    //set::emplace() - insert only if unique
    //insert()
    //auto iter = set.begin(), set.end()
    //auto iter2 = next(iter,2) - begin+2
    //auto it = find(val) - ret .end() if not found
    //print iterator: cout << *it
    //for(auto it=s.begin();it != s.end();it++)
    //set.erase(val or it)
    //if - set.empty()
    //set.size()
    
    
    set<int> x = {1,4,2,3,3};
    //std::cout << x << endl; ne moze ovako
    for (auto s : x) {
        cout<<s<<" ";
    }
    
    set<int> s1 = {1,2,3};
    set<int> s2 = {3,4,5,6};
    print_set(unite_two_sets(&s1,&s2));
    
    print_set(intersection_set(s1,s2));
    

    return 0;
}
