#include <iostream>
#include "grid.h"


bool validCoords(Grid &grid, unsigned x, unsigned y) {
    return x < grid.pb.lines && y < grid.pb.columns;
}


void setMines(Grid &grid) {
    for (unsigned i = 0; i < grid.pb.mines; i++) {
        unsigned mP;
        std::cin >> mP;
        grid.pb.minePos[i] = mP;
    }
}


void generateMS(Grid &grid) {
    grid.ms = new Case *[grid.pb.lines];
    for (unsigned x = 0; x < grid.pb.lines; x++) {
        grid.ms[x] = new Case[grid.pb.columns];
        for (unsigned y = 0; y < grid.pb.columns; y++) {
            grid.ms[x][y].content = 0;
            grid.ms[x][y].state = STATE::HIDDEN;
        }
    }
}

void placeMines(Grid &grid) {
    for (unsigned m = 0; m < grid.pb.mines; m++) {
        unsigned x, y;
        getCoords(grid.pb, grid.pb.minePos[m], x, y);
        grid.ms[x][y].content = MINE;
    }
}

void addMineAdj(Grid &grid, unsigned &x, unsigned &y) {
    enum {
        COUNT_TEST = 8
    };
    unsigned int coords[COUNT_TEST][2] =
            {
                    {x,     y + 1},
                    {x,     y - 1},
                    {x + 1, y},
                    {x + 1, y + 1},
                    {x + 1, y - 1},
                    {x - 1, y},
                    {x - 1, y + 1},
                    {x - 1, y - 1},
            };

    for (unsigned int *coord: coords) {
        if (validCoords(grid, coord[0], coord[1])) {
            if (grid.ms[coord[0]][coord[1]].content < 8) grid.ms[coord[0]][coord[1]].content += 1;
        }
    }
}

void fillMS(Grid &grid) {
    for (unsigned x = 0; x < grid.pb.lines; x++) {
        for (unsigned y = 0; y < grid.pb.columns; y++) {
            if (grid.ms[x][y].content == MINE) {
                addMineAdj(grid, x, y);
            }
        }
    }
}

void unmaskMine(Grid &grid, unsigned x, unsigned y) {
    enum {
        COUNT_TEST = 8
    };
    unsigned int coords[COUNT_TEST][2] =
            {
                    {x + 0, y + 1},
                    {x + 0, y - 1},
                    {x + 1, y + 0},
                    {x + 1, y + 1},
                    {x + 1, y - 1},
                    {x - 1, y + 0},
                    {x - 1, y + 1},
                    {x - 1, y - 1},
            };

    if (!validCoords(grid, x, y)) return;
    Case &c = grid.ms[x][y];

    if (c.state == STATE::VISIBLE) return;
    c.state = STATE::VISIBLE;

    if (c.content == MINE) {
        for (unsigned m = 0; grid.pb.mines > m; m++) {
            unsigned mx, my;
            getCoords(grid.pb, grid.pb.minePos[m], mx, my);
            grid.ms[mx][my].state = STATE::VISIBLE;
        }
        return;
    }

    if (c.content != 0) return;

    for (unsigned t = 0; t < COUNT_TEST; t++) {
        unmaskMine(grid, coords[t][0], coords[t][1]);
    }
}

void executeMoves(Grid &grid) {
    unsigned moveCount;
    std::cin >> moveCount;

    for (unsigned m = 0; m < moveCount; m++) {
        char action;
        unsigned position, x, y;
        std::cin >> action >> position;
        getCoords(grid.pb, position, x, y);
        if (action == 'D') {
            unmaskMine(grid, x, y);
        }

        if (action == 'M') {
            markMine(grid.ms[x][y]);
            if(grid.ms[x][y].content == MINE) {
                unsigned xm, ym;
                getCoords(grid.pb, grid.pb.minePos[0], xm, ym);
                unmaskMine(grid, xm, ym);
            }
        }
    }
}

bool gameWon(Grid &grid) {
    for (unsigned int x = 0; x < grid.pb.lines; x++) {
        for (unsigned y = 0; y < grid.pb.columns; y++) {
            Case &c = grid.ms[x][y];
            if (c.content == MINE && c.state != STATE::MARKED) return false;
        }
    }
    return true;
}

bool gameLost(Grid &grid) {
    for (unsigned int x = 0; x < grid.pb.lines; x++) {
        for (unsigned y = 0; y < grid.pb.columns; y++) {
            Case &c = grid.ms[x][y];

            if ((c.content == MINE && c.state == STATE::VISIBLE) ||
                (c.content != MINE && c.state == STATE::MARKED))
                return true;
        }
    }
    return false;
}

void showResult(Grid &grid, unsigned cmd) {
    if (cmd == 4) std::cout << "game " << (gameLost(grid) ? "lost" : "not lost");
    else std::cout << "game " << (gameWon(grid) ? "won" : "not won");
}

void getActionToPlay(Grid &grid) {
    unsigned underscoreCount = grid.pb.columns * 3,
            lineCount = (grid.pb.columns * 4) + 1;

    for (unsigned x = 0; x < grid.pb.lines; x++) {
        char useless, line[lineCount + 1];
        for (unsigned _ = 0; _ < underscoreCount; _++) std::cin >> useless;
        std::cin.read(line, sizeof(line));
        //If we start with 2 and get all 4 values, it's ok !
        for (unsigned c = 3; c < lineCount + 1; c += 4 /*c++ :p*/) {
            unsigned getPos = grid.pb.columns * x + (c / 4);
            if(line[c] == '.') {
                std::cout << 'D' << getPos;
                return;
            }
        }
    }
}

void showGrid(Grid &grid) {

    std::cout << grid.pb.lines << " " << grid.pb.columns << '\n';
    for (unsigned int x = 0; x < grid.pb.lines; x++) {
        for (unsigned line = 0; line < grid.pb.columns; line++) {
            std::cout << " ___";
        }
        std::cout << "\n";
        for (unsigned int y = 0; y < grid.pb.columns; y++) {

            if (y == 0) std::cout << "| ";
            else std::cout << ' ';

            std::cout << showElement(grid.ms[x][y])
                      << " |";
        }
        std::cout << '\n';
    }
    for (unsigned line = 0; line < grid.pb.columns; line++) {
        std::cout << " ___";
    }
    std::cout << '\n';
}

void deleteGrid(Grid &grid) {
    delete[] grid.pb.minePos;
    for (unsigned i = 0; i < grid.pb.lines; i++) {
        delete[] grid.ms[i];
    }
    delete[] grid.ms;
}

void createGrid() {
    Grid grid{};
    setProblem(grid.pb);

    setMines(grid);

    generateMS(grid);

    placeMines(grid);

    fillMS(grid);

    executeMoves(grid);

    showGrid(grid);

    deleteGrid(grid);
}

void getResult(unsigned cmd) {
    Grid grid{};
    setProblem(grid.pb);

    setMines(grid);

    generateMS(grid);

    placeMines(grid);

    fillMS(grid);

    executeMoves(grid);

    showResult(grid, cmd);

    deleteGrid(grid);
}

void readGrid() {
    Grid grid{};
    setBasicProblem(grid.pb);

    getActionToPlay(grid);
}