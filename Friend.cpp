//friend keyword is used to grant a function or class access to the private and protected members of another class.

Friend function: A non-member function that is allowed to access the private and protected members of a class.
Friend class: A class that is allowed to access the private and protected members of another class.
Scope: Friendship is not inherited, meaning if a class A is a friend of class B, and class C is derived from B, C will not automatically be a friend of A.

  FRIEND FUNKCIJA:

class MyClass {
private:
    int privateVar;

public:
    MyClass(int value) : privateVar(value) {}

    // Declaring a friend function
    friend void printPrivate(const MyClass& obj);
};

// Friend function definition
void printPrivate(const MyClass& obj) {
    // Accessing private member of MyClass directly
    std::cout << "Private variable: " << obj.privateVar << std::endl;
}


FRIEND KLASA:

class ClassB; // Forward declaration of ClassB

class ClassA {
private:
    int privateDataA;

public:
    ClassA(int value) : privateDataA(value) {}

    // Declaring ClassB as a friend class
    friend class ClassB;  
};

class ClassB {
public:
    void printClassAData(const ClassA& obj) {
        // ClassB can access private data of ClassA
        std::cout << "Private data of ClassA: " << obj.privateDataA << std::endl;
    }
};
