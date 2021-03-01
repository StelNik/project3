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

    virtual void add_item(Item* i)  { } ;
    virtual void add_item(vector<Item*> i)  { } ;
    virtual void add_item(Spell* s)  { } ;
    virtual bool buy() { };
    virtual bool sell() { };

    virtual void set_party(vector<Hero*> p) { };
    virtual vector<Hero*> get_party() { };
    virtual void remove_party() { };

    virtual bool can_move() = 0;

    virtual void set_monsters(vector<Monster*> m) {};
    virtual void set_monsters(Monster* m) { };
    virtual vector<Monster*> get_monsters() { };

    // Επιστρεφει το index του ηρωα που επιλεχτηκε
    virtual int select_hero_from_party() {};
    virtual bool is_market() = 0;
    virtual bool is_common() = 0;
    virtual void battle() { };

};

class Common : public gridTile {
    private:
    vector<Hero*> heroes;
    vector<Monster*> monsters;
    public:
    Common(int x_, int y_) : gridTile(x_, y_) {  }
    

    void set_party(vector<Hero*> p) { heroes = p;};
    vector<Hero*> get_party() { return heroes; };
    void remove_party() { heroes.clear(); };
    

    void set_monsters(Monster* m) { monsters.push_back(m); };
    void set_monsters(vector<Monster*> m) { monsters = m; };
    vector<Monster*> get_monsters() { return monsters; }; 

    int select_hero_from_party();

    void print();
    void print_graphic();
    bool can_move() { return true; };


    bool is_market() { return false; };
    bool is_common() { return true; };

    bool heroes_alive();
    bool monsters_alive();
    void battle();

};

class Market : public gridTile {
    private:
    vector<Item*> items;
    vector<Spell*> spells;
    vector<Hero*> heroes;
    public:
    Market(int x_, int y_) : gridTile(x_, y_) { }
    
    void set_party(vector<Hero*> p) { heroes = p;};
    vector<Hero*> get_party() { return heroes; };
    void remove_party() { heroes.clear(); };

    void add_item(vector<Item*> i) { items = i; };
    void add_item(Item* i) { items.push_back(i); };
    void add_item(Spell* s) { spells.push_back(s); };

    bool buy();
    bool buy_item(int hero_index);
    bool buy_spell(int hero_index);
    bool sell();

    int select_hero_from_party();


    void print();
    void print_graphic();

    bool can_move() { return true; };

    bool is_market() { return true; };
    bool is_common() { return false; };
};

class nonAccessible : public gridTile {
    
    public:
    nonAccessible(int x_, int y_) : gridTile(x_, y_) {}
    void print();
    void print_graphic();

    bool can_move() { return false; };



    bool is_market() { return false; };
    bool is_common() { return false; };

};


class Grid {
    private:
    const int size_x;
    const int size_y;
    gridTile* grid[5][5];
    vector<Hero*> party;

    bool move_party_to_coordinates(int x, int y, vector<Hero*> p);
    

    public:
    Grid();

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
    void move();
    void move_many();

    void decide_buy_sell();
    void decide_inventory_equip_use();
    void battle();



};