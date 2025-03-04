// Consider a scenario where you have a base class NetworkDevice and derived classes Router and Switch.
 // virtual inheritance, design the classes and 
 //discuss the benefits.

 The const keyword in C++ can be used in the context of class methods to signify that the method does not modify 
 the state of the object it is called on. It ensures that the method will not alter any member variables of the class or call
  any non-const methods on the object.

There are two primary ways const is used in class methods:

Const Member Functions (const after the method signature)
Const Parameters and Return Types (used within method signatures)

 If the destructor is not virtual, only the base class destructor will be called, which can result in
  incomplete cleanup of resources allocated by the derived class. This is often referred to as "slicing" or incomplete destruction, 
 and it may lead to resource leaks (e.g., memory or file handles not being freed).

 Abstract Class:

Can have both abstract methods (without implementation) and concrete methods (with implementation).
Can have method overloading and default implementations.
Interface:

Can only have abstract methods (no method implementations) in many languages (including C++).
No default implementations of methods (in C++ prior to C++11, although C++11 and onwards allow static and default methods in interfaces, but they're not widely used).
 #include <iostream>
 #include <string>
 #include <map>
 
 using namespace std;
 
 class NetworkDevice {
     public:
         NetworkDevice() {}
         virtual ~NetworkDevice() {} //mora da ima virtualni destruktor ako je prazna apstraktna klasa bez implementacija virtuelnih fja
         virtual string ResolveMAC(string s)=0;
     protected:
         string private_key;
         int name;
 };
 
 class Router : virtual public NetworkDevice {
     public:
         Router() {
             IP_MAC_Table.insert({"127.0.0.1","dwaf.23sf.324.aefg"});
         }
         map<string,string> IP_MAC_Table; //ARP table
         string ResolveMAC(string s) override {
             return IP_MAC_Table[s];
         }
         
 };
 
 class Switch : virtual public NetworkDevice {
     private:
         map<int,string> Port_MAC_Table;
     public:
         Switch() {
             Port_MAC_Table.insert({3214,"dwaf.23sf.324.aefg"});
         }
         string ResolveMAC(string i) override {
             return Port_MAC_Table[stoi(i)];
         }
         
 };
 
 class DiamodProblem: public Switch,public Router {
     public:
         DiamodProblem() {
             cout << "Diamog" <<endl;
         }
         string ResolveMAC(string s) override {
             return Router::ResolveMAC(s);
         }
 };
 
 int main() {
     
     NetworkDevice *dev1;
     Router r;
     dev1 = &r;
     NetworkDevice *dev2;
     Switch s;
     dev2 = &s;
     cout << dev1->ResolveMAC("127.0.0.1") << endl;
     cout << dev2->ResolveMAC("3214") << endl;
     
     DiamodProblem d;
     cout << d.ResolveMAC("127.0.0.1") << endl;
 
     return 0;
 }
