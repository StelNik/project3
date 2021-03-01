#include "item.hpp"


Item::Item (string name_, int price_, int level_req_) :
     name(name_),
     price(price_),
     level_req(level_req_) {}








Weapon::Weapon(string name_, int price_, int level_req_, int damage_, bool one_handed_) : 
    Item(name_, price_, level_req_), damage(damage_), one_handed(one_handed_) {}

void Weapon::print() {
    cout << "\nPrinting\nWeapon: " << name 
         << "\nPrice: " << price 
         << "\nLevel requirement: " << level_req 
         << "\nDamage: " << damage
         << "\nOne_handed: " << one_handed << endl; 
} 


Armor::Armor(string name_, int price_, int level_req_, int resistance_) :
    Item(name_, price_, level_req_), resistance(resistance_) {}

void Armor::print() {
    cout << "\nPrinting\nArmor: " << name 
         << "\nPrice: " << price 
         << "\nLevel requirement: " << level_req 
         << "\nResistance: " << resistance << endl; 
}



Potion::Potion(string name_, int price_, int level_req_, int buff_) :
    Item(name_, price_, level_req_), buff(buff_) {}

void Potion::print() {
    cout << "\nPrinting\nPotion: " << name 
         << "\nPrice: " << price 
         << "\nLevel requirement: " << level_req 
         << "\nBuff: " << buff << endl; 
}


strPotion::strPotion(string name_, int price_, int level_req_, int buff_) :
            Potion(name_, price_, level_req_, buff_) {}

agiPotion::agiPotion(string name_, int price_, int level_req_, int buff_) :
            Potion(name_, price_, level_req_, buff_) {}

dexPotion::dexPotion(string name_, int price_, int level_req_, int buff_) :
            Potion(name_, price_, level_req_, buff_) {}