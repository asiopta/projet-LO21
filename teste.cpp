#include <iostream>
#include <string>

using namespace std;


class Carte{
private:
    unsigned int age;
    unsigned int cout_construction;

public:

    //constructeur


    //methodes
    void setAge(int newAge);
    int getAge() const;


    //methode virtuelle pure, cad est appelable uniquement par les classes filles, et à definir pour chaques classes filles
    virtual string gettype() const = 0;

    //destructeur
    virtual ~Carte();
};

class CarteBleu : public Carte{
private:
    int element1;

public:

    //constructeur


    //methodes
    void setAge(int newAge);
    int getAge() const;


    //methode virtuelle pure, cad est appelable uniquement par les classes filles, et à definir pour chaques classes filles
    virtual string gettype() const = 0;

    //destructeur
    virtual ~CarteBleu();
};

class CarteBleu : public Carte{
private:
    int element1;

public:

    //constructeur


    //methodes
    void setAge(int newAge);
    int getAge() const;


    //methode virtuelle pure, cad est appelable uniquement par les classes filles, et à definir pour chaques classes filles
    virtual string gettype() const = 0;

    //destructeur
    virtual ~CarteBleu();
};

class CarteRouge : public Carte{
private:
    unsigned int element2;

public:

    //constructeur


    //methodes
    void setAge(int newAge);
    int getAge() const;


    //methode virtuelle pure, cad est appelable uniquement par les classes filles, et à definir pour chaques classes filles
    virtual string gettype() const = 0;

    //destructeur
    virtual ~CarteRouge();
};


class Joueur{
private:
    Carte cartejoueur;

public:
   //destructeur
   ~Joueur();
};
