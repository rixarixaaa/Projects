/**
 * Parisa Nawar
 * pxn210032
 */
 #include "LinkList.h"
 
 #include <cstring>
 #include <iostream>
 #include <vector>
 #include <iomanip>
 
 Node* head;
 
 Linklist::Linklist() {
    head = NULL;
 }
 
/**
 * Function addNode of LinkList class adds each Player object as a Node
 * inside the Linklist, at the end where there is a null. If there is
 * a Player object that is the same as an existing node, then that player 
 * object will be added to an existing node to avoid duplicates
 */
void Linklist::addNode(Player d) {
    Node* newNode = new Node(d);
    Node* curNode;
    
    if(head == NULL) {
        head = newNode;
        return;
    }
    else {
        curNode = head;
    
        while (curNode != NULL) {
            if(*curNode == *newNode) { 
                *curNode += *newNode;
                return;
            } 
            curNode = curNode->next; 
        } 
        
        curNode = head;
        
        while(curNode->next != NULL) {
            curNode = curNode->next;
        }

        curNode->next = newNode;
    }
 }

/**
 * function sortList inside the Linklist class sorts 
 * the Linklist in alphabetical order of the player names
 */
void Linklist::sortList() {
    Node* curNode;
    Node* prevNode;
    
    bool sort = false;
    
    while(!sort) {
        sort = true;
        curNode = head;
        prevNode = head;

        while(curNode != NULL && curNode->next != NULL) {
            if(*(curNode->next) < *curNode) {
                sort = false;
                
                if(curNode == head) {
                    head = head->next;
                    curNode->next = head->next;
                    head->next = curNode;
                }
                else {
                    prevNode->next = curNode->next;
                    curNode->next = curNode->next->next;
                    prevNode->next->next = curNode;
                }
                
            }

            prevNode = curNode;
            curNode = curNode->next;
        }
    } 
}

/**
 * function toString prints out the name and stats of 
 * each Player object by calling the node toString, which calls
 * the Player object toString and recursively prints out every Player 
 * object alphabetically
 */
std::string Linklist::toString() {
      Node* curNode = head;
      
      std::string toStr = "";
      
      while(curNode != NULL) {
          toStr += curNode->toString();
          
          curNode = curNode->next;
      }
      
      return toStr;
  } 

/**
 * printLeaderBA prints out the top leaders of Batting average 
 * by creating three vectors to store players for the top 3 places
 * and pushes down every place if there's a new first place leader,
 * or pushes down bottom two place if there's a new second place leader
 * then prints out each place with commas if there's a tie
 */
