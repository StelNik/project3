#include "living.hpp"
// #include "item.hpp"
#include <vector>
#include <iostream>
using namespace std;



class gridTile {

    protected:
    int x, y;
    public:
    gridTile(int x_, int y_) : x(x_), y(y_) {}
    virtual void print() = 0;
    virtual void print_graphic() = 0;

    bool add_item(Item* i);

    bool buy();
    bool sell();

    virtual void set_party(vector<Hero*> p) = 0;
    virtual void remove_party() = 0;
    virtual bool can_move() = 0;
};

class Common : public gridTile {
    private:
    vector<Hero*> heroes;
    vector<Monster*> monsters;
    public:
    Common(int x_, int y_) : gridTile(x_, y_) {  }
    

    void set_party(vector<Hero*> p) { heroes = p;};
    void remove_party() { heroes.clear(); };
    
    // void set_heroes(Hero* h1) {
    //     heroes.push_back(h1); 
    // };
    // void set_heroes(Hero* h1, Hero* h2) {
    //     heroes.push_back(h1); 
    //     heroes.push_back(h2); 
    // };
    // void set_heroes(Hero* h1, Hero* h2, Hero* h3) {
    //     heroes.push_back(h1); 
    //     heroes.push_back(h2);
    //     heroes.push_back(h3);
    // };
    void set_monsters(vector<Monster*> m) { monsters = m; };
    // void set_monsters(Monster* m1) {
    //     monsters.push_back(m1); 
    // };
    // void set_monsters(Monster* m1, Monster* m2) {
    //     monsters.push_back(m1); 
    //     monsters.push_back(m2); 
    // };
    // void set_monsters(Monster* m1, Monster* m2, Monster* m3) {
    //     monsters.push_back(m1); 
    //     monsters.push_back(m2);
    //     monsters.push_back(m3);
    // };

    void print();
    void print_graphic();
    bool can_move() { return true; };
};

class Market : public gridTile {
    private:
    vector<Item*> items;
    vector<Hero*> heroes;
    public:
    Market(int x_, int y_) : gridTile(x_, y_) { }
    
    void set_party(vector<Hero*> p) { heroes = p;};
    void remove_party() { heroes.clear(); };

    // void set_heroes(Hero* h1) {
    //     heroes.push_back(h1); 
    // };
    // void set_heroes(Hero* h1, Hero* h2) {
    //     heroes.push_back(h1); 
    //     heroes.push_back(h2); 
    // };
    // void set_heroes(Hero* h1, Hero* h2, Hero* h3) {
    //     heroes.push_back(h1); 
    //     heroes.push_back(h2);
    //     heroes.push_back(h3);
    // };
    void add_item(vector<Item*> i) { items = i; };
    void add_item(Item* i) { items.push_back(i); };
    bool buy();
    bool sell();

    void print();
    void print_graphic();

    bool can_move() { return true; };
};

class nonAccessible : public gridTile {
    
    public:
    nonAccessible(int x_, int y_) : gridTile(x_, y_) {}
    void print();
    void print_graphic();

    bool can_move() { return false; };
    void set_party(vector<Hero*> p) {};
    void remove_party() {};
};


class Grid {
    private:
    const int size_x;
    const int size_y;
    gridTile* grid[5][5];
    vector<Hero*> party;
    

    public:
    Grid() : size_x(5), size_y(5) {
        for(int i = 0 ; i < size_x  ; i++) {
            for(int j = 0 ; j < size_y ; j++) {
                if(i == 0  || j == 0 ) {
                    grid[i][j] = new nonAccessible(i,j);
                } else {
                    grid[i][j] = new Common(i,j);
                }
                
            }
        }
        make_nonAccessible(0,2);
        make_Market(2,2);
        make_nonAccessible(2,4);
        make_nonAccessible(3,1);
    }

    void make_nonAccessible(int i, int j) {
        delete grid[i][j];
        grid[i][j] = new nonAccessible(i,j);
    }
    void make_Market(int i, int j) {
        delete grid[i][j];
        grid[i][j] = new Market(i,j);
    }

    void print() {
        for(int i = 0 ; i < size_x ; i++) 
            for(int j = 0 ; j < size_y ; j++) 
                grid[i][j]->print();
                   
    }
    void print_graphic() {
        for(int i = 0 ; i < size_x ; i++) {
            for(int j = 0 ; j < size_y ; j++) {
                if(j == 0) cout << "\n";
                grid[i][j]->print_graphic();
            }
        }
        cout << endl;
    }
    void start(vector<Hero*> p);

    void move_party_to_coordinates(int x, int y);
    void move();

};