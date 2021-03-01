#include "grid.hpp"





// Επιστρεφει false αν το τετραγωνο δεν ειναι accesible, 
// αλλιως βαζει εκει τον ηρωα και επιστρεφει true
bool gridTile::set_hero(Hero* h_) {
    if(!is_accesible()) {
        cout << "Non accesible tile" << endl;
        return false;
    }
    this->h = h_;
    return true;
}

bool gridTile::set_monster(Monster* m_) {
    if(!is_common()) { 
        cout << "Cant assign monster. Tile not common!" << endl;
        return false;
    }
    this->m = m_;
    return true;
}

bool gridTile::add_item(Item* i) {
    if(!is_market()) {
        cout << "This is not a market" << endl;
        return false;
    }

    this->items.push_back(i);
    return true;
}

// 


void gridTile::print() {
    cout << "\nPrinting TILE: ";
    if(is_common()) cout << "Common ";
    if(is_market()) cout << "Market ";
    if(is_accesible()) cout << "Accesible ";
    if(!is_accesible()) return;
    if(is_market()) {
        cout << "\nPrinting market:" << endl;
        for(int i = 0 ; i < items.size() ; i++ )
            items[i]->print();
    }
    
    if(h != NULL) {
        cout <<"\nWith Hero:";
        h->print();
    } else cout << endl;
    if(m != NULL) {
        cout <<"\nWith Monster:";
        m->print();
    } else cout << endl;
    
}

// Κανει τους απαραιτητους ελέγχους και επιστρέφει true αν ο ήρωας αγόρασε
// ή false αν δεν πραγματοποιήθηκε αγορά
bool gridTile::buy() {
    if(!is_market()) {
        cout <<"Tile not a market" << endl;
        return false;
    }
    if(this->h == NULL) {
        cout << "No hero available" << endl;
        return false;
    }
    if(items.size() == 0) return false;
    cout << "Select item index or -1 to exit" << endl;
    for(int i = 0 ; i < items.size() ; i++) {
        cout << "Index :" << i;
        items[i]->print();
        cout << "\n";
    }

    while(true) {
        int index;
        cin >> index;
        if(index == -1 ) {
            cout << "Exiting without buying" << endl; 
            return false;
        }
        if(index >= items.size()) {
            cout << "Select correct index" << endl;
        } else {
            int price = items[index]->get_price();
            if(h->get_money() < price ) {
                cout << "Not enough money, select again" << endl;
            } else {
                h->sub_money(price);
                h->add_item_to_inventory(items[index]);
                cout << "Hero bought item with index: " << index << endl;

                // Διαγράφω απο το Market το αντικείμενο που πουλήθηκε με iterators
                vector<Item*>::iterator it = items.begin();
                it += index;
                items.erase(it);

                return true;
            }
        }
    }

}


bool gridTile::sell() {
    if(!is_market()) {
        cout <<"Tile not a market" << endl;
        return false;
    }
    if(this->h == NULL) {
        cout << "No hero available" << endl;
        return false;
    }
    return h->sell();
}