A function template allows you to define a function that works with any data type.
A class template allows you to define a class that works with any data type.

sintax
template <typename T>

T add(T a, T b) {
    return a + b;
}
//T is a template parameter. It is a placeholder for any data type (like int, float, double, etc.).
//The add function can now be used with any type that supports the + operator.

template <typename T>
class Box {
private:
    T value;
public:
    Box(T val) : value(val) {}
    T getValue() { return value; }
};

Box<int> intBox(100);         // Box of integers
Box<double> doubleBox(3.14);  // Box of doubles


//
Code Reusability: You can write a single function or class that works with multiple data types, avoiding code duplication.
Type Safety: The compiler ensures that only compatible types are used in templates, providing type safety.
Flexibility: Templates allow you to write generic algorithms that work with different types of data, without knowing the exact types in advance.
