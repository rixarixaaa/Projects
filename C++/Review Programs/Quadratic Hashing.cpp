/**
 * Parisa Nawar
 * pxn210032
 */
#include <iostream>

using namespace std;

class quadHash {
    private:
        const double loadFactor = 0.5;
        int* hashArr;
        int hashSize;
        int curSize;
        double loadFctr;
        
    public:
        quadHash();
        quadHash(int s);
        void rehash();
        void quadInsert(int val);
        bool isPrime(int i);
        void printHash();
    
};

int main() {
    int size, val, i = 0;
    quadHash trialHash;

    cin >> size;
    
    while(i < size) {
        cin >> val;
        trialHash.quadInsert(val);
        i++;
    }
    trialHash.printHash();
}

quadHash::quadHash() {
    hashSize = 11;
    hashArr = new int[11];
    for(int i = 0; i < hashSize; i++) {
        hashArr[i] = 0;
    }
    curSize = 0;
}

quadHash::quadHash(int s) {
    hashSize = s;
    hashArr = new int[hashSize];
    curSize = 0;
}

void quadHash::rehash() {
    int j = 0;
    int nSize;
    int* newArr;
    
    nSize = hashSize * 2;
    while(!isPrime(nSize)) {
        nSize++;
    }
    
    newArr = new int[nSize];
    for(int i = 0; i < nSize; i++) {
        newArr[i] = 0;
    } 
    
    for(int i = 0; i < hashSize; i++) {
        j = 0;
        int k = hashArr[i] % nSize;

        while(newArr[(k + j * j) % nSize]) {
            j++;
        }
        newArr[(k + j * j) % nSize] = hashArr[i];
    }
    
    hashSize = nSize;
    hashArr = newArr;
}

void quadHash::quadInsert(int val) {
    int i = 0;
    loadFctr = (1.0 * curSize) / hashSize;
    
    if(loadFctr >= loadFactor) {
        rehash();
    }
    
    int k = val % hashSize;

    while(hashArr[(k + i * i) % hashSize]) {
        i++;
    }
    hashArr[(k + i * i) % hashSize] = val;
    curSize++;
}

bool quadHash::isPrime(int i) {
    if(i <= 1) {
        return false;
    }
    
    for(int k = 2; k < i; k++) {
        if(i % k == 0) {
            return false;
        }
    }
    
    return true;
}

void quadHash::printHash() {
    for(int i = 0; i < hashSize; i++) {
        if(!hashArr[i]) {
            cout << "_" << " ";
        }
        else {
            cout << hashArr[i] << " ";
        }
    }
}











