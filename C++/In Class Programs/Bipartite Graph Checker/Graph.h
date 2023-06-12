//Parisa Nawar pxn210032
// Aman Verma axv190078
#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <fstream>
#include <vector>
#include <queue>

class Graph {
    private:
        int** data;
        int curSize;
        int maxSize;
        
    public:   
        Graph();
        Graph(int maxSize);
        bool isEmpty();
        void createGraph(std::ifstream&);
        void isConnected();
        void DFS(int ind, std::vector<bool>&);
        void isBipartite();
};

#endif //GRAPH_H
