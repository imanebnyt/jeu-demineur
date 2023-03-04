#ifndef I_MINESWEEPER_PROBLEM_H
#define I_MINESWEEPER_PROBLEM_H

struct Problem {
    unsigned lines, columns, mines;
    unsigned *minePos;
};

/**
 * @brief retourne les coordonnées du problème
 * @param[in] pb probleme donnée
 * @param[in] pos position à traduire
 * @param[out] x coord 'x'
 * @param[out] y coord 'y'
 */
void getCoords(Problem &pb, unsigned pos, unsigned &x, unsigned &y);

/**
 * @brief initialisation des colonnes, lignes et mines pour le problème
 * @param[out] pb problème à sauvegarder
 */
void setProblem(Problem &pb);

/**
 * @brief initialisation d'un problème sans mines
 * @param[out] pb problème à sauvegarder
 */
void setBasicProblem(Problem &pb);

/**
 * @brief génére des mines de manière aléatoire
 * @param[in] pb probleme à sauvegarder
 */
void generateMines(Problem &pb);

/**
 * @brief dévoile le probleme
 * @param[in] pb probleme a montrer
 */
void printProblem(Problem &pb);

/**
 * @brief suppression de l'allocation dynamique en mémoire
 * @param pb probleme dont l'allocation soit etre effacée
 */
void deleteProblem(Problem &pb);

/**
 * @brief création d'un probleme
 */
void createProblem();

#endif //I_MINESWEEPER_PROBLEM_H
