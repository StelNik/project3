#include "spell.hpp"


Spell::Spell (string name_, int price_, int level_req_, int min_damage_,
              int max_damage_, int magicPower_, int number_of_rounds_) :
    name(name_),
    price(price_),
    level_req(level_req_),
    min_damage(min_damage_),
    max_damage(max_damage_),
    magicPower(magicPower_),
    number_of_rounds(number_of_rounds_)  {}



IceSpell::IceSpell(string name_, int price_, int level_req_, int min_damage_,int max_damage_,
                   int magicPower_, int number_of_rounds_, int damage_reduction_) :
        Spell(name_, price_, level_req_, min_damage_,
              max_damage_, magicPower_,number_of_rounds_), damage_reduction(damage_reduction_) {}

void IceSpell::print() { 
    cout << "\nPrinting\nIceSpell: " << name 
         << "\nPrice: " << price 
         << "\nLevel requirement: " << level_req 
         << "\nDamage range: " << min_damage << " - " << max_damage
         << "\nMagicPower: " << magicPower 
         << "\nRounds:" << number_of_rounds
         << "\nDamage Reduction: " << damage_reduction << endl;

}




FireSpell::FireSpell(string name_, int price_, int level_req_, int min_damage_,int max_damage_,
                     int magicPower_, int number_of_rounds_, int armor_reduction_) :
        Spell(name_, price_, level_req_, min_damage_,
              max_damage_, magicPower_,number_of_rounds_), armor_reduction(armor_reduction_) {}             


void FireSpell::print() { 
    cout << "\nPrinting\nFireSpell: " << name 
         << "\nPrice: " << price 
         << "\nLevel requirement: " << level_req 
         << "\nDamage range: " << min_damage << " - " << max_damage
         << "\nMagicPower: " << magicPower
         << "\nRounds:" << number_of_rounds
         << "\nArmor Reduction: " << armor_reduction << endl; }


LightningSpell::LightningSpell(string name_, int price_, int level_req_, int min_damage_,
                    int max_damage_, int magicPower_, int number_of_rounds_, int dodge_reduction_) :
        Spell(name_, price_, level_req_, min_damage_,
              max_damage_, magicPower_,number_of_rounds_), dodge_reduction(dodge_reduction_) {}



void LightningSpell::print() { 
    cout << "\nPrinting\nLightningSpell: " << name 
         << "\nPrice: " << price 
         << "\nLevel requirement: " << level_req 
         << "\nDamage range: " << min_damage << " - " << max_damage
         << "\nMagicPower: " << magicPower
         << "\nRounds:" << number_of_rounds
         << "\nDodge Reduction: " << dodge_reduction << endl;
 }