#include "grid2.hpp"



void gridTile::print() {
}

int Common::select_hero_from_party() {
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
}

int Market::select_hero_from_party() {
    cout << "\nSelect Hero index" << endl;
    for(int i = 0 ; i < heroes.size() ; i++) {
        cout << "\nIndex :" << i;
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
}


// Κανει τους απαραιτητους ελέγχους και επιστρέφει true αν ο ήρωας αγόρασε
// ή false αν δεν πραγματοποιήθηκε αγορά
bool Market::buy() {
    cout << "\nUSING BUY\n";
    if(heroes.size() == 0) {
        cout << "No hero available" << endl;
        return false;
    }
    bool zero_items = false;
    bool zero_spells = false;

    if(items.size() == 0) {
        zero_items = true;
        cout << "No items available" << endl;
    }
        

    if(spells.size() == 0) {
        zero_spells = true;
        cout << "No spells available" << endl;
    }
        

    if(items.size() == 0 && spells.size() == 0) 
        return false;    
    

    // ΕΠΙΛΟΓΗ ΗΡΩΑ

    int hero_index = select_hero_from_party();

    cout << "\nPress 1 to Buy Items, 2 to Buy Potions" << endl;
    int decision;
    bool decided = false;
    while(!decided) {
        cin >> decision;
        switch(decision) {
            case 1:
                if(zero_items) {
                    cout << "There are no items" << endl;
                    break;
                }
                buy_item(hero_index);
                decided = true;
                break;
            case 2:
                if(zero_spells) {
                    cout << "There are no spells" << endl;
                    break;
                }
                buy_spell(hero_index);
                decided = true;
                break;

        }
    }
}

bool Market::buy_item(int hero_index) {
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

bool Market::buy_spell(int hero_index) {
    // ΕΠΙΛΟΓΗ ΑΝΤΙΚΕΙΜΕΝΟΥ
    cout << "Select item index or -1 to exit" << endl;
    for(int i = 0 ; i < spells.size() ; i++) {
        cout << "Index :" << i;
        spells[i]->print();
        cout << "\n";
    }

    while(true) {
        int index;
        cin >> index;
        if(index == -1 ) {
            cout << "Exiting without buying" << endl; 
            return false;
        }
        if(index >= spells.size()) {
            cout << "Select correct index" << endl;
        } else {
            int price = spells[index]->get_price();
            if(heroes[hero_index]->get_money() < price ) {
                cout << "Not enough money, select again" << endl;
            } else {
                heroes[hero_index]->sub_money(price);
                heroes[hero_index]->add_item_to_inventory(spells[index]);
                cout << "Hero bought item with index: " << index << endl;

                // Διαγράφω απο το Market το αντικείμενο που πουλήθηκε με iterators
                vector<Spell*>::iterator it = spells.begin();
                it += index;
                spells.erase(it);

                return true;
            }
        }
    }
}


bool Market::sell() {
    cout << "\nUSING SELL\n";
    // ΕΠΙΛΟΓΗ ΗΡΩΑ
    int hero_index = select_hero_from_party();
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
    if(heroes.size() == 0) {cout << "[M ]";}
    else {cout << "[Mh]";}

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
    if(heroes.size() == 0) cout << "[C ]";
    else cout << "[Ch]";

}   

void nonAccessible::print() {
    cout << "Printing nonAccessible Tile at:\nx:" << this->x << ", y:" << this->y << endl;
}
void nonAccessible::print_graphic() {
    cout << "[N ]";
}


Grid::Grid() : size_x(5), size_y(5) {
    for(int i = 0 ; i < size_x  ; i++) {
        for(int j = 0 ; j < size_y ; j++) {
            if(i == 0  || j == 0 || i == 4 || j == 4) {
                grid[i][j] = new nonAccessible(i,j);
            } else {
                grid[i][j] = new Common(i,j);
            }
            
        }
    }
    make_Market(2,2);
    make_nonAccessible(2,4);
    make_nonAccessible(3,1);
    Dragon* d = new Dragon("Onyxia", 100, 5, 10, 20, 30);
    grid[1][1]->set_monsters(d);
    Dragon* d1 = new Dragon("Deathwing", 100, 5, 10, 20, 30);
    grid[1][2]->set_monsters(d1);
    Exoskeleton* e = new Exoskeleton("Cyrrollalee", 100, 5,10,20,30);
    grid[1][3]->set_monsters(e);
    Exoskeleton* e1 = new Exoskeleton("Brandobaris", 100, 5,10,20,30);
    grid[2][1]->set_monsters(e1);
    Spirit* sp = new Spirit("Nami", 100, 5, 10, 20, 30);
    grid[2][3]->set_monsters(sp);
    Spirit* sp1 = new Spirit("Gadhelyn", 100, 5, 10, 20, 30);
    grid[3][2]->set_monsters(sp1);
    Spirit* sp2 = new Spirit("Soraka", 100, 5, 10, 20, 30);
    grid[3][3]->set_monsters(sp2);


    Weapon* w = new Weapon("Axe",50,0,10,true);
    IceSpell* i = new IceSpell("speeelll",10,4,4,10,4,4,4);
    grid[2][2]->add_item(w);
    grid[2][2]->add_item(i);
}


void Grid::start(vector<Hero*> p) {
    this->party = p;
    for(int i = 0 ; i < party.size() ; i++) {
        party[i]->set_coordinates(1,1);
    }
    grid[1][1]->set_party(this->party);
}


bool Grid::move_party_to_coordinates(int x, int y, vector<Hero*> p) {
    // Αρχικές συντεταγμένες
    Coordinates before_move = p[0]->get_coordinates();
    // Το τετραγωνο ειναι nonAccessible
    if(!grid[x][y]->can_move()) {
        return false;
    } else
    // Το τετράγωνο είναι accessible (common/market) 
    {
        // Αλλαζω τις συντεταγμένες των ηρώων του party
        for(int i = 0 ; i < party.size() ; i++) {
            p[i]->set_coordinates(x, y); 
        }
        // Ενημερώνω το καινούριο τετράγωνο με το party
        grid[x][y]->set_party(p);
        // Αφαιρώ το party απο το προηγούμενο τετράγωνο
        grid[before_move.x][before_move.y]->remove_party();
        return true;
    }
}


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
                moved = move_party_to_coordinates(c.x + 1, c.y , party);
                break;
            case left:
                moved = move_party_to_coordinates(c.x, c.y - 1 , party);
                break;
            case up:
                moved = move_party_to_coordinates(c.x - 1, c.y , party);
                break;
            case right:
                moved = move_party_to_coordinates(c.x , c.y + 1 , party);
                break;
        }
        if(!moved) cout << "Cant move there\n";
    }
}


