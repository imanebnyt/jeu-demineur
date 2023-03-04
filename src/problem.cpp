#include <iostream>
#include "problem.h"

void getCoords(Problem &pb, unsigned pos, unsigned &x, unsigned &y) {
    x = pos / pb.columns;
    y = pos % pb.columns;
}

void setProblem(Problem &pb) {
    unsigned lines, columns, mines;
    std::cin >> lines >> columns >> mines;
    pb.lines = lines;
    pb.columns = columns;
    pb.mines = mines;
    pb.minePos = new unsigned[pb.mines];
}

void setBasicProblem(Problem &pb) {
    unsigned lines, columns, mines;
    std::cin >> lines >> columns;
    pb.lines = lines;
    pb.columns = columns;
}

void generateMines(Problem &pb) {
    unsigned limit = pb.lines * pb.columns - 1;
    for (unsigned i = 0; i < pb.mines; i++) {
        unsigned minePos = rand() % limit;
        pb.minePos[i] = minePos;
    }
}

void printProblem(Problem &pb) {
    std::cout << pb.lines << " "
              << pb.columns << " "
              << pb.mines << " ";
    for (unsigned i = 0; i < pb.mines; i++) {
        std::cout << pb.minePos[i] << " ";
    }
    std::cout << '\n';
}

void deleteProblem(Problem &pb) {
    delete[] pb.minePos;
}

void createProblem() {
    Problem pb{};
    setProblem(pb);

    generateMines(pb);

    printProblem(pb);

    deleteProblem(pb);
}