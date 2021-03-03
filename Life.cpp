#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Life.h"

using namespace std;

Life::Life()
{
  m_rows = 2;
  m_cols = 2;
  boardMap = new char* [2];
  for (int i = 0; i < 2; i++)
  {
    boardMap[i] = new char[2];
  }
  currentNeighbors = new int* [2];
  for (int i = 0; i < 2; i++)
  {
    currentNeighbors[i] = new int[2];
  }
  previousNeighbors = new int* [2];
  for (int i = 0; i < 2; i++)
  {
    previousNeighbors[i] = new int[2];
  }
  gameState = false;
}

Life::Life(int row, int col, float populationDen)
{
  m_rows = row;
  m_cols = col;
  popDense = populationDen;
  boardMap = new char* [row];
  for (int i = 0; i < row; i++)
  {
    boardMap[i] = new char[col];
  }
  currentNeighbors = new int* [row];
  for (int i = 0; i < row; i++)
  {
    currentNeighbors[i] = new int[col];
  }
  previousNeighbors = new int* [row];
  for (int i = 0; i < row; i++)
  {
    previousNeighbors[i] = new int[col];
  }
  for (int r = 0; r < m_rows;r++)
  {
    for (int c = 0; c < m_cols; c++)
    {
      currentNeighbors[r][c] = -1;
      previousNeighbors[r][c] = -1;
    }
  }
  createRandomBoard(popDense);
  gameState = false;
}


string Life::lineOutput(int lineNum)
{
    string result;
    for (int c = 0; c < m_cols; c++)
    {
      result += boardMap[lineNum][c];
    }
    return result;
}

void Life::createRandomBoard(float popDense)
{
  srand(time(NULL)); //initializes the random number generator
  int numm_rows = m_rows;
  int numm_cols = m_cols;
  int numSpaces = numm_rows * numm_cols;
  int numPopDensity = popDense * numSpaces;
  int count = 0;
  int r = 0;
  int c = 0;

  for (int r = 0; r < m_rows;r++)
  {
    for (int c = 0; c < m_cols; c++)
    {
      boardMap[r][c] = '-';
    }
  }
  while (count < numPopDensity)
  {
    r = abs((rand() % numm_rows));
    c = abs((rand() % numm_cols));
    if (boardMap[r][c] != 'X')
    {
      boardMap[r][c] = 'X';
      count++;
    }
  }
}

void Life::drawBoard()
{
  for (int r = 0; r < m_rows; r++)
  {
    for (int c = 0; c < m_cols; c++)
    {
      cout << boardMap[r][c];
    }
    cout << endl;
  }
}

