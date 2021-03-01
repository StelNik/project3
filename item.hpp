#include <iostream>
using namespace std;

class Item {
    protected:
    string name;
    int price;
    int level_req;



    public:
    Item (string name_, int price_, int level_req_);
    string get_name() { return name; };
    int get_price () { return price; };
    int get_level_req () { return level_req; };
    virtual void print() = 0;
    virtual bool is_armor() { };
    virtual bool is_weapon() { };

    virtual bool is_agility() { };
    virtual bool is_dexterity() { };
    virtual bool is_strength() { };
};


class Weapon : public Item {

    protected:
    int damage;
    bool one_handed;

    public:
    Weapon(string name_, int price_, int level_req_, int damage_, bool one_handed_);
    void print();
    int get_damage() { return damage; };
    bool is_armor() { return false ;};
    bool is_weapon() { return true ;};
};

class Armor : public Item {
    protected:
    int resistance;

    public:
    Armor(string name_, int price_, int level_req_, int resistance_);
    void print();
    int get_resistance() { return resistance; };
    bool is_armor() { return true ;};
    bool is_weapon() { return false ;};
};


class Potion : public Item {
    protected:
    int buff;

    public:
    Potion(string name_, int price_, int level_req_, int buff_);
    void print();
    int get_buff() { return buff;};
};

class strPotion : public Potion {

    public:
    strPotion(string name_, int price_, int level_req_, int buff_);
    // int get_str_buff() { Potion::get_buff(); }
};

class dexPotion : public Potion {

    public:
    dexPotion(string name_, int price_, int level_req_, int buff_);
    // int get_dex_buff() { Potion::get_buff(); }
};

class agiPotion : public Potion {

    public:
    agiPotion(string name_, int price_, int level_req_, int buff_);
    // int get_agi_buff() { Potion::get_buff(); }
};