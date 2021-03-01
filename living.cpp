#include "living.hpp"
int spec_stat_boost = 10;
int lvlUp_stat_boost = 5;
int enemy_Stat_boost = 5;
int exp_to_level = 50;

Living::Living(string name_,  int healthPower_) :
               name(name_),  healthPower(healthPower_) { level = 1; }





Hero::Hero(string name_,  int healthPower_, int magicPower_, int strength_,
        int dexterity_, int agility_, int money_) : 
        Living(name_,  healthPower_), 
        magicPower(magicPower_),
        strength(strength_),
        dexterity(dexterity_),
        agility(agility_),
        money(money_) { coordinates.x = -1; coordinates.y = -1; experience = 0; equipped_weapon = NULL; equipped_armor = NULL;  }


void Hero::add_experience(int ammount) {
        experience += ammount; 
        if(experience > exp_to_level) {
            levelUp();
            set_experience(experience - exp_to_level);
        } 
}
bool Hero::equip() {
    cout << "\nSelect Armor/Weapon index to equip\n";
    if(inventory.size() == 0) {
        cout << "No items in the inventory" << endl;
        return false;
    }
    // ΕΠΙΛΟΓΗ ΑΝΤΙΚΕΙΜΕΝΟΥ
    int index;
    bool selected = false;
    // Ελεγχος μεχρι να γινει σωστη επιλογη αντικειμενου
    Item* i;
    while(!selected) {
        cin >> index;
        if(index >= inventory.size()) {
            cout << "Select correct index" << endl;
        } else {
            i = inventory[index];
            if(i->is_armor()) return equip( (Armor*)i );
            if(i->is_weapon()) return equip( (Weapon*)i );
            // selected = true;
        }
    }
}

// Επιστρέφει true αν εγινε το equip, false αν δεν εγινε (λογω level requirement)
bool Hero::equip(Weapon* w) {
    if( w->get_level_req() <= this->level ) {
        this->equipped_weapon = w; 
        return true;
    } else {
        cout << "\n Hero not high enough level to equip this Weapon" << endl;
        return false;
    } 
    

}

// Επιστρέφει true αν εγινε το equip, false αν δεν εγινε (λογω level requirement)
bool Hero::equip(Armor* a) {
    if( a->get_level_req() <= this->level ) {
        this->equipped_armor = a;
        return true;
    } else {
        cout << "\n Hero not high enough level to equip this Armor" << endl;
        return false;
    } 
}


bool Hero::use() {
    cout << "\nSelect Potion index to use\n";
    if(pot_inventory.size() == 0) {
        cout << "No items in the potion inventory" << endl;
        return false;
    }
    // ΕΠΙΛΟΓΗ POTION
    int index;
    bool selected = false;
    // Ελεγχος μεχρι να γινει σωστη επιλογη potion
    Item* i;
    while(!selected) {
        cin >> index;
        if(index >= pot_inventory.size()) {
            cout << "Select correct index" << endl;
        } else {
            i = pot_inventory[index];
            if(i->is_agility()) return use( (agiPotion*)i );
            if(i->is_dexterity()) return use( (dexPotion*)i );
            if(i->is_strength()) return use( (strPotion*)i );
            // selected = true;
        }
    }
}

// Επιστρέφει true αν εγινε το equip, false αν δεν εγινε (λογω level requirement)
bool Hero::use(strPotion* p) {
    if( p->get_level_req() <= this->level ) {
        this->strength += p->get_buff();
        return true;
    } else {
        cout << "\n Hero not high enough level to use this Potion" << endl;
        return false;
    }
    
}

// Επιστρέφει true αν εγινε το equip, false αν δεν εγινε (λογω level requirement)
bool Hero::use(dexPotion* p) {
    if( p->get_level_req() <= this->level ) {
        this->strength += p->get_buff();
        return true;
    } else {
        cout << "\n Hero not high enough level to use this Potion" << endl;
        return false;
    }
}

// Επιστρέφει true αν εγινε το equip, false αν δεν εγινε (λογω level requirement)
bool Hero::use(agiPotion* p) {
    if( p->get_level_req() <= this->level ) {
        this->strength += p->get_buff();
        return true;
    } else {
        cout << "\n Hero not high enough level to use this Potion" << endl;
        return false;
    }
}


