#include "living.hpp"
// #include "item.hpp"
#include <vector>
#include <iostream>
using namespace std;



class gridTile {

    private:
    Hero* h;
    Monster* m;
    vector<Item*> items;
    bool accesible;
    bool common;
    bool market;


    public:
    gridTile() {
        accesible = true; common = true; market = true;
    }
    gridTile(bool accessible_, bool common_, bool market_) : 
            accesible(accessible_), common(common_), market(market_) 
            { h = NULL; m = NULL; }

    Hero* get_hero() { return h; };
    Monster* get_monster() { return m; };
    void print();


    bool is_market() { return market; };
    bool is_common() { return common; };
    bool is_accesible() { return accesible; };
    
    bool set_hero(Hero* h_);
    bool set_monster(Monster* m_);
    bool add_item(Item* i);

    bool buy();
    bool sell();
};



class Grid {
    private:
    const int size_x;
    const int size_y;
    gridTile* grid[2][2];
    

    public:
    Grid() : size_x(2), size_y(2) {
        for(int i = 0 ; i < 2  ; i++) {
            for(int j = 0 ; j < 2 ; j++) {
                grid[i][j] = new gridTile;
            }
        }
    }
    void print() {
        for(int i = 0 ; i < size_x ; i++) 
            for(int j = 0 ; j < size_y ; j++) 
                grid[i][j]->print();
                   
    }


};