void Life::addLine(int lineNum, string input)
{
  if (lineNum > (m_rows - 1))
  {
    return;
  }
  for (int c = 0; c < m_cols; c++)
  {
    boardMap[lineNum][c] = input.at(0);
    input = input.substr(1);
  }
}
//Calculates Neighbor Values based on Classic Mode
void Life::calculateNeighbors()
{
  for (int r = 0; r < m_rows;r++)
  {
    for (int c = 0; c < m_cols; c++)
    {
      int neighbors = 0;

      //NW corner calculation
      if ((r == 0) && (c == 0))
      {
        if (boardMap[0][1] != '-') {
          neighbors++;
        }
        if (boardMap[1][1] != '-') {
          neighbors++;
        }
        if (boardMap[1][0] != '-') {
          neighbors++;
        }
      }

      //NE corner calculation
      else if ((r == 0) && (c == (m_cols - 1)))
      {
        if (boardMap[0][m_cols - 2] != '-') {
          neighbors++;
        }
        if (boardMap[1][m_cols - 2] != '-') {
          neighbors++;
        }
        if (boardMap[1][m_cols - 1] != '-') {
          neighbors++;
        }
      }

      //SW corner calculation
      else if ((r == (m_rows - 1)) && (c == 0))
      {
        if (boardMap[m_rows - 2][0] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 2][1] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 1][1] != '-') {
          neighbors++;
        }
      }

      //SE corner calculation
      else if ((r == (m_rows - 1)) && (c == m_cols - 1))
      {
        if (boardMap[m_rows - 2][m_cols - 1] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 2][m_cols - 2] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 1][m_cols - 2] != '-') {
          neighbors++;
        }
      }

      //North edge calculation
      else if (r == 0)
      {
        if (boardMap[0][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[0][c + 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[1][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[1][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[1][c + 1] != '-')
        {
          neighbors++;
        }
      }

      //West edge calculation
      else if (c == 0)
      {
        if (boardMap[r - 1][0] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][0] != '-')
        {
          neighbors++;
        }
        if (boardMap[r - 1][1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r][1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][1] != '-')
        {
          neighbors++;
        }
      }

      //South edge calculation
      else if (r == (m_rows - 1))
      {
        if (boardMap[m_rows - 1][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[m_rows - 1][c + 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[m_rows - 2][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[m_rows - 2][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[m_rows - 2][c + 1] != '-')
        {
          neighbors++;
        }
      }

      //East edge calculation
      else if (c == (m_cols - 1))
      {
        if (boardMap[r - 1][m_cols - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][m_cols - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r - 1][m_cols - 2] != '-')
        {
          neighbors++;
        }
        if (boardMap[r][m_cols - 2] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][m_cols - 2] != '-')
        {
          neighbors++;
        }
      }

      //Middle spaces
      else
      {
        if (boardMap[r - 1][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r - 1][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[r - 1][c + 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r][c + 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][c + 1] != '-')
        {
          neighbors++;
        }
      }
      currentNeighbors[r][c] = neighbors;
    }
  }
}

//Calculates based on Donut Mode
void Life::calculateDonutMode()
{
  for (int r = 0; r < m_rows;r++)
  {
    for (int c = 0; c < m_cols; c++)
    {
      int neighbors = 0;

      //NW corner calculation
      if ((r == 0) && (c == 0))
      {
        if (boardMap[0][1] != '-') {
          neighbors++;
        }
        if (boardMap[1][1] != '-') {
          neighbors++;
        }
        if (boardMap[1][0] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 1][0] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 1][1] != '-') {
          neighbors++;
        }
        if (boardMap[0][m_cols - 1] != '-') {
          neighbors++;
        }
        if (boardMap[1][m_cols - 1] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 1][m_cols - 1] != '-') {
          neighbors++;
        }
      }

      //NE corner calculation
      else if ((r == 0) && (c == (m_cols - 1)))
      {
        if (boardMap[0][m_cols - 2] != '-') {
          neighbors++;
        }
        if (boardMap[1][m_cols - 2] != '-') {
          neighbors++;
        }
        if (boardMap[1][m_cols - 1] != '-') {
          neighbors++;
        }
        if (boardMap[0][0] != '-') {
          neighbors++;
        }
        if (boardMap[1][0] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 1][m_cols - 1] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 1][m_cols - 2] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 1][0] != '-') {
          neighbors++;
        }
      }

      //SW corner calculation
      else if ((r == (m_rows - 1)) && (c == 0))
      {
        if (boardMap[m_rows - 2][0] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 2][1] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 1][1] != '-') {
          neighbors++;
        }
        if (boardMap[0][0] != '-') {
          neighbors++;
        }
        if (boardMap[0][1] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 1][m_cols - 1] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 2][m_cols - 1] != '-') {
          neighbors++;
        }
        if (boardMap[0][m_cols - 1] != '-') {
          neighbors++;
        }
      }

      //SE corner calculation
      else if ((r == (m_rows - 1)) && (c == m_rows - 1))
      {
        if (boardMap[m_rows - 2][m_cols - 1] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 2][m_cols - 2] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 1][m_cols - 2] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 1][0] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 2][0] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 1][m_cols - 1] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 2][m_cols - 1] != '-') {
          neighbors++;
        }
        if (boardMap[0][0] != '-') {
          neighbors++;
        }
      }

      //North edge calculation
      else if (r == 0)
      {
        if (boardMap[0][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[0][c + 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[1][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[1][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[1][c + 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[m_rows - 1][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[m_rows - 1][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[m_rows - 1][c + 1] != '-')
        {
          neighbors++;
        }
      }

      //West edge calculation
      else if (c == 0)
      {
        if (boardMap[r - 1][0] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][0] != '-')
        {
          neighbors++;
        }
        if (boardMap[r - 1][1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r][1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r - 1][m_cols - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r][m_cols - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][m_cols - 1] != '-')
        {
          neighbors++;
        }
      }

      //South edge calculation
      else if (r == (m_rows - 1))
      {
        if (boardMap[m_rows - 1][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[m_rows - 1][c + 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[m_rows - 2][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[m_rows - 2][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[m_rows - 2][c + 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[0][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[0][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[0][c + 1] != '-')
        {
          neighbors++;
        }
      }

      //East edge calculation
      else if (c == (m_cols - 1))
      {
        if (boardMap[r - 1][m_cols - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][m_cols - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r - 1][m_cols - 2] != '-')
        {
          neighbors++;
        }
        if (boardMap[r][m_cols - 2] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][m_cols - 2] != '-')
        {
          neighbors++;
        }
        if (boardMap[r - 1][0] != '-')
        {
          neighbors++;
        }
        if (boardMap[r][0] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][0] != '-')
        {
          neighbors++;
        }
      }

      //Middle spaces
      else
      {
        if (boardMap[r - 1][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r - 1][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[r - 1][c + 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r][c + 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][c + 1] != '-')
        {
          neighbors++;
        }
      }
      currentNeighbors[r][c] = neighbors;
    }
  }
}

//Calculates based on Mirror Mode
void Life::calculateMirrorMode()
{
  for (int r = 0; r < m_rows;r++)
  {
    for (int c = 0; c < m_cols; c++)
    {
      int neighbors = 0;

      //NW corner calculation
      if ((r == 0) && (c == 0))
      {
        if (boardMap[0][0] != '-')
        {
          neighbors += 3;
        }
        if (boardMap[0][1] != '-') {
          neighbors += 2;
        }
        if (boardMap[1][1] != '-') {
          neighbors++;
        }
        if (boardMap[1][0] != '-') {
          neighbors += 2;
        }
      }

      //NE corner calculation
      else if ((r == 0) && (c == (m_cols - 1)))
      {
        if (boardMap[0][m_cols - 1])
        {
          neighbors += 3;
        }
        if (boardMap[0][m_cols - 2] != '-') {
          neighbors += 2;
        }
        if (boardMap[1][m_cols - 2] != '-') {
          neighbors++;
        }
        if (boardMap[1][m_cols - 1] != '-') {
          neighbors += 2;
        }
      }

      //SW corner calculation
      else if ((r == (m_rows - 1)) && (c == 0))
      {
        if (boardMap[m_rows - 1][0] != '-')
        {
          neighbors += 3;
        }
        if (boardMap[m_rows - 2][0] != '-') {
          neighbors += 2;
        }
        if (boardMap[m_rows - 2][1] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 1][1] != '-') {
          neighbors += 2;
        }
      }

      //SE corner calculation
      else if ((r == (m_rows - 1)) && (c == m_cols - 1))
      {
        if (boardMap[m_rows - 1][m_cols - 2] != '-')
        {
          neighbors += 3;
        }
        if (boardMap[m_rows - 2][m_cols - 1] != '-') {
          neighbors += 2;
        }
        if (boardMap[m_rows - 2][m_cols - 2] != '-') {
          neighbors++;
        }
        if (boardMap[m_rows - 1][m_cols - 2] != '-') {
          neighbors += 2;
        }
      }

      //North edge calculation
      else if (r == 0)
      {
        if (boardMap[r][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[0][c - 1] != '-')
        {
          neighbors += 2;
        }
        if (boardMap[0][c + 1] != '-')
        {
          neighbors += 2;
        }
        if (boardMap[1][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[1][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[1][c + 1] != '-')
        {
          neighbors++;
        }
      }

      //West edge calculation
      else if (c == 0)
      {
        if (boardMap[r][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[r - 1][0] != '-')
        {
          neighbors += 2;
        }
        if (boardMap[r + 1][0] != '-')
        {
          neighbors += 2;
        }
        if (boardMap[r - 1][1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r][1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][1] != '-')
        {
          neighbors++;
        }
      }

      //South edge calculation
      else if (r == (m_rows - 1))
      {
        if (boardMap[r][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[m_rows - 1][c - 1] != '-')
        {
          neighbors += 2;
        }
        if (boardMap[m_rows - 1][c + 1] != '-')
        {
          neighbors += 2;
        }
        if (boardMap[m_rows - 2][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[m_rows - 2][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[m_rows - 2][c + 1] != '-')
        {
          neighbors++;
        }
      }

      //East edge calculation
      else if (c == (m_cols - 1))
      {
        if (boardMap[r][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[r - 1][m_cols - 1] != '-')
        {
          neighbors += 2;
        }
        if (boardMap[r + 1][m_cols - 1] != '-')
        {
          neighbors += 2;
        }
        if (boardMap[r - 1][m_cols - 2] != '-')
        {
          neighbors++;
        }
        if (boardMap[r][m_cols - 2] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][m_cols - 2] != '-')
        {
          neighbors++;
        }
      }

      //Middle spaces
      else
      {
        if (boardMap[r - 1][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r - 1][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[r - 1][c + 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r][c + 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][c - 1] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][c] != '-')
        {
          neighbors++;
        }
        if (boardMap[r + 1][c + 1] != '-')
        {
          neighbors++;
        }
      }
      currentNeighbors[r][c] = neighbors;
    }
  }
}

void Life::calculateNextGen(string mode)
{
  int** totalNeighbors;
  totalNeighbors = new int* [m_rows];
  for (int i = 0; i < m_rows; i++)
  {
    totalNeighbors[i] = new int[m_cols];
  }
  //Fill in board and average numbers
  for (int r = 0; r < m_rows; r++)
  {
    for (int c = 0; c < m_cols; c++)
    {
      totalNeighbors[r][c] = currentNeighbors[r][c];
    }
  }
  if (mode == "c")
  {
    calculateNeighbors();
  }
  else if (mode == "d")
  {
    calculateDonutMode();
  }
  else
  {
    calculateMirrorMode();
  }
  bool changed = false;
  for (int r = 0; r < m_rows; r++)
  {
    for (int c = 0; c < m_cols; c++)
    {
      float average;
      if (totalNeighbors[r][c] == -1)
      {
        totalNeighbors[r][c] = currentNeighbors[r][c];
        average = totalNeighbors[r][c];
      }
      else if (previousNeighbors[0][0] == -1)
      {
        totalNeighbors[r][c] += currentNeighbors[r][c];
        average = totalNeighbors[r][c] / 2;
      }
      else {
        totalNeighbors[r][c] += currentNeighbors[r][c];
        totalNeighbors[r][c] += previousNeighbors[r][c];
        average = totalNeighbors[r][c] / 3;
      }
      if (average < 1.5)
      {
        if (boardMap[r][c] != '-')
        {
          changed = true;
        }
        boardMap[r][c] = '-';
      }
      //continue checking averages
      else if (average >= 2.51 && average <= 3.5)
      {
        if (boardMap[r][c] != 'X')
        {
          changed = true;
        }
        boardMap[r][c] = 'X';
      }
      else if (average >= 3.51)
      {
        if (boardMap[r][c] != '-')
        {
          changed = true;
        }
        boardMap[r][c] = '-';
      }
    }
  }
  gameState = true;
  for (int r = 0; r < m_rows;r++)
  {
    for (int c = 0; c < m_cols; c++)
    {
      if (currentNeighbors[r][c] != previousNeighbors[r][c])
      {
        gameState = false;
      }
    }
  }
  if (changed)
  {
    gameState = false;
  }
  if (boardEmpty())
  {
    gameState = true;
  }

  for (int r = 0; r < m_rows; r++)
  {
    for (int c = 0; c < m_cols; c++)
    {
      previousNeighbors[r][c] = currentNeighbors[r][c];
    }
  }
}

bool Life::endGame()
{
  if (gameState)
  {
    cout << "Press enter to end the program." << endl;
    string holder;
    getline(cin,holder);
    return gameState;
  }
  else
  {
    return gameState;
  }
}

bool Life::boardEmpty()
{
  for (int r = 0; r < m_rows;r++)
  {
    for (int c = 0; c < m_cols; c++)
    {
      if (boardMap[r][c] != '-')
      {
        return false;
      }
    }
  }
  return true;
}
