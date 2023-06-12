/**
 * Parisa Nawar
 * pxn210032
 */
#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <fstream>
#include <vector>

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
};

#endif //GRAPH_H
