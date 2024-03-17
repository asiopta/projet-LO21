#pragma once
#include <iostream>
#include <string>
using namespace std;

enum class RessourcePrimaire {
    Pierre,
    Bois,
    Brique
};

enum class RessourceSecondaire {
    verre,
    parchemin
};

class Carte{
private:
    unsigned int age;
    unsigned int coutconstruction;
    //materiauxconstruction;


public:
    void setAge(int newAge) {
        if (newAge >= 1 && newAge <= 3) {
            age = newAge;
        } else {
            cout<< "Error: Age must be 1, 2, or 3." << endl;
        }
    }

    int getAge() const {
        return age;
    }
};

class Merveille{
private:
    Carte c;
    unsigned int ptVictoire;
    RessourceSecondaire production[3];

public:

};