void Hero::checkInventory() {
    cout << "\nCHECKING INVENTORY\n";
    cout << "\nHero: " << name << " has equipped:\n";
    if(equipped_weapon != NULL) equipped_weapon->print();
    if(equipped_armor != NULL) equipped_armor->print();

    int size = inventory.size();
    if(size == 0) {
        cout << "Armor/Weapon Inventory is empty!" << endl;
    } else {
        cout << "Armor/Weapon Inventory contains:\n";
        for(int i = 0 ; i < size ; i++) {
            inventory[i]->print();
        } 
    }
    int pot_size = pot_inventory.size();
    if(pot_size == 0) {
        cout << "Potion Inventory is empty!" << endl;
    } else {
        cout << "Potion Inventory contains:\n";
        for(int i = 0 ; i < size ; i++) {
            pot_inventory[i]->print();
        } 
    }
}


bool Hero::sell_item() {
    cout << "\nSelect item index or -1 to exit" << endl;
    for(int i = 0 ; i < inventory.size() ; i++) {
        cout << "Index :" << i;
        inventory[i]->print();
        cout << "\n";
    }
    while(true) {
        int index;
        cin >> index;
        if(index == -1 ) {
            cout << "Exiting without buying" << endl; 
            return false;
        }
        if(index < inventory.size()) {
            int price = inventory[index]->get_price() / 2;
            cout << "Hero sold item with index: " << index;
            cout << " for the price of: " << price << endl;
            this->add_money(price);

            // Με τη βοηθεια iterators, διαγράφω απο το inventory το αντικειμενο που πουλήθηκε
            vector<Item*>::iterator it = inventory.begin();
            it += index;
            inventory.erase(it);
            
            return true;
        }
        cout << "Select correct index" << endl;
    }  
}

bool Hero::sell_spell() {
    cout << "\nSelect spell index or -1 to exit" << endl;
    for(int i = 0 ; i < spell_inventory.size() ; i++) {
        cout << "Index :" << i;
        spell_inventory[i]->print();
        cout << "\n";
    }
    while(true) {
        int index;
        cin >> index;
        if(index == -1 ) {
            cout << "Exiting without buying" << endl; 
            return false;
        }
        if(index < spell_inventory.size()) {
            int price = spell_inventory[index]->get_price() / 2;
            cout << "Hero sold spell with index: " << index;
            cout << " for the price of: " << price << endl;
            this->add_money(price);

            // Με τη βοηθεια iterators, διαγράφω απο το inventory το αντικειμενο που πουλήθηκε
            vector<Spell*>::iterator it = spell_inventory.begin();
            it += index;
            spell_inventory.erase(it);
            
            return true;
        }
        cout << "Select correct index" << endl;
    }  
}
bool Hero::sell() {
    bool zero_items = false;
    bool zero_spells = false;
    if(inventory.size() == 0) {
        zero_items = true;
        cout << "No items to sell" << endl;
    }
    if(spell_inventory.size() == 0) {
        zero_spells = true;
        cout << "No spells to sell" << endl;
    }
    if(inventory.size() == 0  && spell_inventory.size() == 0) {
        return false;
    }

    cout << "\nPress 1 to sell Items, 2 to sell Potions" << endl;
    int decision;
    bool decided = false;
    while(!decided) {
        cin >> decision;
        switch(decision) {
            case 1:
                if(zero_items) {
                    cout << "There are no items to sell" << endl;
                    break;
                }
                sell_item();
                decided = true;
                break;
            case 2:
            if(zero_spells) {
                    cout << "There are no spells to sell" << endl;
                    break;
                }
                sell_spell();
                decided = true;
                break;
        }
    }
}

int Hero::attack() {
    if(equipped_weapon != NULL) {
        return equipped_weapon->get_damage() + strength;
    }
    return strength;
}

void Hero::get_attacked(int damage) {
    // prepei na kanw kai to dodge
    if(equipped_armor != NULL) {
        healthPower = healthPower - (damage - equipped_armor->get_resistance());
    } else {
        healthPower = healthPower - damage;
    }
    if(healthPower <= 0) {
        healthPower = 0;
        death();
    }
}

int Monster::attack() {
    return ( get_min_damage() + get_max_damage() ) / 2; 
}


void Monster::get_attacked(int damage) {
    // prepei na kanw kai to dodge
    healthPower = healthPower - (damage - armor);
    if(healthPower <= 0) {
        healthPower = 0;
        death();
    }
}


Warrior::Warrior( string name_, int healthPower_, int magicPower_, int strength_,
        int dexterity_, int agility_, int money_) :
        Hero(name_, healthPower_ , magicPower_, strength_ + spec_stat_boost,
        dexterity_, agility_ + spec_stat_boost , money_) {}

