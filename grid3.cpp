#include "grid2.hpp"



void gridTile::print() {
}

// Κανει τους απαραιτητους ελέγχους και επιστρέφει true αν ο ήρωας αγόρασε
// ή false αν δεν πραγματοποιήθηκε αγορά
bool Market::buy() {
    cout << "\nUSING BUY\n";
    if(heroes.size() == 0) {
        cout << "No hero available" << endl;
        return false;
    }
    if(items.size() == 0) {
        cout << "No items available" << endl;
        return false;
    }

    // ΕΠΙΛΟΓΗ ΗΡΩΑ
    cout << "Select Hero index" << endl;
    for(int i = 0 ; i < heroes.size() ; i++) {
        cout << "Index :" << i;
        heroes[i]->print();
        cout << "\n";
    }
    int hero_index;
    bool selected = false;
    // Ελεγχος μεχρι να γινει σωστη επιλογη ήρωα
    while(!selected) {
        cin >> hero_index;
        if(hero_index >= heroes.size()) {
            cout << "Select correct index" << endl;
        } else {
            selected = true;
        }
    }

    // ΕΠΙΛΟΓΗ ΑΝΤΙΚΕΙΜΕΝΟΥ
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
            if(heroes[hero_index]->get_money() < price ) {
                cout << "Not enough money, select again" << endl;
            } else {
                heroes[hero_index]->sub_money(price);
                heroes[hero_index]->add_item_to_inventory(items[index]);
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


bool Market::sell() {
    cout << "\nUSING SELL\n";
    if(this->heroes.size() == 0) {
        cout << "No hero available" << endl;
        return false;
    }
        // ΕΠΙΛΟΓΗ ΗΡΩΑ
    cout << "\nSelect Hero index or -1 to exit" << endl;
    for(int i = 0 ; i < heroes.size() ; i++) {
        cout << "Index :" << i;
        heroes[i]->print();
        cout << "\n";
    }
    int hero_index;
    bool selected = false;
    // Ελεγχος μεχρι να γινει σωστη επιλογη ήρωα
    while(!selected) {
        cin >> hero_index;
        if(hero_index == -1) {
            cout << "Exiting without selling" << endl;
            return false;
        }
        if(hero_index >= heroes.size()) {
            cout << "Select correct index" << endl;
        } else {
            selected = true;
        }
    }
    return heroes[hero_index]->sell();
}




void Market::print() {
    cout << "Printing Market Tile at:\nx:" << this->x << ", y:" << this->y << endl;
    if(heroes.size() == 0) {
        cout << "No heroes are here" << endl;
    }  else {
        cout << "\e[1m  \nHeroes:\n   \e[0m";
        for(int i = 0 ; i < heroes.size() ; i++) {
            heroes[i]->print();
        }
    }
    if(items.size() == 0) {
        cout << "There are 0 items available on the market" << endl;
    } else {
        cout << "Available items:\n";
        for(int i = 0 ; i < items.size() ; i++) {
            items[i]->print();
        }
    }
}

void Market::print_graphic() {
    cout << "[M]";
}

void Common::print() {
    cout << "Printing Common Tile at:\nx:" << this->x << ", y:" << this->y << endl;
    if(heroes.size() == 0) {
        cout << "No heroes are here" << endl;
    }  else {
        cout << "\e[1m  \nHeroes:\n  \e[0m";
        for(int i = 0 ; i < heroes.size() ; i++) {
            heroes[i]->print();
        }
    }
    if(monsters.size() == 0) {
        cout << "No monsters are here" << endl;
    }  else {
        cout << "\e[1m  \nMonsters:\n  \e[0m";
        for(int i = 0 ; i < monsters.size() ; i++) {
            monsters[i]->print();
        }
    }
}

void Common::print_graphic() {
    cout << "[C]";
}

void nonAccessible::print() {
    cout << "Printing nonAccessible Tile at:\nx:" << this->x << ", y:" << this->y << endl;
}
void nonAccessible::print_graphic() {
    cout << "[N]";
}



void Grid::start(vector<Hero*> p) {
    this->party = p;
    for(int i = 0 ; i < party.size() ; i++) {
        party[i]->set_coordinates(1,1);
    }
    grid[1][1]->set_party(this->party);
}


// void Grid::move_party_to_coordinates(int x, int y) {
//     for(int i = 0 ; i < party.size() ; i)
// }


void Grid::move() {
    cout <<"\nChoose where to move" << endl;
    bool moved = false;
    Coordinates c = party[0]->get_coordinates();
    const int down = 2, left = 4, up = 8, right = 6; 
    while(!moved) {
        int direction;
        cin >> direction;
        switch(direction) {
            case down: 
                if(grid[c.x + 1][c.y]->can_move()) {
                    cout <<"Move down\n";
                    // Αλλαζω την θεση όλων των ηρώων
                    for(int i = 0 ; i < party.size() ; i++) {
                        party[i]->set_coordinates(c.x + 1, c.y); 
                    }
                    // Ενημερώνω το καινούριο τετράγωνο με τους ήρωες
                    grid[c.x + 1][c.y]->set_party(party);
                    // ΔΙαγράφω τους ήρωες απο το παλιό τετράγωνο
                    grid[c.x][c.y]->remove_party();
                    moved = true;
                }
                break;
            case left:
                if(grid[c.x][c.y - 1]->can_move()) {
                    cout <<"Move left\n";
                    // Αλλαζω την θεση όλων των ηρώων
                    for(int i = 0 ; i < party.size() ; i++) {
                        party[i]->set_coordinates(c.x, c.y - 1);
                    }
                    grid[c.x][c.y - 1]->set_party(party);
                    grid[c.x][c.y]->remove_party();
                    moved = true;
                } 
                break;
            case up:
                if(grid[c.x - 1][c.y]->can_move()) {
                    cout <<"Move up\n";
                    // Αλλαζω την θεση όλων των ηρώων
                    for(int i = 0 ; i < party.size() ; i++) {
                        party[i]->set_coordinates(c.x - 1, c.y);
                    }
                    grid[c.x - 1][c.y]->set_party(party);
                    grid[c.x][c.y]->remove_party();
                    moved = true;
                } 
                break;
            case right:
                if(grid[c.x][c.y + 1]->can_move()) {
                    cout <<"Move right\n";
                    // Αλλαζω την θεση όλων των ηρώων
                    for(int i = 0 ; i < party.size() ; i++) {
                        party[i]->set_coordinates(c.x, c.y + 1);
                    }
                    grid[c.x][c.y + 1]->set_party(party);
                    grid[c.x][c.y]->remove_party();
                    moved = true;
                } 
                break;
        }
        if(!moved) cout << "Cant move there\n";
    }
}