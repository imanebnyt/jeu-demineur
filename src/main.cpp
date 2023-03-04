#include <iostream>
#include <random>
#include "grid.h"

int main() {
    srand((unsigned) time(nullptr));

    unsigned command;
    std::cin >> command;
    switch (command) {
        // création du problème
        case 1:
            createProblem();
            break;
        // création de la grille
        case 2:
            createGrid();
            break;
        case 3:
        // retourne le résultat pour une commande donnée
        case 4:
            getResult(command);
            break;
        // lecture de la grille
        case 5:
            readGrid();
            break;
        // dans le cas ou commande non reconnue
        default:
            std::cout << "Commande inconnue...";
            break;
    }
}