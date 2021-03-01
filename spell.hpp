#include <iostream>
using namespace std;

class Spell { 
    protected:
    string name;
    int price;
    int level_req;
    int min_damage;
    int max_damage;
    int magicPower;
    int number_of_rounds;


    public:
    Spell(string name_, int price_, int level_req_, int min_damage_,
          int max_damage_, int mana_, int number_of_rounds_);
    string get_name() { return name; };
    int get_price () { return price; };
    int get_level_req () { return level_req; };
    int get_min_damage() { return min_damage; };
    int get_max_damage() { return max_damage; };
    int get_magic_Power() { return magicPower; };
    int get_number_of_rounds() { return number_of_rounds; };
    virtual void print() = 0;
};


class IceSpell : public Spell {
    protected:
    int damage_reduction;
    public:
    IceSpell(string name_, int price_, int level_req_, int min_damage_,
          int max_damage_, int magicPower_, int number_of_rounds_, int damage_reduction_);
    int get_damage_reduction() { return damage_reduction; };
    void print();
    
};

class FireSpell : public Spell {
    protected:
    int armor_reduction;
    public:
    FireSpell(string name_, int price_, int level_req_, int min_damage_,
          int max_damage_, int magicPower_, int number_of_rounds_, int armor_reduction_);
    int get_armor_rediction() { return armor_reduction; };
    void print();
};

class LightningSpell : public Spell {
    protected:
    int dodge_reduction;
    public:
    LightningSpell(string name_, int price_, int level_req_, int min_damage_,
          int max_damage_, int magicPower_, int number_of_rounds_, int dodge_reduction_);
    int get_dodge_reduction() { return dodge_reduction; };
    void print();
};