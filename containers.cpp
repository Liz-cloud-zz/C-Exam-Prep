//
// Created by Chris Kay on 2022/06/02.
//

#include <memory>
#include <iostream>
#include <vector>
using std::cout; using std::endl;

void vectorIterators (void) {
    int arr[4] = {4, 5, 6, 7};
    std::vector<int> vectName(arr, arr + 4); // initialize with start and 1+end pointers.

    typedef std::vector<int>::const_iterator iter; //make new typedef from old.

    for (iter it = vectName.begin(); it != vectName.end(); it++) {
        cout << *it << endl;
    }
    cout << endl;

    vectName.push_back(8);

    for (int &a: vectName) { // for each returns actual value.
        cout << a << endl;
    }
}

int main(){
    vectorIterators();
}

