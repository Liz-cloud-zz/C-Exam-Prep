//
// Created by Chris Kay on 2022/05/27.
//
//Source definition file.
#include <memory>
#include <iostream>
#include <stdint.h>
//int64_t -> 64 bit int.
using namespace std;

class MyInt {
private:
    int i;
public:
    MyInt(int i): i(i){};
    MyInt(): i(77){} //Default constructor - array construction fails without
    friend std::ostream & operator<<(std::ostream & os, const MyInt & in);
    friend void dynamicMemory(); //friend so function can access private i.
    ~MyInt(){cout<< i << " Destroyed \t";}
};
std::ostream & operator<<(std::ostream & os, const MyInt & in){
    os << in.i;
    return os;
}
void sharedPtrByValue(std::shared_ptr<int> a){
    cout << "ByValue: sharedPtr ref count now: " << a.use_count() << endl; // count increases because of local copy.

    {
        shared_ptr<int> b = a;
        cout << "ByRef: sharedPtr ref after copying: count now:" << b.use_count() << "==" << a.use_count() << endl;
    }
    cout << "ByValue: sharedPtr ref count after b leaving scope now: " << a.use_count() << endl;
}
void sharedPtrByRef(std::shared_ptr<int> &a){
    cout << "ByRef: sharedPtr ref count stays at One: " << a.use_count() << endl;
}

std::unique_ptr<int> uniqueHotPotato(std::unique_ptr<int> b){
    b.reset(new int(8080));
    return std::move(b);
}

void sharedPointersExample(){
//        std::shared_ptr<int>(new int(10)); //make_shared
//        int *ptr = new int(20)
//        std::shared_ptr<int> ptr = std::make_shared<int>(10);

    std::shared_ptr<int> number1 = std::make_shared<int>(111); //explicit decl. //HEAP OR NOT?
    std::shared_ptr<int> number2(new int(222)); // direct instantiation (preferred)
    auto number3 = std::make_shared<int>(333); // no use of new. uses auto
    std::cout << *number1 << " " << *number2 << " " << *number3 << " " << std::endl ;

    sharedPtrByValue(number1);
    sharedPtrByRef(number1);

    std::shared_ptr<int> bar = std::make_shared<int> (10);
    std::shared_ptr<MyInt> bar1 = std::make_shared<MyInt> (100);
    //std::shared_ptr<T> varName = make_shared<T>(constructorArgs);

    // same as:
    std::shared_ptr<int> foo2 (new int(10));
    auto baz = std::make_shared<std::pair<int,int>> (30,40);

    std::cout << "*bar: " << *bar << '\n' << bar.use_count();
    std::cout << "*baz: " << baz->first << ' ' << baz->second << '\n';

    // add passing of shared pointer by value, reference, check use_count.
    //move pointer in a function

    // TODO update and incorporate code
}

