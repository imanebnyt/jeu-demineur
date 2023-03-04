#include "case.h"

// controle visibilite des mines sur la grille
char showElement(Case &bloc) {
    switch (bloc.state) {

        case VISIBLE: // mine visible
            if (bloc.content > 8) return 'm';
            if (bloc.content == 0) return ' ';
            return (char) (48 + bloc.content);
        case HIDDEN: // mine cachee
            return '.';
        case MARKED: // mine barree
            return 'x';
    }
}

/**
 * @brief fonction marquant les mines
 * @param bloc 
 */

void markMine(Case &bloc) {
    bloc.state = STATE::MARKED;
}