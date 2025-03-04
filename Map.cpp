#include <iostream>
#include <map>
using namespace std;
//key value pairs sorted on the basis of keys

std::map:
Ordered: The elements in a map are always stored in sorted order according to the key. By default, the sorting is done using
 the operator< on the key type, but you can provide a custom comparator if needed.
Internal structure: A map is typically implemented as a red-black tree (a self-balancing binary search tree), which maintains
 the order of elements while providing efficient insertion, deletion, and search operations.
std::unordered_map:
Unordered: The elements in an unordered_map are not stored in any specific order. The elements are distributed across buckets based on their hash value (via a hash function), and the order can vary.
Internal structure: An unordered_map is implemented as a hash table, where the key-value pairs are stored in buckets, and each bucket corresponds to a specific hash value of the key.
2. Time Complexity
std::map:
Search: O(log N) for find, insert, and erase operations.
Insertion/Deletion: O(log N) due to the tree structure.
std::unordered_map:
Search: O(1) on average for find, insert, and erase operations. However, in the worst case (when many elements hash to the same bucket), it can degrade to O(N) due to collisions.
Insertion/Deletion: O(1) on average.
How to modify your class to use with map and unordered_map? The class must be hashable to use a user-defined type as a key.
 In the case of std::map, the comparison operators (<, >, etc.) need to be overloaded (I think just one of them but I forget 
    which without looking it up).

//set.find(key)
//it->first - key, it->second -val

map<char,int> count_char_frequency(string s) {
    map<char,int> res;
    char c;
    int i = 0;
    for(int i=0;i<size(s);i++){
        int count = 0;
        auto it = res.find(s[i]);
        if(it == res.end()) { //ako nije nasao
            res.insert({s[i],1});
        } else {
            count = it->second;
            count++;
            res[it->first] = count; //ovako se update element u recniku
            cout << it->first << " ";
            count = 0;
        }
    }
    return res;
}

void print_map(map<char,int> m) {
    cout << endl;
    for(auto it = m.begin(); it!=m.end(); it++) {
        cout << it->first << " " << it->second << endl;
    }
}

int main() {
    map<int,string> m = {{1,"a"},{2,"b"},{3,"c"}};
    print_map(count_char_frequency("aabccc"));
    return 0;
}