void Warrior::levelUp() {
    cout << "Warrior: " << name << " has leveled UP!" << endl;
    strength += lvlUp_stat_boost + spec_stat_boost;
    dexterity += lvlUp_stat_boost;
    agility += lvlUp_stat_boost + spec_stat_boost;
}

void Warrior::print() { 
    cout << "\nPrinting\nWarrior: " << name 
         << "\nHealthPower: " << healthPower 
         << "\nMagicPower: " << magicPower
         << "\nLevel: " << level
         << "\nStrength: " << strength
         << "\nDexterity: " << dexterity 
         << "\nAgility: " << agility
         << "\nMoney: " << money << endl;
}


Sorcerer::Sorcerer( string name_, int healthPower_, int magicPower_, int strength_,
        int dexterity_, int agility_, int money_) :
        Hero(name_, healthPower_ , magicPower_, strength_, 
        dexterity_ + spec_stat_boost, agility_ + spec_stat_boost, money_) {}

void Sorcerer::levelUp() {
    cout << "Sorcerer: " << name << " has leveled UP!" << endl;
    strength += lvlUp_stat_boost;
    dexterity += lvlUp_stat_boost + spec_stat_boost;
    agility += lvlUp_stat_boost + spec_stat_boost;
}
void Sorcerer::print() { 
    cout << "\nPrinting\nSorcerer: " << name 
         << "\nHealthPower: " << healthPower 
         << "\nMagicPower: " << magicPower
         << "\nLevel: " << level
         << "\nStrength: " << strength
         << "\nDexterity: " << dexterity 
         << "\nAgility: " << agility
         << "\nMoney: " << money << endl;
}

Paladin::Paladin( string name_, int healthPower_, int magicPower_, int strength_,
        int dexterity_, int agility_, int money_) :
        Hero(name_, healthPower_ , magicPower_, strength_ + spec_stat_boost,
        dexterity_ + spec_stat_boost , agility_, money_) {}

void Paladin::levelUp() {
    cout << "Paladin: " << name << " has leveled UP!" << endl;
    strength += lvlUp_stat_boost + spec_stat_boost;
    dexterity += lvlUp_stat_boost + spec_stat_boost;
    agility += lvlUp_stat_boost;
}

void Paladin::print() { 
    cout << "\nPrinting\nPaladin: " << name 
         << "\nHealthPower: " << healthPower 
         << "\nMagicPower: " << magicPower
         << "\nLevel: " << level
         << "\nStrength: " << strength
         << "\nDexterity: " << dexterity 
         << "\nAgility: " << agility
         << "\nMoney: " << money << endl;
}


Monster::Monster(string name_, int healthPower_, int min_damage_,
                     int max_damage_, int armor_, int dodge_) : 
        Living(name_, healthPower_),min_damage(min_damage_),
             max_damage(max_damage_), armor(armor_), dodge(dodge_) {}


Dragon::Dragon(string name_, int healthPower_, int min_damage_,
            int max_damage_, int armor_, int dodge_) :
            Monster(name_, healthPower_, min_damage_ + enemy_Stat_boost,
                    max_damage_ + enemy_Stat_boost , armor_, dodge_) {}

void Dragon::print() {
    cout << "\nPrinting\nDragon: " << name 
         << "\nHealthPower: " << healthPower 
         << "\nLevel: " << level
         << "\nDamage range: " << min_damage << " - " << max_damage
         << "\nArmor: " << armor 
         << "\nDodge: " << dodge << endl;
}

Exoskeleton::Exoskeleton(string name_, int healthPower_, int min_damage_,
            int max_damage_, int armor_, int dodge_) :
            Monster(name_, healthPower_, min_damage_,
             max_damage_, armor_ + enemy_Stat_boost, dodge_) {}

void Exoskeleton::print() {
    cout << "\nPrinting\nExoskeleton: " << name 
         << "\nHealthPower: " << healthPower 
         << "\nLevel: " << level
         << "\nDamage range: " << min_damage << " - " << max_damage
         << "\nArmor: " << armor 
         << "\nDodge: " << dodge << endl;
}

Spirit::Spirit(string name_, int healthPower_, int min_damage_,
            int max_damage_, int armor_, int dodge_) :
            Monster(name_, healthPower_, min_damage_,
             max_damage_, armor_, dodge_ + enemy_Stat_boost) {}

void Spirit::print() {
    cout << "\nPrinting\nSpirit: " << name 
         << "\nHealthPower: " << healthPower 
         << "\nLevel: " << level
         << "\nDamage range: " << min_damage << " - " << max_damage
         << "\nArmor: " << armor 
         << "\nDodge: " << dodge << endl;
}