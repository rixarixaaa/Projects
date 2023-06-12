//Parisa Nawar pxn210032
// Aman Verma axv190078
#include "Graph.h"

#include <iostream>
#include <cstring>   
#include <fstream>
#include <vector>
#include <queue>

int** data;
int curSize;
int maxSize;

Graph::Graph() {
    curSize = 0;
    maxSize = 10;
    
    data = new int*[maxSize + 1];
    
    for (int i = 0; i < maxSize+1; i++) {
        data[i] = new int[maxSize+1];
    }
}

Graph::Graph(int maxSize) {
    curSize = 0;
    this->maxSize = maxSize;

    data = new int*[maxSize + 1];
    
    for (int i = 0; i < maxSize+1; i++) {
        data[i] = new int[maxSize+1];
    }
}
    
bool Graph::isEmpty() {
    if(curSize == 0) {
        return true;
    }
    else {
        return false;
    }
}
    
void Graph::createGraph(std::ifstream& f) {
    std::string line;
    int ver, ind;
    
    getline(f, line);
    
    maxSize = stoi(line);
    data = new int*[maxSize + 1];
    
    for (int i = 0; i < maxSize + 1; i++) {
        data[i] = new int[maxSize + 1];
    }
    
    while(getline(f, line)) {
        ind = stoi(line.substr(0, 1));
        int size = static_cast<int>(line.size());
            
        for(int i = 1; i < size; i++) {
            if(isdigit(line.at(i))) {
                ver = stoi(line.substr(i,1));
                    
                data[ind][ver] = 1;
            }
        }
            
    }
}

void Graph::isConnected() {
    std::vector<bool>visit(maxSize + 1, false);
    
    bool connected = true;
    
    for(int i = 1; i < maxSize + 1; i++) {
        for(int j = 1; j < maxSize + 1; j++) {
            visit[j] = false;
        }
        
        DFS(i, visit);
        
        for(int j = 1; j < maxSize + 1; j++) {
            if(visit[j] == false) {
                std::cout << "not connected";
                connected = false;
                break;
            }
        }
    
        if(connected == false) {
            break;
        } 
    }
    
    if(connected == true) {
        std::cout << "connected";
    }
}

void Graph::DFS(int ind, std::vector<bool>& arr) {
    arr[ind] = true;
    
   for(int j = 1; j < maxSize + 1; j++) {
       if(data[ind][j] == 1 && arr[j] == false) {
           DFS(j, arr);
        }
    }
}


void Graph::isBipartite() {
    std::vector<int>color(maxSize + 1, -1);
    bool bipartite = true;
    
    color[1] = 1;
    
    std::queue<int> q;
    q.push(1);
    
    while(!q.empty()) {
        int color1 = q.front();
        q.pop();
        
        if(data[color1][color1] == 1) {
            bipartite = false;
        }
        
        for(int i = 1; i < maxSize + 1; i++) {
            if(data[color1][i] == 1 && color[i] == -1) {
                if (color[color1] == 0)
                    color[i] = 1;
                else if (color[color1] == 1)
                    color[i] = 0;
                    
                q.push(i);
            }
            else if(data[color1][i] == 1 && color[i] == color[color1]) {
                bipartite = false;
            }
        }
    }
    
    if(bipartite == true) {
        std::cout << "Bipartite" << std::endl;
    }
    else if(bipartite == false) {
        std::cout << "Not bipartite" << std::endl;
    }
    
}

   