void Linklist::printLeaderBA() {
    Node* curNode = head;
    
    std::vector<Node*>firstPlace;
    std::vector<Node*>secondPlace;
    std::vector<Node*>thirdPlace;
    
    while(curNode != NULL) {
        if((!firstPlace.empty()) && curNode->data.calculateBA() == firstPlace[0]->data.calculateBA()) {
            if(curNode != firstPlace[0]) {
                firstPlace.push_back(curNode);
            }
        }
        else if((!secondPlace.empty()) && curNode->data.calculateBA() == secondPlace[0]->data.calculateBA()) {
            if(curNode != secondPlace[0]) {
                secondPlace.push_back(curNode);
            }
        }
        else if((!thirdPlace.empty()) && curNode->data.calculateBA() == thirdPlace[0]->data.calculateBA()) {
            if(curNode != thirdPlace[0]) {
                thirdPlace.push_back(curNode);
            }
        }
        else if((!firstPlace.empty()) && firstPlace[0]->data.calculateBA() < curNode->data.calculateBA()) {
            thirdPlace.clear();
            for(size_t i = 0; i < secondPlace.size(); i++) {
                thirdPlace.push_back(secondPlace[i]);
            }
            
            secondPlace.clear();
            for(size_t i = 0; i < firstPlace.size(); i++) {
                secondPlace.push_back(firstPlace[i]);
            }
            
            firstPlace.clear();
            firstPlace.push_back(curNode);
        }
        else if((!secondPlace.empty()) && secondPlace[0]->data.calculateBA() < curNode->data.calculateBA()) {
            thirdPlace.clear();
            for(size_t i = 0; i < secondPlace.size(); i++) {
                thirdPlace.push_back(secondPlace[i]);
            }
            
            secondPlace.clear();
            secondPlace.push_back(curNode);
        }
        else if((!thirdPlace.empty()) && thirdPlace[0]->data.calculateBA() < curNode->data.calculateBA()) {
            thirdPlace.clear();
            thirdPlace.push_back(curNode);
        }
        else if(firstPlace.empty()) {
            firstPlace.push_back(curNode);
        }
        else if(secondPlace.empty()) {
            secondPlace.push_back(curNode);
        }
        else if(thirdPlace.empty()) {
            thirdPlace.push_back(curNode);
        }
        
        curNode = curNode->next;
    }
    
    std::cout << "BATTING AVERAGE" << std::endl;
    
    std::cout << std::fixed << std::setprecision(3) << firstPlace[0]->data.calculateBA() << "\t";
    
    if(firstPlace.size() == 1) {
        std::cout << firstPlace[0]->data.getName();
    }
    else {
        std::cout << firstPlace[0]->data.getName();
        
        for(size_t i = 1; i < firstPlace.size(); i++) {
            std::cout << ", " << firstPlace[i]->data.getName();
        }
    }
    std::cout << std::endl;
    
    if(firstPlace.size() < 3 && secondPlace.size() > 0) {
        std::cout << std::fixed << std::setprecision(3) << secondPlace[0]->data.calculateBA() << "\t";
        
        if(secondPlace.size() == 1) {
            std::cout << secondPlace[0]->data.getName();
        }
        else {
            std::cout << secondPlace[0]->data.getName();
            for(size_t i = 1; i < secondPlace.size(); i++) {
                std::cout << ", " << secondPlace[i]->data.getName();
            }
        }
        std::cout << std::endl;
    }
    
    if(firstPlace.size() + secondPlace.size() < 3 && thirdPlace.size() > 0) {
        std::cout << std::fixed << std::setprecision(3) << thirdPlace[0]->data.calculateBA() << "\t";
        if(thirdPlace.size() == 1) {
            std::cout << thirdPlace[0]->data.getName();
        }
        else {
            std::cout << thirdPlace[0]->data.getName();
            for(size_t i = 1; i < thirdPlace.size(); i++) {
                std::cout << ", " << thirdPlace[i]->data.getName();
            } 
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
}

/**
 * printLeaderOBP prints out the top leaders of On Base Percentage
 * by creating three vectors to store players for the top 3 places
 * and pushes down every place if there's a new first place leader,
 * or pushes down bottom two place if there's a new second place leader
 * then prints out each place with commas if there's a tie
 */
void Linklist::printLeaderOBP() {
    Node* curNode = head;
    
    std::vector<Node*>firstPlace;
    std::vector<Node*>secondPlace;
    std::vector<Node*>thirdPlace;
    
    while(curNode != NULL) {
        if((!firstPlace.empty()) && curNode->data.calculateOBP() == firstPlace[0]->data.calculateOBP()) {
            if(curNode != firstPlace[0]) {
                firstPlace.push_back(curNode);
            }
        }
        else if((!secondPlace.empty()) && curNode->data.calculateOBP() == secondPlace[0]->data.calculateOBP()) {
            if(curNode != secondPlace[0]) {
                secondPlace.push_back(curNode);
            }
        }
        else if((!thirdPlace.empty()) && curNode->data.calculateOBP() == thirdPlace[0]->data.calculateOBP()) {
            if(curNode != thirdPlace[0]) {
                thirdPlace.push_back(curNode);
            }
        }
        else if((!firstPlace.empty()) && firstPlace[0]->data.calculateOBP() < curNode->data.calculateOBP()) {
            thirdPlace.clear();
            for(size_t i = 0; i < secondPlace.size(); i++) {
                thirdPlace.push_back(secondPlace[i]);
            }
            
            secondPlace.clear();
            for(size_t i = 0; i < firstPlace.size(); i++) {
                secondPlace.push_back(firstPlace[i]);
            }
            
            firstPlace.clear();
            firstPlace.push_back(curNode);
        }
        else if((!secondPlace.empty()) && secondPlace[0]->data.calculateOBP() < curNode->data.calculateOBP()) {
            thirdPlace.clear();
            for(size_t i = 0; i < secondPlace.size(); i++) {
                thirdPlace.push_back(secondPlace[i]);
            }
            
            secondPlace.clear();
            secondPlace.push_back(curNode);
        }
        else if((!thirdPlace.empty()) && thirdPlace[0]->data.calculateOBP() < curNode->data.calculateOBP()) {
            thirdPlace.clear();
            thirdPlace.push_back(curNode);
        }
        else if(firstPlace.empty()) {
            firstPlace.push_back(curNode);
        }
        else if(secondPlace.empty()) {
            secondPlace.push_back(curNode);
        }
        else if(thirdPlace.empty()) {
            thirdPlace.push_back(curNode);
        }
        
        curNode = curNode->next;
    }
    
    std::cout << "ON-BASE PERCENTAGE" << std::endl;
    
    std::cout << std::fixed << std::setprecision(3) << firstPlace[0]->data.calculateOBP() << "\t";
    
    if(firstPlace.size() == 1) {
        std::cout << firstPlace[0]->data.getName();
    }
    else {
        std::cout << firstPlace[0]->data.getName();
        
        for(size_t i = 1; i < firstPlace.size(); i++) {
            std::cout << ", " << firstPlace[i]->data.getName();
        }
    }
    std::cout << std::endl;
    
    if(firstPlace.size() < 3 && secondPlace.size() > 0) {
        std::cout << std::fixed << std::setprecision(3) << secondPlace[0]->data.calculateOBP() << "\t";
        
        if(secondPlace.size() == 1) {
            std::cout << secondPlace[0]->data.getName();
        }
        else {
            std::cout << secondPlace[0]->data.getName();
            for(size_t i = 1; i < secondPlace.size(); i++) {
                std::cout << ", " << secondPlace[i]->data.getName();
            }
        }
        std::cout << std::endl;
    }
    
    if(firstPlace.size() + secondPlace.size() < 3 && thirdPlace.size() > 0) {
        std::cout << std::fixed << std::setprecision(3) << thirdPlace[0]->data.calculateOBP() << "\t";
        if(thirdPlace.size() == 1) {
            std::cout << thirdPlace[0]->data.getName();
        }
        else {
            std::cout << thirdPlace[0]->data.getName();
            for(size_t i = 1; i < thirdPlace.size(); i++) {
                std::cout << ", " << thirdPlace[i]->data.getName();
            } 
        }
        std::cout << std::endl; 
    }
    
    std::cout << std::endl;
}

/**
 * printLeaderHit prints out the top leaders of Hits
 * by creating three vectors to store players for the top 3 places
 * and pushes down every place if there's a new first place leader,
 * or pushes down bottom two place if there's a new second place leader
 * then prints out each place with commas if there's a tie
 */
void Linklist::printLeaderHit() {
    Node* curNode = head;
    
    std::vector<Node*>firstPlace;
    std::vector<Node*>secondPlace;
    std::vector<Node*>thirdPlace;
    
    while(curNode != NULL) {
        if((!firstPlace.empty()) && curNode->data.getHit() == firstPlace[0]->data.getHit()) {
            if(curNode != firstPlace[0]) {
                firstPlace.push_back(curNode);
            }
        }
        else if((!secondPlace.empty()) && curNode->data.getHit() == secondPlace[0]->data.getHit()) {
            if(curNode != secondPlace[0]) {
                secondPlace.push_back(curNode);
            }
        }
        else if((!thirdPlace.empty()) && curNode->data.getHit() == thirdPlace[0]->data.getHit()) {
            if(curNode != thirdPlace[0]) {
                thirdPlace.push_back(curNode);
            }
        }
        else if((!firstPlace.empty()) && firstPlace[0]->data.getHit() < curNode->data.getHit()) {
            thirdPlace.clear();
            for(size_t i = 0; i < secondPlace.size(); i++) {
                thirdPlace.push_back(secondPlace[i]);
            }
            
            secondPlace.clear();
            for(size_t i = 0; i < firstPlace.size(); i++) {
                secondPlace.push_back(firstPlace[i]);
            }
            
            firstPlace.clear();
            firstPlace.push_back(curNode);
        }
        else if((!secondPlace.empty()) && secondPlace[0]->data.getHit() < curNode->data.getHit()) {
            thirdPlace.clear();
            for(size_t i = 0; i < secondPlace.size(); i++) {
                thirdPlace.push_back(secondPlace[i]);
            }
            
            secondPlace.clear();
            secondPlace.push_back(curNode);
        }
        else if((!thirdPlace.empty()) && thirdPlace[0]->data.getHit() < curNode->data.getHit()) {
            thirdPlace.clear();
            thirdPlace.push_back(curNode);
        }
        else if(firstPlace.empty()) {
            firstPlace.push_back(curNode);
        }
        else if(secondPlace.empty()) {
            secondPlace.push_back(curNode);
        }
        else if(thirdPlace.empty()) {
            thirdPlace.push_back(curNode);
        }
        
        curNode = curNode->next;
    }
    
    std::cout << "HITS" << std::endl;
    
    std::cout << firstPlace[0]->data.getHit() << "\t";
    
    if(firstPlace.size() == 1) {
        std::cout << firstPlace[0]->data.getName();
    }
    else {
        std::cout << firstPlace[0]->data.getName();
        
        for(size_t i = 1; i < firstPlace.size(); i++) {
            std::cout << ", " << firstPlace[i]->data.getName();
        }
    }
    std::cout << std::endl;
    
    if(firstPlace.size() < 3 && secondPlace.size() > 0) {
        std::cout << secondPlace[0]->data.getHit() << "\t";
        if(secondPlace.size() == 1) {
            std::cout << secondPlace[0]->data.getName();
        }
        else {
            std::cout << secondPlace[0]->data.getName();
            for(size_t i = 1; i < secondPlace.size(); i++) {
                std::cout << ", " << secondPlace[i]->data.getName();
            }
        }
        std::cout << std::endl;
    }
    
    if(firstPlace.size() + secondPlace.size() < 3 && thirdPlace.size() > 0) {
        std::cout << thirdPlace[0]->data.getHit() << "\t";
        if(thirdPlace.size() == 1) {
            std::cout << thirdPlace[0]->data.getName();
        }
        else {
            std::cout << thirdPlace[0]->data.getName();
            for(size_t i = 1; i < thirdPlace.size(); i++) {
                std::cout << ", " << thirdPlace[i]->data.getName();
            } 
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
}

/**
 * printLeaderWalk prints out the top leaders of Walk 
 * by creating three vectors to store players for the top 3 places
 * and pushes down every place if there's a new first place leader,
 * or pushes down bottom two place if there's a new second place leader
 * then prints out each place with commas if there's a tie
 */
void Linklist::printLeaderWalk() {
    Node* curNode = head;
    
    std::vector<Node*>firstPlace;
    std::vector<Node*>secondPlace;
    std::vector<Node*>thirdPlace;
    
    while(curNode != NULL) {
        if((!firstPlace.empty()) && curNode->data.getWalk() == firstPlace[0]->data.getWalk()) {
            if(curNode != firstPlace[0]) {
                firstPlace.push_back(curNode);
            }
        }
        else if((!secondPlace.empty()) && curNode->data.getWalk() == secondPlace[0]->data.getWalk()) {
            if(curNode != secondPlace[0]) {
                secondPlace.push_back(curNode);
            }
        }
        else if((!thirdPlace.empty()) && curNode->data.getWalk() == thirdPlace[0]->data.getWalk()) {
            if(curNode != thirdPlace[0]) {
                thirdPlace.push_back(curNode);
            }
        }
        else if((!firstPlace.empty()) && firstPlace[0]->data.getWalk() < curNode->data.getWalk()) {
            thirdPlace.clear();
            for(size_t i = 0; i < secondPlace.size(); i++) {
                thirdPlace.push_back(secondPlace[i]);
            }
            
            secondPlace.clear();
            for(size_t i = 0; i < firstPlace.size(); i++) {
                secondPlace.push_back(firstPlace[i]);
            }
            
            firstPlace.clear();
            firstPlace.push_back(curNode);
        }
        else if((!secondPlace.empty()) && secondPlace[0]->data.getWalk() < curNode->data.getWalk()) {
            thirdPlace.clear();
            for(size_t i = 0; i < secondPlace.size(); i++) {
                thirdPlace.push_back(secondPlace[i]);
            }
            
            secondPlace.clear();
            secondPlace.push_back(curNode);
        }
        else if((!thirdPlace.empty()) && thirdPlace[0]->data.getWalk() < curNode->data.getWalk()) {
            thirdPlace.clear();
            thirdPlace.push_back(curNode);
        }
        else if(firstPlace.empty()) {
            firstPlace.push_back(curNode);
        }
        else if(secondPlace.empty()) {
            secondPlace.push_back(curNode);
        }
        else if(thirdPlace.empty()) {
            thirdPlace.push_back(curNode);
        }
        
        curNode = curNode->next;
    }
    
    std::cout << "WALKS" << std::endl;
    
    std::cout << firstPlace[0]->data.getWalk() << "\t";
    
    if(firstPlace.size() == 1) {
        std::cout << firstPlace[0]->data.getName();
    }
    else {
        std::cout << firstPlace[0]->data.getName();
        
        for(size_t i = 1; i < firstPlace.size(); i++) {
            std::cout << ", " << firstPlace[i]->data.getName();
        }
    }
    std::cout << std::endl;
    
    if(firstPlace.size() < 3 && secondPlace.size() > 0) {
        std::cout << secondPlace[0]->data.getWalk() << "\t";
        
        if(secondPlace.size() == 1) {
            std::cout << secondPlace[0]->data.getName();
        }
        else {
            std::cout << secondPlace[0]->data.getName();
            for(size_t i = 1; i < secondPlace.size(); i++) {
                std::cout << ", " << secondPlace[i]->data.getName();
            }
        }
        std::cout << std::endl;
    }
    
    if(firstPlace.size() + secondPlace.size() < 3 && thirdPlace.size() > 0) {
        std::cout << thirdPlace[0]->data.getWalk() << "\t";
        
        if(thirdPlace.size() == 1) {
            std::cout << thirdPlace[0]->data.getName();
        }
        else {
            std::cout << thirdPlace[0]->data.getName();
            for(size_t i = 1; i < thirdPlace.size(); i++) {
                std::cout << ", " << thirdPlace[i]->data.getName();
            } 
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
}

/**
 * printLeaderSO prints out the top leaders of Strikeout 
 * by creating three vectors to store players for the top 3 places
 * and pushes down every place if there's a new first place leader,
 * or pushes down bottom two place if there's a new second place leader
 * then prints out each place with commas if there's a tie
 */
void Linklist::printLeaderSO() {
    Node* curNode = head;
    
    std::vector<Node*>firstPlace;
    std::vector<Node*>secondPlace;
    std::vector<Node*>thirdPlace;
    
    while(curNode != NULL) {
        if((!firstPlace.empty()) && curNode->data.getStrOut() == firstPlace[0]->data.getStrOut()) {
            if(curNode != firstPlace[0]) {
                firstPlace.push_back(curNode);
            }
        }
        else if((!secondPlace.empty()) && curNode->data.getStrOut() == secondPlace[0]->data.getStrOut()) {
            if(curNode != secondPlace[0]) {
                secondPlace.push_back(curNode);
            }
        }
        else if((!thirdPlace.empty()) && curNode->data.getStrOut() == thirdPlace[0]->data.getStrOut()) {
            if(curNode != thirdPlace[0]) {
                thirdPlace.push_back(curNode);
            }
        }
        else if((!firstPlace.empty()) && firstPlace[0]->data.getStrOut() > curNode->data.getStrOut()) {
            thirdPlace.clear();
            for(size_t i = 0; i < secondPlace.size(); i++) {
                thirdPlace.push_back(secondPlace[i]);
            }
            
            secondPlace.clear();
            for(size_t i = 0; i < firstPlace.size(); i++) {
                secondPlace.push_back(firstPlace[i]);
            }
            
            firstPlace.clear();
            firstPlace.push_back(curNode);
        }
        else if((!secondPlace.empty()) && secondPlace[0]->data.getStrOut() > curNode->data.getStrOut()) {
            thirdPlace.clear();
            for(size_t i = 0; i < secondPlace.size(); i++) {
                thirdPlace.push_back(secondPlace[i]);
            }
            
            secondPlace.clear();
            secondPlace.push_back(curNode);
        }
        else if((!thirdPlace.empty()) && thirdPlace[0]->data.getStrOut() > curNode->data.getStrOut()) {
            thirdPlace.clear();
            thirdPlace.push_back(curNode);
        }
        else if(firstPlace.empty()) {
            firstPlace.push_back(curNode);
        }
        else if(secondPlace.empty()) {
            secondPlace.push_back(curNode);
        }
        else if(thirdPlace.empty()) {
            thirdPlace.push_back(curNode);
        }
        
        curNode = curNode->next;
    }
    
    std::cout << "STRIKEOUTS" << std::endl;
    
    std::cout << firstPlace[0]->data.getStrOut() << "\t";
    
    if(firstPlace.size() == 1) {
        std::cout << firstPlace[0]->data.getName();
    }
    else {
        std::cout << firstPlace[0]->data.getName();
        
        for(size_t i = 1; i < firstPlace.size(); i++) {
            std::cout << ", " << firstPlace[i]->data.getName();
        }
    }
    std::cout << std::endl;
    
    if(firstPlace.size() < 3 && secondPlace.size() > 0) {
        std::cout << secondPlace[0]->data.getStrOut() << "\t";
        
       if(secondPlace.size() == 1) {
            std::cout << secondPlace[0]->data.getName();
        }
        else {
            std::cout << secondPlace[0]->data.getName();
            for(size_t i = 1; i < secondPlace.size(); i++) {
                std::cout << ", " << secondPlace[i]->data.getName();
            }
        }
        std::cout << std::endl;
    }
    
    if(firstPlace.size() + secondPlace.size() < 3 && thirdPlace.size() > 0) {
        std::cout << thirdPlace[0]->data.getStrOut() << "\t";
        
        if(thirdPlace.size() == 1) {
            std::cout << thirdPlace[0]->data.getName();
        }
        else {
            std::cout << thirdPlace[0]->data.getName();
            for(size_t i = 1; i < thirdPlace.size(); i++) {
                std::cout << ", " << thirdPlace[i]->data.getName();
            } 
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
}

/**
 * printLeaderHBP prints out the top leaders of Hit By Percentage
 * by creating three vectors to store players for the top 3 places
 * and pushes down every place if there's a new first place leader,
 * or pushes down bottom two place if there's a new second place leader
 * then prints out each place with commas if there's a tie
 */
void Linklist::printLeaderHBP() {
    Node* curNode = head;
    
    std::vector<Node*>firstPlace;
    std::vector<Node*>secondPlace;
    std::vector<Node*>thirdPlace;
    
    while(curNode != NULL) {
        if((!firstPlace.empty()) && curNode->data.getHBP() == firstPlace[0]->data.getHBP()) {
            if(curNode != firstPlace[0]) {
                firstPlace.push_back(curNode);
            }
        }
        else if((!secondPlace.empty()) && curNode->data.getHBP() == secondPlace[0]->data.getHBP()) {
            if(curNode != secondPlace[0]) {
                secondPlace.push_back(curNode);
            }
        }
        else if((!thirdPlace.empty()) && curNode->data.getHBP() == thirdPlace[0]->data.getHBP()) {
            if(curNode != thirdPlace[0]) {
                thirdPlace.push_back(curNode);
            }
        }
        else if((!firstPlace.empty()) && firstPlace[0]->data.getHBP() < curNode->data.getHBP()) {
            thirdPlace.clear();
            for(size_t i = 0; i < secondPlace.size(); i++) {
                thirdPlace.push_back(secondPlace[i]);
            }
            
            secondPlace.clear();
            for(size_t i = 0; i < firstPlace.size(); i++) {
                secondPlace.push_back(firstPlace[i]);
            }
            
            firstPlace.clear();
            firstPlace.push_back(curNode);
        }
        else if((!secondPlace.empty()) && secondPlace[0]->data.getHBP() < curNode->data.getHBP()) {
            thirdPlace.clear();
            for(size_t i = 0; i < secondPlace.size(); i++) {
                thirdPlace.push_back(secondPlace[i]);
            }
            
            secondPlace.clear();
            secondPlace.push_back(curNode);
        }
        else if((!thirdPlace.empty()) && thirdPlace[0]->data.getHBP() < curNode->data.getHBP()) {
            thirdPlace.clear();
            thirdPlace.push_back(curNode);
        }
        else if(firstPlace.empty()) {
            firstPlace.push_back(curNode);
        }
        else if(secondPlace.empty()) {
            secondPlace.push_back(curNode);
        }
        else if(thirdPlace.empty()) {
            thirdPlace.push_back(curNode);
        }
        
        curNode = curNode->next;
    }
    
    std::cout << "HIT BY PITCH" << std::endl;
    
    std::cout << firstPlace[0]->data.getHBP() << "\t";
    
    if(firstPlace.size() == 1) {
        std::cout << firstPlace[0]->data.getName();
    }
    else {
        std::cout << firstPlace[0]->data.getName();
        
        for(size_t i = 1; i < firstPlace.size(); i++) {
            std::cout << ", " << firstPlace[i]->data.getName();
        }
    }
    std::cout << std::endl;
    
    if(firstPlace.size() < 3 && secondPlace.size() > 0) {
        std::cout << secondPlace[0]->data.getHBP() << "\t";
        
        if(secondPlace.size() == 1) {
            std::cout << secondPlace[0]->data.getName();
        }
        else {
            std::cout << secondPlace[0]->data.getName();
            for(size_t i = 1; i < secondPlace.size(); i++) {
                std::cout << ", " << secondPlace[i]->data.getName();
            }
        }
        std::cout << std::endl;
    }
    
    if(firstPlace.size() + secondPlace.size() < 3 && thirdPlace.size() > 0) {
        std::cout << thirdPlace[0]->data.getHBP() << "\t";
        
        if(thirdPlace.size() == 1) {
            std::cout << thirdPlace[0]->data.getHBP() << "\t";
            
        }
        else {
            std::cout << thirdPlace[0]->data.getName();
            for(size_t i = 1; i < thirdPlace.size(); i++) {
                std::cout << ", " << thirdPlace[i]->data.getName();
            } 
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
}

