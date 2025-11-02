#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <ctime>  
#include <list>
#include "Goat.h"
using namespace std;

// Import

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
void avg_age(list<Goat>& trip);
void any_old_enough(list<Goat>& trip);
void find_by_name(list<Goat>& trip);
void birthday_all(list<Goat>& trip);
void remove_color(list<Goat>& trip);
void reverse_trip(list<Goat>& trip);
void names_transform(list<Goat>& trip);
void dedupe_names(list<Goat>& trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(Goat(name, age, color));
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:  avg_age(trip);            
                break; 
            case 5:  any_old_enough(trip);     
                break;
            case 6:  find_by_name(trip);       
                break; 
            case 7:  birthday_all(trip);       
                break; 
            /*case 8:  remove_color(trip);       
                break; 
            case 9:  reverse_trip(trip);       
                break;
            case 10: names_transform(trip);    
                break; 
            case 11: dedupe_names(trip);       
                break;*/
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Average age (accumulate)\n";
    cout << "[5] Any goat >= N years? (any_of)\n";
    cout << "[6] Find first by name (find_if)\n";
    cout << "[7] Give everyone a birthday +1 (for_each)\n";
    cout << "[8] Remove all of a color (remove_if + erase)\n";
    cout << "[9] Reverse order (reverse)\n";
    cout << "[10] Copy names (transform)\n";
    cout << "[11] De-duplicate by name (unique)\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice; cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void avg_age(list<Goat>& trip) {
    if (trip.empty()) { cout << "Trip is empty.\n"; return; }
    int total = accumulate(trip.begin(), trip.end(), 0,[](int acc, const Goat& g){ 
        return acc + g.get_age(); });
    cout << fixed << setprecision(2)
         << "Average age: " << (double)total / trip.size() << "\n";
}

void any_old_enough(list<Goat>& trip) {
    if (trip.empty()) { cout << "Trip is empty.\n"; return; }
    int n; 
    cout << "Enter N (years): "; 
    cin >> n;
    bool ok = any_of(trip.begin(), trip.end(),
        [n](const Goat& g){ return g.get_age() >= n; });
    cout << (ok ? "Yes" : "No") << ", at least one goat is >= " << n << ".\n";
}

void find_by_name(list<Goat>& trip){
    if (trip.empty()) { cout << "Trip is empty.\n"; return; }
    string want; 
    cout << "Name to find: "; cin >> want;
    auto it = find_if(trip.begin(), trip.end(),
        [&want](const Goat& g){ return g.get_name() == want; });
    if (it == trip.end()) {
        cout << "No goat named '" << want << "'.\n";
    }
    else{
        cout << "Found: " << it->get_name()
        << "(age " << it->get_age()
        << ", color: " << it->get_color()<< ")\n";
    }
}

void birthday_all(list<Goat>& trip){
    if (trip.empty()) { cout << "Trip is empty.\n"; return; }
    for_each(trip.begin(), trip.end(),
        [](Goat& g){ g.set_age(g.get_age() + 1); });
    cout << "Every goat just had a birthday! (+1 age)\n";
}

