#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool LoadFile(string filename, int data[][9]) {
    ifstream file;
    string line, num;
    int row = 0, col = 0, stToNum = 0;
    
    file.open(filename);
    if(!file.is_open()) {
        cout << "Error reading file." << endl;
        return false;
    }
    
    /**if(is_empty(file)) {
        cout << "Error reading file." << endl;
        return false;
    } */
    
    while(getline(file, line)) {
        col = 0;
        for(size_t i = 0; i < line.size(); i++) {
            if(isdigit(line.at(i))) {
                num = line.at(i);
                stToNum = stoi(num);
                data[row][col] = stToNum;
                col++;
            }
        }
        row++;
    }
    
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(data[i][j] < 1) {
                cout << "Error reading file." << endl;
                return false;
            }
        }
    }
    
    file.close();
    return true;
}

bool TestRow(const int data[][9] , int row) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(data[row][i] == data[row][j] && i != j) {
                cout << "Row " << row + 1 << " is invalid." << endl;
                return false;
            }
        }
    }
    return true;
}

bool TestColumn(const int data[][9], int col) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(data[i][col] == data[j][col] && i != j) {
                cout << "Column " << col + 1 << " is invalid." << endl;
                return false;
            }
        }
    }
    return true;
}

bool TestBox(const int data[][9], int box) {
    int boxCheck[9];
    int count = 0;
    
    if(box == 0) { // Box 1
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                boxCheck[count] = data[i][j];
                count++;
            }
        }
        
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(boxCheck[i] == boxCheck[j] && i != j) {
                    cout << "Box 1 is invalid." << endl;
                    return false;
                }
            }
        }
    }
    else if(box == 1) { // Box 2
        for(int i = 0; i < 3; i++) {
            for(int j = 3; j < 6; j++) {
                boxCheck[count] = data[i][j];
                count++;
            }
        }
        
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(boxCheck[i] == boxCheck[j] && i != j) {
                   cout << "Box 2 is invalid." << endl;
                    return false; 
                }
            }
        }
    }
    else if(box == 2) { // Box 3
        for(int i = 0; i < 3; i++) {
            for(int j = 6; j < 9; j++) {
                boxCheck[count] = data[i][j];
                count++;
            }
        }
        
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(boxCheck[i] == boxCheck[j] && i != j) {
                   cout << "Box 3 is invalid." << endl;
                    return false; 
                }
            }
        }
    }
    else if(box == 3) { // Box 4
        for(int i = 3; i < 6; i++) {
            for(int j = 0; j < 3; j++) {
                boxCheck[count] = data[i][j];
                count++;
            }
        }
        
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(boxCheck[i] == boxCheck[j] && i != j) {
                   cout << "Box 4 is invalid." << endl;
                    return false; 
                }
            }
        }
    }
    else if(box == 4) { // Box 5
        for(int i = 3; i < 6; i++) {
            for(int j = 3; j < 6; j++) {
                boxCheck[count] = data[i][j];
                count++;
            }
        }
        
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(boxCheck[i] == boxCheck[j] && i != j) {
                   cout << "Box 5 is invalid." << endl;
                    return false; 
                }
            }
        } 
    }
    else if(box == 5) { // Box 6
        for(int i = 3; i < 6; i++) {
            for(int j = 6; j < 9; j++) {
                boxCheck[count] = data[i][j];
                count++;
            }
        }
        
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(boxCheck[i] == boxCheck[j] && i != j) {
                   cout << "Box 6 is invalid." << endl;
                    return false; 
                }
            }
        }
    }
    else if(box == 6) { // Box 7
        for(int i = 6; i < 9; i++) {
            for(int j = 0; j < 3; j++) {
                boxCheck[count] = data[i][j];
                count++;
            }
        }
        
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(boxCheck[i] == boxCheck[j] && i != j) {
                   cout << "Box 7 is invalid." << endl;
                    return false; 
                }
            }
        }
    }
    else if(box == 7) { // Box 8
        for(int i = 6; i < 9; i++) {
            for(int j = 3; j < 6; j++) {
                boxCheck[count] = data[i][j];
                count++;
            }
        }
        
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(boxCheck[i] == boxCheck[j] && i != j) {
                   cout << "Box 8 is invalid." << endl;
                    return false; 
                }
            }
        }
    }
    else if (box == 8) { // Box 9
        for(int i = 6; i < 9; i++) {
            for(int j = 6; j < 9; j++) {
                boxCheck[count] = data[i][j];
                count++;
            }
        }
        
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(boxCheck[i] == boxCheck[j] && i != j) {
                   cout << "Box 9 is invalid." << endl;
                    return false; 
                }
            }
        }
    }
    return true;
}

void Display(const int data[][9]) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            cout << data[i][j];
        }
        cout << endl;
    }
}

int main()
{
    string fName;
    int suSquare[9][9];
    bool valid = 1;
    
    cout << "Enter the filename: ";
    cin >> fName;
    
    if(LoadFile(fName, suSquare) == 1) {
        Display(suSquare);
        
        for(int i = 0; i < 9; i++) {
            if(TestRow(suSquare, i) == 0) {
                valid = 0;
            }
        }
        for(int i = 0; i < 9; i++) {
            if(TestColumn(suSquare, i) == 0) {
                valid = 0;
            }
        }
        for(int i = 0; i < 9; i++) {
            if(TestBox(suSquare, i) == 0) {
                valid = 0;
            }
        }
    
        if(valid == 1) {
            cout << "The solution is valid." << endl;
        }
    }
}
