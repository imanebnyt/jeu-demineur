//
// Created by Imane & Ranim;
//

#ifndef I_MINESWEEPER_GRID_H
#define I_MINESWEEPER_GRID_H

#include "case.h"
#include "problem.h"

struct Grid {
    Problem pb;
    Case **ms; // MineSweeper
};

/**
 * @brief Vérifie les coordonées x et y
 * @param[in] grid la grille
 * @param[in] x à vérifier
 * @param[in] y à vérifier
 * @return true si les coordonées sont valides, false sinon
 */

bool validCoords(Grid &grid, unsigned x, unsigned y);

/**
 * @brief set mine from buffer
 * @param[inout] grid
 */
void setMines(Grid &grid);

/**
 * @brief génération du démineur
 * @param[inout] grid la grille du démineur
 */
void generateMS(Grid &grid);

/**
 * @brief place les mines dans le jeu du démineur
 * @param[inout] gridla grille du jeu
 */
void placeMines(Grid &grid);

/**
 * @brief ajoute +1 à la case adjacente à une mine
 * @param[inout] grid grille du jeu
 * @param[in] x coordonée x de la mine
 * @param[in] y coordonée y de la mine
 */
void addMineAdj(Grid &grid, unsigned &x, unsigned &y);

/**
 * @brief place les valeurs dans le démineur
 * @param[inout] grid la grille du jeu
 */
void fillMS(Grid &grid);

/**
 * @brief démasquer une case
 * @param[inout] grid grille du jeu
 * @param x coordonée x de la case
 * @param y coordonée y de la case
 */

void unmaskMine(Grid &grid, unsigned x, unsigned y);

/**
 * @brief execution d'un mouvement
 * @param[in] grid grille du jeu
 */
void executeMoves(Grid &grid);

/**
 * @brief montrer la grille
 * @param[in] grid grille du jeu
 */
void showGrid(Grid &grid);

/**
 * @brief annonce si le jeu est gagné 
 * @param[in] grid grille du jeu
 * @return true si utilisateur gagnant, false sinon
 */
bool gameWon(Grid &grid);

/**
 * @brief annonce si jeu perdu
 * @param[in] grid grille du jeu
 * @return true si jeu perdu, false sinon
 */
bool gameLost(Grid &grid);

/**
 * @brief montre le résultat
 * @param[in] grid grille du jeu
 * @param cmd obtenir la commande d'execution
 */
void showResult(Grid &grid, unsigned cmd);

/**
 * @brief retourne la prochaine action
 * @param[in] grid grille 
 */
void getActionToPlay(Grid &grid);

/**
 * @brief supprime toute l'allocation dynamique en mémoire de la grille
 * @param grid grille dont la mémoire doit etre supprimée
 */
void deleteGrid(Grid &grid);

/**
 * @brief crée une grille
 */
void createGrid();

/**
 * @brief retourne l'état du jeu
 * @param cmd commande à executer
 */
void getResult(unsigned cmd);

/**
 * @brief lectire de la grille
 */
void readGrid();

#endif //I_MINESWEEPER_GRID_H