void uniquePointersExample() {
    //zero overhead compared to raw pointers.

    //moving between unique_ptrs
    std::unique_ptr<int> lhs(new int(20));
    std::unique_ptr<int> rhs(new int(207));
    rhs = std::move(lhs);
    std::cout << *rhs << std::endl; //rhs now points to 20, lhs now nullptr

    unique_ptr<int> newPtr = uniqueHotPotato(std::move(lhs));
    cout << "Successfully hotPotatoed uniquePtr: " << *newPtr << endl;

    //unique_ptr to shared_ptr
    std::unique_ptr<std::string> name = std::make_unique<std::string>("sdfsdssd");
    std::shared_ptr<std::string> name1 = std::move(name);
    void * p = nullptr;
    std::cout << "Name now nullptr: " << p << " same as: " << name << std::endl;
    std::cout << "Unique pointer moved to shared: " << &name1 << std::endl;

    rhs.release(); //now nullptr
    rhs.reset(new int(10)); //lhs reset to new ptr pointing to 10.
}
void weakPointersExample() {
    std::shared_ptr<int> node0(new int(222)); // direct instantiation (preferred)
    std::weak_ptr<int> node1(node0);

    cout << node1.use_count();//
    {
    std::shared_ptr<int> spt = node1.lock();//make shared copy of weak.
    std::cout << "*spt == " << *spt << '\n';
    cout << "use count within scope now: " << spt.use_count() << endl;
    }
    cout << "use count after leaving scope now: " << node1.use_count() << endl;

}
void pointerRefExample (){
    std::cout << "POINTERS & REFs EXAMPLE \n";
    // &ref, pointer, initialization.
    int j(10);
    int *k = &j;
    int & l = j;
    std::cout << "j, k & l same: \n" << "j:" << &j << "\nk:" << k << "\nl:" << &l << std::endl;

    int b(10); int *intPointer = &b;
    int *heapPtr = new int(10);
    std::cout << "Comparison of hex digits / bits: \nStck size: " << sizeof(intPointer) << std::dec << std::endl << "Heap size: " << sizeof(heapPtr) << std::dec << std::endl;
    std::cout << "\nYou can get the the address a pointer stores: " << intPointer << "\nThe value of that address:" << *intPointer <<" \nThe address of the pointer variable itself on the stack: "<< &intPointer << std::endl;

    int c(3);
    int &ref = c;
    int * ptr = &c;
    cout << c << " " << *ptr;

}
void pointerArithmeticExample (){
    std::cout << "POINTER ARITHMETIC EXAMPLE \n";
    int arr[5] = {1,2,3,4,5}; //4Bytes each
    // int arr[5] = {1,2,3,4,5}; //8Bytes each
    // NB: 0x16d2a7708 - 0x16d2a7710 = 0x8 - 8,9,a,b,c,d,e,0
    std::cout << "Element and address:\n";
    for (int i=0; i<5; i++){
        std::cout << *(arr+i) << " Address:" << arr+i << " Size(B):"  << sizeof(*(arr+i))<< std::endl;
    }

    std::cout << "Method 1:\n";
    for (int i=0; i<5; i++){
        std::cout << *(arr+i) << " ";
    }
    std::cout << "\nMethod 2:\n";
    for (int a: arr){
        std::cout << a << " ";
    }
    std::cout << "\nMethod 3:\n";
    for (int i=0; i<5; i++){
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    //WORD EXAMPLE.
    char word[4]={'w','o','r','d'};
    for (int i = 0; i < 4; ++i) { //++i faster than i++
        cout << *(word+i);
    }
    for (int i = 0; i < 4; ++i) { //++i faster than i++
        cout << word[i];
    }
    for (char * i = word; i!=word+4; ++i){
        cout << *i;
    }
}

void rawPointers(){
    char a = 'a';
    char * ptr = &a;
    char ** ptr1 = &ptr;
    char *** ptr2 = &ptr1;
    char ****ptr3 = & ptr2; //pointer 3 to pointer 2 to pointer 1 to pointer to char.
    std::cout << *(*(*(*ptr3)));

    //int* pt = 0xFFFFFFA0;//new int(1);//NULL;
    //    int * ptrNull = nullptr;
    //    cout<< (ptrNull);
}

void dynamicMemory(){
    //SINGLE ALLOCATION
    MyInt * intPtr = new MyInt(4);
    delete intPtr;

    //ARRAY ALLOCATION
    MyInt *ints = new MyInt[10];
    for( int i = 0; i<10; i++){
        cout << (ints+i)->i << " ";
        *(ints+i) = MyInt(i); // replace MyInt.
        cout << (ints+i)->i << " \t";
    }
    delete [] ints;

    //ARRAY OF POINTERS ALLOCATION
    MyInt ** MyIntPtrs = new MyInt * [3];

    for( int i = 0; i<3; i++){
        MyIntPtrs[i] = new MyInt(i); // each of the 3 pointers now holds a pointer to memory of just created MyInts.
    }

    for( int i = 0; i<3; i++) {
        delete *(MyIntPtrs+i); //delete each of the allocated pointers. Linearly / Flat array view.
        //delete MyIntPtrs[i]; //easier way
    }

    delete [] MyIntPtrs;

    }

int main(){
//    sharedPointersExample();
//    uniquePointersExample();
    weakPointersExample();
//    pointerRefExample();
//    pointerArithmeticExample();
//    rawPointers();
//    dynamicMemory();
}