//Parisa Nawar
//pxn210032
#include <iostream>
#include <string>

using namespace std;

class StringHash {
   private:
    int size;
    int initialValue;
    int hashMultiplier;
    int relativePrime;
    string* hashTable;
   
   public:
    StringHash(int size, int initialValue, int hashMultiplier, int relativePrime){
       this->size = size;
       this->initialValue = initialValue;
       this->hashMultiplier = hashMultiplier;
       this->relativePrime = relativePrime;
       
       hashTable = new string[size];
       
       for(int i = 0; i < size; i++) {
           hashTable[i] = "<EMPTY>";
       }
   }
   
   int hashMultiplicative1(string data) {
       int stringHash = initialValue;
       
       for(size_t i = 0; i < data.size(); i++) {
           stringHash = (stringHash * hashMultiplier) + data[i];
        }
       
       return abs(stringHash % size);
   }
   
   int hashMultiplicative2(string data) {
       int hashMult = hashMultiplicative1(data);

       return relativePrime - (hashMult % relativePrime);
   }
   
   int hashDouble(int index, string data) {
       int hM1 = hashMultiplicative1(data);
       int hM2 = hashMultiplicative2(data);
       
       return abs((hM1 + (index * hM2)) % size);
   }

   bool contains(string data) {
        int hashi = hashDouble(0, data);
        bool found = false;
        
        cout << "Searching \"" << data << "\"";
        
        for(int i = 0; i < size; i++) {
            hashi = hashDouble(i, data);
            cout << " -> " << hashi;
            
            if(hashTable[hashi] == data) {
                found = true;
                cout << endl << "TRUE" << endl;
                break;
            }
            else if(hashTable[hashi] == "<EMPTY>") {
                found = false;
                cout << " -> FAILED" << endl << "FALSE" << endl;
            }
        }
        
        if(found == false) {
            cout << " -> FAILED" << endl << "FALSE" << endl;
        }
        
        return found;
    }
    
    bool add(string data) {
        bool added = false;
        int hashi = hashDouble(0, data);
        int i = 0;
        
        cout << "Adding \"" << data << "\"";
        
        for(i = 0; i < size; i++) {
            hashi = hashDouble(i, data);
            cout << " -> " << hashi;
                
            if(hashTable[hashi] == "<EMPTY>") {
                added = true;
                hashTable[hashi] = data;
                cout << endl;
                break;
            }
            else if(hashTable[hashi] == data) {
                added = false;
                cout << " -> FAILED" << endl;
                break;
            } 
        }
        
        if(i == size) {
            added = false;
            cout << " -> FAILED" << endl;
        }
        
        return added;
    }
    
    bool remove(string data) {
        bool removed = false;
        int hashi = hashDouble(0, data);
        
        cout << "Removing \"" << data << "\"";
        
        for(int i = 0; i < size; i++) {
            hashi = hashDouble(i, data);
            cout << " -> " << hashi;
            
            if(hashTable[hashi] == data) {
                hashTable[hashi] = "<REMOVED>";
                removed = true;
                cout << endl;
                break;
            }
            else if(hashTable[hashi] == "<EMPTY>") {
                removed = false;
                cout << "-> FAILED" << endl;
                break;
            }
        }
        
        if(removed == false) {
            cout << "-> FAILED" << endl;
        }
        
        return removed;
    }
    
    void displayTable() {
        for(int i = 0; i < size; i++) {
            cout << i << " : " << hashTable[i] << endl;
        }
    } 
    
    void resize() {
        int nHashi;
        int oSize = size;
        size = size * 2; 
    
        string* newHashTable = new string[size];
        
        for(int i = 0; i < size; i++) {
            newHashTable[i] = "<EMPTY>";
        }
        
        for(int i = 0; i < oSize; i++) {
            if(hashTable[i] != "<EMPTY>") {
                if(hashTable[i] != "<REMOVED>") {
                    nHashi = hashDouble(i, hashTable[i]);
                    cout << "Rehashing \"" << hashTable[i] << "\"";
                    for(int j = 0; j < size; j++) {
                       nHashi = hashDouble(j, hashTable[i]); 
                       cout << " -> " << nHashi;
                       
                       if(newHashTable[nHashi] == "<EMPTY>") {
                           newHashTable[nHashi] = hashTable[i];
                           cout << endl;
                           break;
                       }
                    }
                }
            }
        } 
        
        hashTable = newHashTable;
        
    }
};

int main()
{
    int tSize, initialHash, hashMult, relPrime;
    string menuInput = "";
    string hashString;
    
    cout << "Enter table size: ";
    cin >> tSize;
    
    cout << "Enter initial hash value: ";
    cin >> initialHash;
    
    cout << "Enter hash multiplier: ";
    cin >> hashMult;
    
    cout << "Enter relative prime value: ";
    cin >> relPrime;
     
    StringHash* n = new StringHash(tSize, initialHash, hashMult, relPrime);
    
    while(menuInput != "Q" ) {
        cout << "1. Search String" << endl;
        cout << "2. Add String" << endl;
        cout << "3. Remove String" << endl;
        cout << "4. Display Table" << endl;
        cout << "5. Resize Table" << endl;
        cout << "Q. Quit" << endl;
        
        cout << "Choice: ";
        cin >> menuInput;
        
        if(menuInput == "1") {
            cout << "String to search for: ";
            cin >> hashString;
            n->contains(hashString);
        }
        else if(menuInput == "2") {
            cout << "String to add: ";
            cin >> hashString;
            n->add(hashString);
        }
        else if(menuInput == "3") {
            cout << "String to remove: ";
            cin >> hashString;
            n->remove(hashString);
        }
        else if(menuInput == "4") {
            n->displayTable();
        }
        else if(menuInput == "5") {
            n->resize();
        }
    }
    
    
    
    return 0;
}












