The C++11 standard introduced <thread>, which provides support for threads in C++.
std::thread: A class used to manage threads. It allows you to run a function in a separate thread.

std::thread t(function_name);  // Creates a new thread
t.join();                      // Waits for the thread to finish


join(): Waits for the thread to complete before proceeding (blocking).
detach(): Allows the thread to run independently from the calling thread. You don't wait for it to finish.

Race Conditions: Occur when multiple threads access shared data concurrently, leading to unpredictable results.
Mutexes (std::mutex): Used to synchronize access to shared resources and prevent race conditions. Used to lock and 
unlock shared data to ensure that only one thread accesses it at a time.

A thread pool is a collection of pre-created threads that can be reused to execute tasks, reducing the overhead of creating and destroying threads.

Deadlocks: Occur when two or more threads wait indefinitely for each other to release resources.
Race Conditions: Occur when threads access shared data concurrently in an unpredictable way.
