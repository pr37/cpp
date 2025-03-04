
#include <iostream>
using namespace std;
//the new expression returns the address of the memory location

int main() {
    
    int* p = new int;
    *p = 3;
    cout<<*p<<endl;
    int* p2 = new int{4};
    cout<<*p2<<endl;
    
    delete p,p2;

    return 0;
}

Question:
You are working on a large-scale networking application that processes a massive amount of data from multiple sources.
 The application must be optimized for both memory usage and speed. What strategies would you use in C++ to optimize memory
  allocation and reduce the memory footprint?

Answer:
To optimize memory usage and speed in C++ when working with large-scale networking applications, you can apply several 
advanced techniques. Here are some of the key strategies:

1. Object Pooling
Object pooling involves pre-allocating a pool of objects and reusing them, instead of dynamically allocating and deallocating
 memory for each object. This helps reduce the overhead of memory allocation and deallocation.

2. Custom Allocators
Custom allocators are a way to manage memory more efficiently than the default allocator in C++. You can define your own memory 
management strategy to allocate and deallocate memory in a way that fits the specific needs of your application.

Why use it?: To optimize the allocation of large data structures or objects by minimizing overhead and providing more control over
 memory management.

How to use it?: You can create a custom allocator using std::allocator or implement your own memory pool.
3. Memory Alignment
Memory alignment ensures that data is stored in memory at addresses that are multiples of a particular value (usually the size of
     the data type). Proper alignment can reduce memory access latency and avoid performance penalties on some architectures.

Why use it?: Improves CPU cache usage and can prevent costly misaligned memory accesses that may lead to performance degradation.

How to use it?: In C++, you can use alignas (since C++11) or platform-specific optimizations to ensure that your structures are aligned.

Class instance moze da ide na stack ili na heap,
na stack ako ide onda je instancirana u nekom lokalnom scope-u i kad se izadje iz skopa onda se 
automatski oslobodi, instanciranje na stack nije skupa operacija - stack is safe and cheap
Ako se dinamicki instancira onda ide na heap i to je skuplja operacija i ne brisu se automatski
memory leak - na heapu ako se ne obrise objekat

When to use stack memory:
Short-lived objects: If the object is only needed during the scope of a function, then using
 stack allocation is ideal because the memory is automatically freed when the function scope ends.

Small objects: Stack space is limited, so for small objects (e.g., primitive types or small 
    structures), it’s better to use stack allocation.

No need for manual management: You don’t need to worry about freeing the memory manually 
since the memory is automatically reclaimed when the scope ends.

When to use heap memory:
Objects with unknown or large sizes: If the size of the object is large (e.g., large arrays, complex structures), and you cannot know the exact size at compile time, you need to use dynamic memory.

Objects that need to outlive their scope: If you need an object to live beyond the current scope (e.g., across function calls or in different parts of the program), you should allocate it on the heap.
 This is especially true when working with data structures like linked lists, trees, or other objects
  that need to be manually managed and passed around.

Object whose lifetime is controlled manually: When the lifetime of an object is not bound to a
 function scope and must be controlled explicitly (e.g., memory needs to persist until you explicitly
     free it).


Shallow Copy: A shallow copy of an object copies the values of the member variables of the object, but if the member variables
 are pointers (or references to dynamic memory), it only copies the memory address of the pointer rather than the actual data 
 it points to. In other words, both the original object and the copied object will point to the same memory location, leading 
 to potential issues like double-free or unintended modifications.
class Shallow {
    public:
        int* data;
        Shallow(int val) { data = new int(val); }
        ~Shallow() { delete data; }
    };
Deep Copy: A deep copy creates a new object and allocates new memory for any dynamic data members (e.g., pointers). This
 ensures that the original object and the copied object are independent, and modifications to one object will not affect the other.   
class Deep {
        public:
            int* data;
            Deep(int val) { data = new int(val); }
            Deep(const Deep& other) { data = new int(*other.data); } // Deep copy constructor
            ~Deep() { delete data; }
        };

