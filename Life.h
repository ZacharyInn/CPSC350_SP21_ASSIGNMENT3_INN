#ifndef LIFE_H
#define LIFE_H
#include <iostream>

using namespace std;

class Life
{
  public:
    Life(); //default constructor
    Life(int row, int col, float populationDen); //overloaded constructor
    ~Life(); //desturctor
    string lineOutput(int lineNum);
    void addLine(int lineNum, string input);
    void createRandomBoard(float popDense);
    void drawBoard();
    void calculateNeighbors();
    void calculateDonutMode();
    void calculateMirrorMode();
    void calculateNextGen(string mode);
    bool endGame();
    bool boardEmpty();
  private:
    bool gameState;
    int m_rows;
    int m_cols;
    float popDense;
    char **boardMap;
    int **currentNeighbors;
    int **previousNeighbors;
};

#endif
