#include <iostream>
using namespace std;
// #include "item.hpp"
// #include "spell.hpp"
// #include "living.hpp"
#include "grid2.hpp"


int main() {
    Sorcerer* s = new Sorcerer("stelios",30,100,10,5,5,100);
    Weapon* w = new Weapon("Axe",5,1,20,true);
    s->equip(w);
    Exoskeleton* e = new Exoskeleton("marilena",1000,10,20,5,0);
    Grid* g = new Grid;
    vector<Hero*> nice;
    nice.push_back(s);
    // nice.push_back(w);

    g->start(nice);
    g->print_graphic();
    g->move_many();

    // vector<Hero*> h;
    // h.push_back(s);
    // Common* c = new Common(1,1);
    // c->set_monsters(e);
    // c->set_party(h);
    // c->battle();


 
    return 0;
}