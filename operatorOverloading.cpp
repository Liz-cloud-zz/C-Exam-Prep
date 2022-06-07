//
// Created by Chris Kay on 2022/06/03.
//

#include <iostream>
#include <string>

//>>, <<, +, -, /, *, +=, *=, -=,!=, ++, —, [], (), >,<,~
using namespace std;
class Person {
public:
    string firstname;
    string middlename;
    string lastname;
    int age;
    char gender; // M/F
    Person(string first, string mid, string last, int age, char gender ): firstname(first), middlename(mid), lastname(last), age(age), gender(gender){
        setNet();
    }
    void setNet(){ netWorth=34; }
    friend std::ostream & operator<<(std::ostream & out, const Person & rhs); //could have been defined here as well. Friend MUST stay {}
    friend std::istream & operator>>(std::istream & in, Person & rhs){
        in >> rhs.netWorth >> rhs.age;
        return in;
    };
    void operator~(void){ gender='F'; } // unary overload.
    void operator+(int value){ netWorth+=value; }

    Person operator+(const Person & rhs){
        Person temp = *this;
        temp.firstname += " " + rhs.firstname;
        temp.middlename += " " + rhs.middlename;
        temp.lastname += " " + rhs.lastname;
        temp.age += rhs.age;
        temp.netWorth += rhs.netWorth;
        return temp;
    }
    friend Person & operator-=(Person & lhs ,const Person & rhs);
private:
    int netWorth;
};

// << operator can done outside class once friended.
std::ostream & operator<<(std::ostream & out, const Person & rhs){
    out << rhs.firstname + " " + rhs.middlename << " " << rhs.lastname << " " << rhs.age << " " << rhs.netWorth << " " << rhs.gender << endl;
    return out;
}

Person & operator-=(Person & lhs, const Person & rhs){
    lhs.age-=rhs.age;
    lhs.netWorth-= rhs.netWorth;
    return lhs;
}


int main(){
    Person myPerson("John", "Tobias", "Wick", 24, 'M');
    Person yoPerson("Meriam", "Rue", "Slack", 19, 'F');

    cout << myPerson;
    ~myPerson; // changes gender
    cout << myPerson;
    myPerson+4; //increases netWorth
    cout << myPerson;

    Person rt =  myPerson + yoPerson;
    cout << rt;

    myPerson -=yoPerson;
    cout << myPerson;

    cin >> myPerson; // input two digits.
    cout << myPerson;

}
//https://www.learncpp.com/cpp-tutorial/overloading-the-arithmetic-operators-using-friend-functions/