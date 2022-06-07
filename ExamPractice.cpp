//
// Created by Chris Kay on 2022/05/20.
// Test locally or copy and paste to http://cpp.sh/
//

//ExamPractice Driver File

//#include "ExamPractice.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>


/*
List all aspects to be practiced.
 */
static_assert(not (1==2));
//std::invokable;
//std::is_same<T,U>;


// Class Declarations


class Base{
public:
    //public class members
    int x;
    //constructor
    Base(int x, int y, int z) : x(x), y(y), z(z) {};

    // public operator overloading
    int operator()(int i, int j){
        return x+y;; // (x,y) overload
    };
    Base operator+( const Base & rhs){
        this->x = this->x - rhs.x;
        this->y = this->y + rhs.y;
        return *this;
    }

    //public getter method
    int getY(void){
        return this->y; //explicit else just y would do or (*this).y
    }

    std::string getSecretVault(){
        return bestySecretVault;
    }

    //hommies declaration both function and class.
    //A hommie can access the private and protected members of the class in which it is declared as a friend.
    friend void bff( Base & base);
    friend class Besty;
    //Note 1=> friend Base & operator+( Base & lhs, const Base & rhs);

private:
    int y;
    std::string bestySecretVault;

protected:
    int z;
};

//External Free function Base overloads for + and ()
/*
//include lhs & rhs when outside class.
//operator+ in your example is a member function so it can access all the private fields just fine. If you overload some operator as a free function it would be required to be a friend to access non-public fields. –

Base & operator+( Base & lhs, const Base & rhs){
    lhs.x -= rhs.x;
    //Note1 => lhs.y += rhs.y; //to overload when accessing private members, make friend, else overload as class member.
    return lhs;
 }

//can be defined outside class as long as it had been declared.

int Base::operator()(int i, int j){
    return x+y;
}
*/

//function and class hommies definitions.
void bff( Base & b){
    std::cout << "I can access friend's private parts and modify y from "<< b.y << " to " << ++b.y;
};

class Besty{
public:
    Besty(void){}
    void secret (Base &base){
        std::cout <<"\nI can access Base's pvt members directly: " << base.y ;
    }
    void KeepSecretWithBase(Base &base){
        base.bestySecretVault = "I use spaces instead of tabs.";
    }
};
/*
 //construct besty by passing Base as argument also works.
class Besty{
public:
    Base b;
    Besty(Base b): b(b){}
    void secret (void){
        std::cout << b.getY() << "\n" << b.y ;
    }

};

*/

class ThirdFriend: public Base, public Besty{
//interesting case where Besty is a friend class for Base and both have been inherited, giving ThirdFriend
//access to both methods, and example adds secret to Base pvt using function in Besty class.
// demonstrates multiple inheritance incl constructor structure, and usage.
public:
    ThirdFriend(int x, int y, int z): Base(x,y,z) {
    };
};

void operatorOverloadingExample () {
    //error occurs if you try to use an operator which has not yet been overloaded.
    std::cout << "OPERATOR OVERLOADING EXAMPLE \n";
    Base a(10, 6, 1);
    Base b(30,6, 1);
    Base c = a + b; //invert + to subtract.
    std::cout <<  "New C's x is: " << c.x;
    std::cout <<  "\nNew C's y is: " << c.getY() << std::endl;

    //what happens to y when those r added? nothin unaffected.
    c(3,4); // overloading ()
    std::cout << "Editing y through an overloaded method then accesing:" << c.getY();
}

void friendFunctionExample () {
    std::cout << "FRIEND EXAMPLE \n";
    Base b(30,5,1);
    bff(b); //prints x and y of b.
    Besty a;
    a.secret(b);
    std::cout << std::endl;
}

void friendsExample(){
    //Third friend Tells secret from Besty to Base. Base stores secret. She knew coz she is a mutual friend.
    ThirdFriend k(10, 20, 30);
    std::cout << "Empty Secret Vault:" << k.getSecretVault() << std::endl;
    k.KeepSecretWithBase(k);
    std::cout << "Vault Secret:" << k.getSecretVault() << std::endl;
}


//basic class wrapping an int
//std::ostream & operator<<(std::ostream & os, const GrandChild & gc){
//    os << gc.name + " "+ gc.totem;
//    return os;
//}

namespace operatorOverloads {
    //+,-,+=,-=, <<, etc
    using namespace std;
    class Date
    {
        int mo, da, yr;
    public:
        Date(int m, int d, int y)
        {
            mo = m; da = d; yr = y;
        }
        friend ostream& operator<<(ostream& os, const Date& dt);
    };
    ostream& operator<<(ostream& os, const Date& dt)
    {
        os << dt.mo << '/' << dt.da << '/' << dt.yr;
        return os;
    }

    class MyInt {
    private:
        int i;
    public:
        MyInt(int i): i(i){};
        MyInt(){}
        friend std::ostream & operator<<(std::ostream & os, const MyInt & in);
    };
    std::ostream & operator<<(std::ostream & os, const MyInt & in){
        os << in.i;
        return os;
    }

//    void insertionOverloading(void){
//        operatorOverloads::MyInt a(2);
//        std::cout << a;
//
//        GrandChild albon(45,50,60, "JOhn", "Wick");
//        std::cout<< albon;
//    }

    void ostreamOverload (){
    Date dt(5, 6, 92);
    cout << dt;
    }

}

int main(int argc, char * argv[] ) {
    //Pointers::pointerRefExample();
    using std::cout;
    //using namespace std;
    //cout << argv[0] << " " << argc;
    //operatorOverloadingExample();
    //operatorOverloads::ostreamOverload();
    //insertionOverloading();
    // practices + and ()
    //    overloading.TODO
    //    add[]
    //    indexing
    //    overloading
    //    insertionOperatorOverload();
    // friendFunctionExample();

//int arr[3] = {3,4,6};
//for(int a : arr){
//    std::cout << &a << " " << a << std::endl; //moves to new address, overwrites same address on each iteration. Clever!
//}


//std::vector<int> k(arr,arr+3);
//
//for (int j: k) {
//    std::cout << j;
//}
//std::cout << k.size();
//operatorOverloading::ostreamOverload();
    //templates example, functors (Function Objects [py dic comprehension]), concepts.
    //demo  copy_if, fill, for_each, transform, if_condition, etc.
    //restrictions
}