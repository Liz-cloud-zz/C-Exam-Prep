# C++ ExamPrep Repo
Examples on various CPP topics

A file serving as practical revision to a practical C++ course.

### 1. Topics in each file, can be separated by a namespace.
### 2. Add more topics or examples by forking repo and making a PR.
### 3. Feel free to open issues on potential bugs.
### 4. makefile contains targets compiling and running files independently. There is a make all target that compiles and runs all the files. This is done for simplicity as managing header files would have been a nightmare and additional code signatures to write.

# Notes

## 1. C++ Types

Fundamental types in C++ are divided into three categories: integral, floating point, and void. Integral types are capable of handling whole numbers. Floating point types are capable of specifying values that may have fractional parts. The void type describes an empty set of values.

The category integral includes the following datatypes -
```c++
char
bool
short
int
long
long long
wchar_t, __wchar_t
```

The category floating point includes the following datatypes -
```c++
float
double
long double
```

## 2. C++ Concepts

Trivial example:

```c++
template <typename T, typename U, int z >
concept myConcept = std::is_class<T, U> &&
        std::is_integral<z>;

```

## 3. Operator overloading


* OO can be done as class-member (1 argument rhs) or non-member (lhs & rhs) - depending on type of operator. 
* When there is a pvt member involved, use friend.
* += can be returned by reference of modified lhs obj or value of created temp.
* Unary operator takes the format ```void operator~(void){ // body }```
  
## 4. C++ Standard Library Organization

The C++ Standard Library can be categorized into two parts −

    The Standard Function Library − This library consists of general-purpose,stand-alone functions that are not part of any class. The function library is inherited from C.

    The Object Oriented Class Library − This is a collection of classes and associated functions.

Standard C++ Library incorporates all the Standard C libraries also, with small additions and changes to support type safety.
### The Standard Function Library

The standard function library is divided into the following categories −

    I/O,
    String and character handling,
    Mathematical,
    Time, date, and localization,
    Dynamic allocation,
    Miscellaneous,
    Wide-character functions,

### The Object Oriented Class Library

Standard C++ Object Oriented Library defines an extensive set of classes that provide support for a number of common activities, including I/O, strings, and numeric processing. This library includes the following −

    The Standard C++ I/O Classes
    The String Class
    The Numeric Classes
    The STL Container Classes
    The STL Algorithms
    The STL Function Objects
    The STL Iterators
    The STL Allocators
    The Localization library
    Exception Handling Classes
    Miscellaneous Support Library

[Additional STL information.](https://www.geeksforgeeks.org/the-c-standard-template-library-stl/)

### 5. Templates

* Concepts restrict template types for different use cases.
* E.g. A template that takes in an unspecified number of arguments to add together:

#### May need to constrict:
1. Ensure parameters are more than 1: can't add one argument only ,
2. The arguments must have the + operator overloaded and supported.
3. The + operation should be ``` noexcept``` since Add is no except - The noexcept operator performs a compile-time check that returns true if an expression is declared to not throw any exceptions.
4. The return type should match that of Args.

E.g. 2