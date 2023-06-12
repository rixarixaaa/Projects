/**
 * Parisa Nawar
 * pxn210032
 */
 #ifndef PLAYER_H
 #define PLAYER_H
 
 #include <string>
 
 class Player {
    private:
        std::string name;
        int hit;
        int out;
        int strOut;
        int walk;
        int hbp;
        int sac;
        
    public:
        Player();
        Player(std::string, const std::string&);
        
        std::string getName() {return name;}
        int getHit() {return hit;}
        int getOut() {return out;} 
        int getStrOut() {return strOut;}
        int getWalk() {return walk;}
        int getHBP() {return hbp;}
        int getSac() {return sac;}
        
        double calculateBA();
        double calculateOBP();
        
        int calculateAtBat();
        int calculatePlateApp();
        
        Player operator+(const Player& play);
        
        bool operator<(const Player& play);
        bool operator==(const Player& play);
        
        std::string toString();
        
        
    
 };
 
 #endif //PLAYER_H
 