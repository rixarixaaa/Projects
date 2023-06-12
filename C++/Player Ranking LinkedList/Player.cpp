/**
 * Parisa Nawar
 * pxn210032
 */
 #include "Player.h"
 
 #include <cstring>
 #include <iostream>
 #include <sstream>
 #include <iomanip>

    std::string name;
    int hit;
    int out;
    int strOut;
    int walk;
    int hbp;
    int sac;
        
    Player::Player() {
        name = "";
        hit = 0;
        out = 0;
        strOut = 0;
        walk = 0;
        hbp = 0;
        sac = 0;
    }
    
    /**
     * Overloaded Player Constructor takes the name string and parsed
     * record line to evaluate each character by their pertaining stat and
     * storing that stat into the private variables
     */
    Player::Player(std::string n, const std::string& line) {
        
        name = n;
        hit = 0;
        out = 0;
        strOut = 0;
        walk = 0;
        hbp = 0;
        sac = 0;
    
        for(size_t i = 0; i < line.length(); i++) {
            if(line.at(i) == 'H')
            {
                hit++;
            }
            else if(line.at(i) == 'O') {
                out++;
            }
            else if(line.at(i) == 'K') {
                strOut++;
            }
            else if(line.at(i) == 'W') {
                walk++;
            }
            else if(line.at(i) == 'P') {
                hbp++;
            }
            else if(line.at(i) == 'S') {
                sac++;
            }
            
        }
        
        
    }
    
    /**
     * Player function calculateBA calculates
     * the batting average using the batting average equation
     */
    double Player::calculateBA() {
        if(hit == 0 || calculateAtBat() == 0) {
            return 0;
        }
        else {
            return ((hit * 1.0) / (static_cast<double>(calculateAtBat())));
        }
    }
    
    /**
     * Player function calculateOBP calculates
     * the on base percentage using the batting average equation
     */
    double Player::calculateOBP() {
        int top = hit + walk + hbp;
        int bot = calculatePlateApp();
        
        if(top == 0 || bot == 0) {
            return 0;
        }
        else {
            return (((1.0) * (hit + walk + hbp)) / (static_cast<double>(calculatePlateApp())));
        }
    }
    
    /**
     * Player function calculateAtBat calculates the 
     * at bat by using the at bat equation
     */
    int Player::calculateAtBat() {
        return (hit + out + strOut);
    }
    
    /**
     * Player function calculatePlateApp calculates the 
     * plate appearance using the plate appearance
     * equation
     */
    int Player::calculatePlateApp() {
        return (hit + out + strOut + walk + hbp + sac);
    }
    
    /**
     * Player overloaded add operator
     * adds two player objects together and 
     * returns the total of every single stat into
     * a player object
     */
    Player Player::operator+(const Player& play) {
        Player playerTotal;
        
        playerTotal.name = name;
        playerTotal.hit = hit + play.hit;
        playerTotal.out = out + play.out;
        playerTotal.strOut = strOut + play.strOut;
        playerTotal.walk = walk + play.walk;
        playerTotal.hbp = hbp + play.hbp;
        playerTotal.sac = sac + play.sac;
        
        return playerTotal;
    }
    
    /**
     * Player overloaded less than operator compares
     * the names of two player object and 
     * returns whether the left name is alphabetically
     * less than the right name
     */
    bool Player::operator<(const Player& play) {
        return name < play.name;
    }
    
    /**
     * Player overloaded equal evaluator operator
     * compares the names of two player object and
     * returns whether the left name is alphabetically
     * equal to the right name 
     */
    bool Player::operator==(const Player& play) {
        return name == play.name;
    }

    /**
     * Player function toString strings all variables of a player object
     * and returns a string with all the information, including the doubles that 
     * are rounded to 3 decimal places
     */
    std::string Player::toString() {
        
        std::string pr = "";
        std::stringstream baa;
        std::stringstream obpp;
        
        baa << std::fixed << std::setprecision(3) << calculateBA();
        obpp<< std::fixed << std::setprecision(3) << calculateOBP();
        
        pr = pr + name + "\t" + std::to_string(calculateAtBat()) + "\t" + std::to_string(hit) + "\t" + std::to_string(walk) + "\t" + std::to_string(strOut) + "\t" + std::to_string(hbp) + "\t" + std::to_string(sac) + "\t" +  baa.str() + "\t" + obpp.str() + "\n";
        
        return pr;
    } 
    
    
    
    
    
    
    