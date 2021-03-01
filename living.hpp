#include <iostream>
using namespace std;
#include "item.hpp"
#include "spell.hpp"
#include <vector>




class Living {
    protected:
    string name;
    int level;
    int healthPower;

    public:
    Living(string name_, int healthPower_);
    string get_name() { return name; }
    int get_level() { return level; };
    int get_health_Power() { return healthPower; };
    virtual void print() = 0;

    virtual void death() {};
    virtual void get_attacked(int damage) {};
    bool alive() {
        if(healthPower > 0) return true;
        return false;
    }

};

// class Weapon;
// class Armor;
struct Coordinates {
    int x,y;
};
class Hero : public Living {
    protected:

    Coordinates coordinates;
    int magicPower;
    int strength;
    int dexterity;
    int agility;
    int money;
    int experience;
    Weapon* equipped_weapon;
    Armor* equipped_armor;
    vector<Item*> inventory;
    vector<Potion*> pot_inventory;
    vector<Spell*> spell_inventory;


    public:
    Hero(string name_, int healthPower_, int magicPower_, int strength_,
         int dexterity_, int agility_, int money_);

    int get_magicPower() { return magicPower ;};
    int get_strength() { return strength;}
    int get_dexterity() { return dexterity; };
    int get_agility() { return agility; };
    int get_money() { return money; };
    int get_experience() { return experience; };

    void add_experience(int ammount);
    void set_experience(int exp) { experience = exp; };
    // Επιστρέφει true αν εγινε το equip, false αν δεν εγινε (λογω level requirement)
    bool equip();
    bool equip(Weapon* w);
    bool equip(Armor* a);
    void add_item_to_inventory(Item* i){ inventory.push_back(i); };
    void add_item_to_inventory(Potion* p){ pot_inventory.push_back(p); };
    void add_item_to_inventory(Spell* s) { spell_inventory.push_back(s); };
    // Επιστρέφει true αν εγινε το sell, false αν δεν εγινε
    // Η κλήση της ξεκινάει απο την sell κάποιου gridTile η οποία επιλέγει απλά τον ήρωα
    bool sell();

    // Καλούνται απο την Hero::sell(), αφού γίνει επιλογή ανάμεσα σε item/spell
    bool sell_item();
    bool sell_spell();

    void set_coordinates(int x_, int y_) { coordinates.x = x_; coordinates.y = y_; };
    Coordinates get_coordinates() { return coordinates; };
    bool use();
    bool use(strPotion* p);
    bool use(dexPotion* p);
    bool use(agiPotion* p);
    void checkInventory();
    void add_money(int ammount) { money += ammount; };
    void sub_money(int ammount) { money -= ammount; };
    virtual void print() = 0;
    virtual void levelUp() = 0;


    // Επιστρεφει το damage της επιθεσης
    int attack();
    void death() {};
    void win() {
        cout << "Hero wins" << endl;
        add_experience(80);
        add_money(80);
    }
    void lose() {
        add_money( - (get_money() / 2));
    }


    void get_attacked(int damage);

    

    
};

class Warrior : public Hero {

    public:
    Warrior(string name_, int healthPower_, int magicPower_, int strength_,
         int dexterity_, int agility_, int money_);
    void levelUp();
    void print();

};


class Sorcerer : public Hero {

    public:
    Sorcerer( string name_, int healthPower_, int magicPower_, int strength_,
         int dexterity_, int agility_, int money_);
    void levelUp();
    void print();
};


class Paladin : public Hero {

    public:
    Paladin( string name_, int healthPower_, int magicPower_, int strength_,
         int dexterity_, int agility_, int money_);
    void levelUp();
    void print();
};


class Monster : public Living {
    protected:
    int min_damage;
    int max_damage;
    int armor;
    int dodge;

    public:
    Monster(string name_, int healthPower_, int min_damage_,
             int max_Damage_, int armor_, int dodge_);
    virtual void print() = 0;
    int get_min_damage() { return min_damage; };
    int get_max_damage() { return max_damage; };
    int get_armor() { return armor; };
    int get_dodge() { return dodge; };
    // Επιστρεφει το damage της επιθεσης
    int attack();
    void get_attacked(int damage);
    void death() {};
};


class Dragon : public Monster {
    public:
    Dragon(string name_, int healthPower_, int min_damage_,
            int max_Damage_, int armor_, int dodge_);

    void print();
};

class Exoskeleton : public Monster {
    public:
    Exoskeleton(string name_, int healthPower_, int min_damage_,
             int max_Damage_, int armor_, int dodge_);

    void print();
};

class Spirit : public Monster {
    public:
    Spirit(string name_, int healthPower_, int min_damage_,
             int max_Damage_, int armor_, int dodge_);

    void print();

};