#include <iostream>
#include "rwl.h"
#include <fstream>
#include <vector>

RWLock rwlock;

vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

void reader(const char* name) {
    rwlock.lockR();
    
    ofstream fOut(name);
    for (int i(0); i < arr.size(); i++) {
        fOut << arr[i] << " ";
    }
    
    rwlock.unlockR();
}

void print() {
    rwlock.lockR();
    
    for (int i(0); i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    
    rwlock.unlockR();
}

void writer (initializer_list<int> list) {
    rwlock.lockW();
    arr.insert(arr.end(), list);
    rwlock.unlockW();
}

int main() {
    
    thread reader1 (reader, "thread1");
    thread reader2 (reader, "thread2");
    
    initializer_list<int> x = {16, 17, 18};
    thread writer1 (writer, x);
    
    reader1.join();
    reader2.join();
    writer1.join();
    
    thread reader3 (print);
    reader3.join();
    
    return 0;
}