// Goat.h

#ifndef GOAT_H
#define GOAT_H
#include <iostream>
#include <string>


using namespace std;

const int MAX_AGE = 20;

class Goat {
private:
    string name;
    int age;
    string color;
public: 
    Goat()                          { name = ""; age = 0; color = ""; }
    Goat(string n)                  { name = n; age = rand() % MAX_AGE; color = ""; }
    Goat(string n, int a)           { name = n; age = a; color = ""; }
    Goat(string n, int a, string c) { name = n; age = a; color = c; }
    void set_name(string n)         { name = n; };
    string get_name() const         { return name; };
    void set_age(int a)             { age = a; };
    int get_age() const             { return age; }
    void set_color(string c)        { color = c; }
    string get_color() const        { return color; }

    bool operator< (const Goat &other) const {
        return name < other.name;
    }
};

#endif