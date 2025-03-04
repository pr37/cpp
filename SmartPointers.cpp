std::unique_ptr, std::shared_ptr, and std::weak_ptr - ovo su sve smart pointeri

#include <memory> tu su smart pointeri = cilj je da se alokacija resursa desi istog momenta kad se inicijalizuje
objekat 
unique - jedan objekat po pointeru
shared - vise objekata po pointeru
weak - pokazivac na objekat koji je u nekom unique ili shared pointeru ali se ne broji kao referenca
RAII 

auto instanca_klase = std:make_unique<Klasa>(value_za_konstruktor);  // unique pointer na heapu Cpp14
auto instanca = std:unique_ptr<Klasa>(new Klasa(val)); // Cpp11

Kako se implementira menadzer resursa:

imamo neku klasu Klasa1

class Klasa1ResourceManager {
    public:
        explicit Klasa1ResourceManager(int value) : //https://www.geeksforgeeks.org/use-of-explicit-keyword-in-cpp/
            pointer_to_instance(new Klasa1(value)) {}

        ~Klasa1ResourceManager() {
            delete pointer_to_instance;
        }

        const Klasa1 &get_instance const { //const Klasa1 & - reference to the Klasa1 object being returned is constant 
            //const at the end of the method means that the method does not modify the state of the object on which it is called.
            //This is often used for getter methods
            return *pointer_to_instance;
        }
    private:
        Klasa1ResourceManager(const Klasa1ResourceManager &other);
        void operator=(const Klasa1ResourceManager &other);
        Klasa1 * pointer_to_instance;

}

Resource Acquisition is Initialization (RAII)?
It's a really terrible name for an incredibly powerful concept,
 and perhaps one of the number 1 things that C++ developers miss when
  they switch to other languages. There has been a bit of a movement to try
   to rename this concept as Scope-Bound Resource Management, though it doesn't 
   seem to have caught on just yet.

When we say 'Resource' we don't just mean memory - it could be file handles, network sockets,
 database handles, GDI objects... In short, things that we have a finite supply of and so we
  need to be able to control their usage. The 'Scope-bound' aspect means that the lifetime of
   the object is bound to the scope of a variable, so when the variable goes out of scope then
    the destructor will release the resource. A very useful property of this is that it makes
     for greater exception-safety. For instance, compare this:

RawResourceHandle* handle=createNewResource();
handle->performInvalidOperation();  // Oops, throws exception
...
deleteResource(handle); // oh dear, never gets called so the resource leaks
With the RAII one

class ManagedResourceHandle {
public:
   ManagedResourceHandle(RawResourceHandle* rawHandle_) : rawHandle(rawHandle_) {};
   ~ManagedResourceHandle() {delete rawHandle; }
   ... // omitted operator*, etc
private:
   RawResourceHandle* rawHandle;
};

ManagedResourceHandle handle(createNewResource());
handle->performInvalidOperation();
In this latter case, when the exception is thrown and the stack is unwound, 
the local variables are destroyed which ensures that our resource is cleaned up and doesn't leak.


The key to the implementation of unique_ptr is to enforce that only one unique_ptr owns an object at any given time. H
ere's how this is achieved:

No Copying:

The copy constructor and copy assignment operator are deleted (i.e., explicitly made unavailable).
 This means you cannot copy a unique_ptr. This prevents two unique_ptrs from simultaneously owning the same object.
If you try to copy a unique_ptr, the compiler will give you an error, ensuring that the object is not accidentally
 shared between multiple unique_ptrs.
cpp
Copy
unique_ptr<int> p1 = std::make_unique<int>(10);
unique_ptr<int> p2 = p1;  // Error: copy constructor is deleted

// Deleted copy constructor (prevents copying of unique_ptr)
unique_ptr(const unique_ptr&) = delete;

// Deleted copy assignment operator (prevents copying of unique_ptr)
unique_ptr& operator=(const unique_ptr&) = delete;


std::shared_ptr is another smart pointer in C++ that allows shared ownership of an object.
 This means that multiple shared_ptrs can point to the same object, and the object will only be
  destroyed when the last shared_ptr that owns it is destroyed or reset.

  Unique_ptr is a pointer that implements RAII. When the pointer goes out of scope, the memory it owns is destroyed. This necessitates that it is the sole owner of the pointed-to memory (making it unique). Its copy constructor is delete using "=delete"
  Shared_ptr is another RAII pointer, but the pointed-to memory is not destroyed until the last shared_ptr pointing to the memory goes out of scope. There is a shared control block with a reference counter that is visible to all shared_ptrs pointing to the same object.

  what is the point of shared pointers?
ChatGPT said:
std::shared_ptr is a type of smart pointer in C++ that automatically manages the lifetime of a dynamically allocated object. The key feature of shared_ptr is its reference counting mechanism, which ensures that the object it points to is destroyed only when all shared_ptr instances that point to that object are out of scope or reset.

What Does std::weak_ptr Do?
A weak_ptr is a smart pointer that does not affect the reference count of the object it points to. It is used to observe (but not own) an object that is owned by a std::shared_ptr. The key difference is that a weak_ptr does not prevent the object from being destroyed.

You can think of std::weak_ptr as a non-owning reference to an object. It allows you to observe the object without contributing to its reference count.

How std::weak_ptr Solves Circular References:
Instead of having a std::shared_ptr pointing to both A and B, we can use a std::weak_ptr for the back references between A and B. This breaks the cycle of ownership, so when the last shared_ptr goes out of scope, the objects can be deleted properly.

unique_ptr<int> p = make_unique<int>(5);
//unique_ptr<int> p2 = p; ne sme
shared_ptr<int> ps = make_shared<int>(6);
//shared_ptr<int> p2 = p; ne sme
shared_ptr<int> p2;
p2 = ps;
cout << *ps << endl << *p2 << endl;
cout << *p << endl;
weak_ptr<int> p3;
p3 = ps;
cout << ps.use_count() << endl; //p.use_count() za brojanje shared pok
