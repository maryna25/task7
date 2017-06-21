#ifndef rwl_h
#define rwl_h

#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class RWLock {
private:
    size_t counter = 0;
    mutex g;
    mutex r;
public:
    
    RWLock();
    
    void lockW();
    void unlockW();
    void lockR();
    void unlockR();
    
    ~RWLock();
};

RWLock::RWLock() {}

RWLock::~RWLock() {}

void RWLock::lockW() {
    g.lock();
}

void RWLock::unlockW() {
    g.unlock();
}

void RWLock::lockR() {
    unique_lock<mutex>(r);
    counter++;
    if (counter == 1) { g.lock(); }
}

void RWLock::unlockR() {
    unique_lock<mutex>(r);
    counter--;
    if (counter == 0) { g.unlock(); }
}


#endif /* rwl_h */