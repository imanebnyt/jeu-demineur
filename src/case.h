#ifndef I_MINESWEEPER_CASE_H
#define I_MINESWEEPER_CASE_H

// type énumeré pour indiquuer l'état de la mine : visible, marquée, ou cachée
enum STATE {
    VISIBLE, HIDDEN, MARKED
};

// 9 mines
enum {
    MINE = 9
};

// type struct d'une case
struct Case {
    STATE state;
    unsigned content; //9 == MINE
};

/**
 * @brief montre l'élement au sein d'une case donnée
 * @param[in] bloc la case à dévoiler
 * @return char à montrer
 */
char showElement(Case &bloc);

/**
 * @brief marque la mine pour une case donnée
 * @param[inout] bloc
 */
void markMine(Case &bloc);

#endif //I_MINESWEEPER_CASE_H
