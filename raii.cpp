//
// Created by Chris Kay on 2022/06/03.
//

/* RAII for a trivial person class with
 * Default Constructor, ()
 * Copy Constructor, &
 * Move Constructor, &&
 * Copy Assignment Operator, &
 * Move Assignment Operator, &&
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace ClassMember {
    class Person {
    public:
        string fullname;
        Person(string fullname, int SecretsNo, string * scArr=nullptr): fullname(fullname), secretsNo(SecretsNo), secretsArray(new string[secretsNo]){
            std::cout << "Normal Constructor invoked" << std::endl;
            for( int i=0; i<secretsNo; i++){
                secretsArray[i] = "secret";
            }
        } //guard against zero?

        //Default constructor
        Person(): fullname("fullname"), secretsNo(10), secretsArray(new string[secretsNo]){
            std::cout << "Default Constructor invoked" << std::endl;
            for( int i=0; i<secretsNo; i++){
                *(secretsArray+i) = "secret";
            }
        }

        //COPY constructor invoked by: Person b = a; -> a already instantiated.
        Person( const Person & rhs ): fullname(rhs.fullname), secretsNo(rhs.secretsNo), secretsArray(new string[rhs.secretsNo]) { // const coz we want read-only
            std::cout << "COPY Constructor invoked" << std::endl;
            //copy all secrets

            for( int i=0; i<secretsNo; i++){
                cout<< *(rhs.secretsArray+i) << " ";
                *(secretsArray+i) = *(rhs.secretsArray+i);
            }
            cout << endl;
        }

        //MOVE constructor invoked by: Person b = std::move(a); -> a already instantiated.
        // copy plus destroy rhs & clear memory (heap).
        Person( Person && rhs ) {
            std::cout << "MOVE Constructor invoked" << std::endl;
            fullname=std::move(rhs.fullname);
            secretsNo= std::move(rhs.secretsNo); //no effect for ints. just do anyway.
            secretsArray = rhs.secretsArray;
            delete [] rhs.secretsArray; //if on stack, set to nullptr.
            //individual secrets moved by moving address
        }

        //COPY ASSIGNMENT Operator invoked by: b = a; -> a and b already instantiated.
        Person & operator=(const Person & rhs){ // const coz we want read-only
            std::cout << "COPY ASSIGNMENT Operator invoked" << std::endl;
            fullname=rhs.fullname;
            secretsNo= rhs.secretsNo;
            secretsArray = new string[rhs.secretsNo];
            //copy all secrets
            for( int i=0; i<secretsNo; i++){
                *(secretsArray+i) = *(rhs.secretsArray+i);
            }
            return *this;
        }

        //MOVE ASSIGNMENT Operator invoked by: b = std::move(a); -> a and b already instantiated.
        // copy plus destructor
        Person & operator=(Person && rhs){
            std::cout << "MOVE ASSIGNMENT Operator invoked" << std::endl;
            fullname=std::move(rhs.fullname);
            secretsNo= std::move(rhs.secretsNo); //no effect for ints. just do anyway.
            secretsArray = rhs.secretsArray;
            delete [] rhs.secretsArray; //if on stack, set to nullptr.
            //individual secrets moved by moving address
            return *this;
        }
        ~Person(){
            delete[] secretsArray;
            //std::cout << "Destructor invoked" << std::endl;
        }
    private:
        int secretsNo;
        //int * netWorth;
        string * secretsArray; //pointer to secrets memory.

    };

    class Buffer {
    public:
        int N
        float * a;
        const static int DEFAULT_SIZE = 10;
        const static std::string NAME;
        Buffer(int size=DEFAULT_SIZE): N(size=), a(new float [N]){} //get size with default parameter, create a heap pointing pointer.
        ~Buffer(){
            delete[] a;
        }
    };

    const string Buffer::NAME = "MyBuffBuffer";
    // TODO write ALL external raai big 5, write 1 internal and comment out. Edit example to suite past papers.
}

// TODO Non-Class Member example to be used on one and extended to others. friend if need be? Scope resolution is important

int  main(){

    //TODO Fix trying to free unallocated space on move constructor.?

    ClassMember::Person a; //Default Constructor invoked
    ClassMember::Person b = a; //Copy Constructor invoked

    ClassMember::Person c(a); //Copy Constructor invoked - alt syntax
    ClassMember::Person d = std::move(c); //Move Constructor invoked c->d. c now empty.

    c = b; //Copy Assignment Constructor.
    b = std::move(a); //Move Assignment invoked

 ClassMember::Person list[5];
}


// TODO Check trivial past exam papers questions and replicate.