MOVE
Move Semantics in C++ allows resources (like dynamically allocated memory) to be transferred from
 one object to another without needing to copy the underlying data. This is done using rvalue 
 references (&&) and std::move. The primary benefit is improved performance, especially when 
 dealing with temporary objects that are no longer needed after their state has been moved.
In traditional copy semantics, when an object is copied, the resources (e.g., dynamically 
    allocated memory) are copied, which can be expensive. With move semantics, the resources are
     transferred (moved), meaning that the move operation typically only involves pointer 
     assignments, which is much faster than copying.
     MyClass obj1(10);
     MyClass obj2 = std::move(obj1); // Move operation: obj2 takes ownership of obj1's data

     std::move is used to cast an lvalue into an rvalue, allowing you to utilize move semantics. Essentially, 
     it enables the compiler to treat an object as an rvalue, 
     making it eligible for moving resources instead of copying them.


     In C++, you can protect an object from being copied by deleting or private-ing the copy constructor and the copy
      assignment operator. This is useful when you want to prevent an object from being copied, either to avoid accidental 
      copying or to prevent resource management issues (like double deletion, memory leaks, etc.).

     Here’s how you can protect an object from copying:
     
     1. Delete the Copy Constructor and Copy Assignment Operator
     The simplest and most explicit way to prevent an object from being copied is by deleting the copy constructor and the copy assignment operator. This makes it clear to anyone using the class that copying is not allowed.
     
     Syntax:
     cpp
     Copy
     class MyClass {
     public:
         MyClass(const MyClass&) = delete;           // Deleted copy constructor
         MyClass& operator=(const MyClass&) = delete; // Deleted copy assignment operator
     };
     Example:
     cpp
     Copy
     #include <iostream>
     using namespace std;
     
     class MyClass {
     public:
         MyClass() {
             cout << "Constructor called\n";
         }
     
         // Delete the copy constructor and copy assignment operator
         MyClass(const MyClass&) = delete;           // Prevent copy constructor
         MyClass& operator=(const MyClass&) = delete; // Prevent copy assignment operator
     
         void print() const {
             cout << "MyClass instance\n";
         }
     };
     
     int main() {
         MyClass obj1;
         obj1.print();
     
         // The following will give a compile-time error because copy is disabled:
         // MyClass obj2 = obj1;  // Copy constructor is deleted
         // MyClass obj3;
         // obj3 = obj1;  // Copy assignment operator is deleted
     
         return 0;
     }
     Output:
     
     sql
     Copy
     Constructor called
     Why This Works:
     The copy constructor is a special constructor used to create a new object as a copy of an existing one.
     The copy assignment operator is used when an already existing object is assigned a copy of another object.
     By deleting these methods, you tell the compiler that copying an object is not allowed, and any attempt to copy or assign 
     an object will result in a compilation error.
     
     2. Make the Copy Constructor and Copy Assignment Operator Private
     Another way to protect your object from being copied is to make the copy constructor and copy assignment operator private.
      This prevents outside code from directly calling these functions, although the compiler can still call them in certain cases,
       like when copying a temporary object.
     
     Syntax:
     cpp
     Copy
     class MyClass {
     private:
         MyClass(const MyClass&);           // Private copy constructor
         MyClass& operator=(const MyClass&); // Private copy assignment operator
     public:
         MyClass() { cout << "Constructor called\n"; }
         void print() const {
             cout << "MyClass instance\n";
         }
     };
     Example:
     cpp
     Copy
     #include <iostream>
     using namespace std;
     
     class MyClass {
     private:
         MyClass(const MyClass&);           // Private copy constructor
         MyClass& operator=(const MyClass&); // Private copy assignment operator
     
     public:
         MyClass() {
             cout << "Constructor called\n";
         }
     
         void print() const {
             cout << "MyClass instance\n";
         }
     };
     
     int main() {
         MyClass obj1;
         obj1.print();
     
         // The following will give a compile-time error:
         // MyClass obj2 = obj1;  // Copy constructor is private
         // MyClass obj3;
         // obj3 = obj1;  // Copy assignment operator is private
     
         return 0;
     }
     Output:
 
     Why This Works:
     The copy constructor and copy assignment operator are declared as private. This means that these functions cannot be called from outside the class, making it impossible to copy an object of this class.
     3. Use Move Semantics (Optional)
     In some cases, you might want to allow moving an object (i.e., transferring ownership of resources without copying).
      In this case, you can delete the copy constructor and copy assignment operator, but define a move constructor and move
       assignment operator to enable efficient transfer of resources.
     
     Example:
     cpp
     Copy
     #include <iostream>
     using namespace std;
     
     class MyClass {
     public:
         MyClass() {
             cout << "Constructor called\n";
         }
     
         MyClass(MyClass&&) noexcept { // Move constructor
             cout << "Move constructor called\n";
         }
     
         MyClass& operator=(MyClass&&) noexcept { // Move assignment operator
             cout << "Move assignment operator called\n";
             return *this;
         }
     
         MyClass(const MyClass&) = delete;           // Prevent copy constructor
         MyClass& operator=(const MyClass&) = delete; // Prevent copy assignment operator
     
         void print() const {
             cout << "MyClass instance\n";
         }
     };
     
     int main() {
         MyClass obj1;
         obj1.print();
     
         MyClass obj2 = std::move(obj1);  // Move constructor is called
         obj2.print();
     
         MyClass obj3;
         obj3 = std::move(obj2);  // Move assignment operator is called
         obj3.print();
     
         return 0;
     }
     Output:
  
     Constructor called
     Move constructor called
     MyClass instance
     Move assignment operator called
     MyClass instance
     Why This Works:
     The move constructor and move assignment operator enable efficient resource transfer (usually for dynamic memory or resources that cannot be copied).
     The copy constructor and copy assignment operator are deleted, so copying is prevented, but moving (transfer of ownership) is still allowed.
     4. Using std::unique_ptr for Exclusive Ownership
     If your object involves resource management (like dynamic memory allocation), it might be useful to use std::unique_ptr to enforce exclusive ownership of a resource. A unique_ptr can only be moved, not copied, thus ensuring that only one object "owns" the resource at any given time.
     
     Example:
     cpp
     Copy
     #include <iostream>
     #include <memory>
     using namespace std;
     
     class MyClass {
     public:
         MyClass() {
             cout << "Constructor called\n";
         }
     
         // Deleting the copy constructor and copy assignment operator
         MyClass(const MyClass&) = delete;           
         MyClass& operator=(const MyClass&) = delete;
     
         // Default constructor and move semantics are still allowed
         MyClass(MyClass&&) noexcept { 
             cout << "Move constructor called\n";
         }
         
         MyClass& operator=(MyClass&&) noexcept { 
             cout << "Move assignment operator called\n";
             return *this;
         }
     
         void print() const {
             cout << "MyClass instance\n";
         }
     };
     
     int main() {
         std::unique_ptr<MyClass> obj1 = std::make_unique<MyClass>();
         obj1->print();
     
         // std::unique_ptr doesn't allow copying, only moving
         std::unique_ptr<MyClass> obj2 = std::move(obj1);  // This works, move semantics
     
         return 0;
     }
     Output:
     
     pgsql
     Copy
     Constructor called
     Move constructor called
     Summary
     To protect an object from being copied in C++, you have several options:
     
     Delete the copy constructor and copy assignment operator: This completely prevents copying.
     Make the copy constructor and copy assignment operator private: This restricts copying to within the class, but it's still technically possible using friends or within the class.
     Use move semantics: If you still want to allow moving objects, delete the copy constructor and copy assignment operator and define move semantics (move constructor and move assignment operator).
     Use std::unique_ptr: For exclusive ownership of resources, use std::unique_ptr, which automatically ensures objects cannot be copied but can be moved.