void Grid::decide_buy_sell() {
    bool decided = false;
    Coordinates c = party[0]->get_coordinates();
    while(!decided) {
        int decision;
        cout << "\nPress 1 to Buy, 2 to Sell, -1 to Exit\n";
        cin >> decision;
        switch (decision)
        {
        case 1:
            grid[c.x][c.y]->buy();
            // decided = true;
            break;
        
        case 2: 
            grid[c.x][c.y]->sell();
            // decided = true;
            break;
        case -1:
            cout << "Exiting" << endl;
            decided = true;
            break;
        }
    }
}

void Grid::decide_inventory_equip_use() {
    cout << "\nSelect hero to check_inventory/equip/use\n";
    // ΕΠΙΛΟΓΗ ΗΡΩΑ
    cout << "Select Hero index" << endl;
    for(int i = 0 ; i < party.size() ; i++) {
        cout << "Index :" << i;
        party[i]->print();
        cout << "\n";
    }
    int hero_index;
    bool selected = false;
    // Ελεγχος μεχρι να γινει σωστη επιλογη ήρωα
    while(!selected) {
        cin >> hero_index;
        if(hero_index >= party.size()) {
            cout << "Select correct index" << endl;
        } else {
            selected = true;
        }
    }

    
    bool decided = false;
    Hero* hero = party[hero_index];
    while(!decided) {
        cout << "\nPress 1 to Check Inventory, 2 to Equip, 3 to Use, -1 to Exit\n";
        int decision;
        cin >> decision;
        switch(decision) {
            case 1:
                hero->checkInventory();
                // decided = true;
                break;
            case 2:
                hero->equip();
                // decided = true;
                break;
            case 3:
                hero->use();
                // decided = true;
                break;
            case -1:
                decided = true;
                cout << "\nExiting" << endl;
                break;

        }
    }
}

void Grid::battle() {
    Coordinates c = party[0]->get_coordinates();
    grid[c.x][c.y]->battle();
}

void Grid::move_many() {
    int move;
    decide_inventory_equip_use();
    while(true) {
        cout << "\nPress 1 to move or -1 to exit\n";
        cin >> move;
        if(move == 1) {
            this->move();
            this->print_graphic();
            Coordinates c = party[0]->get_coordinates();
            decide_inventory_equip_use();
            if(grid[c.x][c.y]->is_market()) {
                // decide_inventory_equip_use();
                decide_buy_sell();
            } else if(grid[c.x][c.y]->is_common()) {
                // decide_inventory_equip_use();
                // battle();
            }
        } else {
            break;
        }
    }
}

void Common::battle() {
        while( heroes_alive() && monsters_alive() ) {
        // Ο καθε ηρωας
            for(int i = 0 ; i < heroes.size() ; i++) {
                // Θα επιτεθει στο πρωτο τερας που θα βρει ζωντανό
                for(int j = 0 ; j < monsters.size() ; j++) {
                    if(monsters[j]->alive()) {
                        monsters[j]->get_attacked(heroes[i]->attack());
                        // Και θα ερθει η σειρα του επομενου ηρωα
                        break;
                    }
                }
            }
            // Το καθε τερας
            for(int i = 0 ; i < monsters.size() ; i++) {
                // Θα επιτεθει στον πρωτο ηρωα που θα βρει ζωντανο
                for(int j = 0 ; j < heroes.size() ; j++) {
                    if(heroes[j]->alive()) {
                        heroes[j]->get_attacked(monsters[i]->attack());
                        // Και θα ερθει η σειρα του επομενου τερατος
                        break;
                    }
                }
            }
        }
        if(heroes_alive()) {
            for(int i = 0 ; i < heroes.size() ; i++) {
                cout << "Heroes have won!" << endl;
                heroes[i]->win();
            }
        } else {
            for(int i = 0 ; i < heroes.size() ; i++) {
                cout << "Heroes have lost!" << endl;
                heroes[i]->lose();
            }
        }
}


bool Common::heroes_alive() {
    // Αν οποιοσδηποτε ηρωας ειναι ζωντανος, τοτε το party ειναι ζωντανό
    for(int i = 0 ; i < heroes.size() ; i++) {
        if(heroes[i]->alive()) return true;
    }
    return false;
}

bool Common::monsters_alive() {
    // Αν οποιοσδηποτε ηρωας ειναι ζωντανος, τοτε το party ειναι ζωντανό
    for(int i = 0 ; i < monsters.size() ; i++) {
        if(monsters[i]->alive()) return true;
    }
    return false;
}

