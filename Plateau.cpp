#include "Plateau.h"

JetonScience::JetonScience(CapaciteScience capacite) : capacite(capacite) {}
void JetonScience::exec_capacite_science() {
    switch (capacite) {
        exec_agriculture(); break;
        case CapaciteScience::architecture: exec_architecture(); break;
        case CapaciteScience::economie: exec_economie(); break;
        case CapaciteScience::loi: exec_loi(); break;
        case CapaciteScience::maconnerie: exec_maconnerie(); break;
        case CapaciteScience::urbanisme: exec_urbanisme(); break;
        case CapaciteScience::theologie: exec_theologie(); break;
        case CapaciteScience::strategie: exec_strategie(); break;
        case CapaciteScience::philosophie: exec_philosophie(); break;
        case CapaciteScience::mathematique: exec_mathematique(); break;
        default:
            std::cout << "Erreur";
    }
}

void exec_agriculture() {
    // implementation of exec_agriculture
}

void exec_architecture() {
    // implementation of exec_architecture
}

void exec_economie() {
    // implementation of exec_economie
}

void exec_loi() {
    // implementation of exec_loi
}

void exec_maconnerie() {
    // implementation of exec_maconnerie
}

void exec_urbanisme() {
    // implementation of exec_urbanisme
}

void exec_theologie() {
    // implementation of exec_theologie
}

void exec_strategie() {
    // implementation of exec_strategie
}

void exec_philosophie() {
    // implementation of exec_philosophie
}

void exec_mathematique() {
    // implementation of exec_mathematique
}


//Jetons Malus
JetonMalus::JetonMalus(int malus) : malus(malus) {}

void exec_malus() {
    // implementation of exec_malus
}


