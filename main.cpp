#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include "Life.h"
using namespace std;

int main()
{
  ifstream inputStream;
  ofstream outputStream;
  int row, col;
  float pDense;
  string mode;
  cout << "Welcome to The Game of Life. Would you like a random world assignment? (y/n)" << endl;
  string answer;
  getline(cin,answer);
  while (answer != "y" && answer != "n") {
    cout << "Please enter a valid answer." << endl;
    getline(cin,answer);
  }
  if (answer == "y")
  {
    cout << "Enter map height: " << endl;
    while (!(cin >> row))
    {
      cout << "Enter a valid integer: " << endl;
      cin.clear();
      cin.ignore(128, '\n');
    }
    cout << "Enter map width: " << endl;
    while (!(cin >> col))
    {
      cout << "Enter a valid integer: " << endl;
      cin.clear();
      cin.ignore(128, '\n');
    }
    cout << "Enter population density as a float between 0 and 1: " << endl;
    while (!(cin >> pDense))
    {
      cout << "Enter a valid float: ";
      cin.clear();
      cin.ignore(128, '\n');
    }
    if (pDense < 0 || pDense > 1)
    {
      cout << "Enter a valid float: ";
      cin >> pDense;
    }
    Life* life1 = new Life(row, col, pDense);

    string trash;
    getline(cin,trash);
    cout << "What kind of boundary mode do you want to run in? (c/d/m)" << endl;
    getline(cin, mode);
    while (!((mode != "c") || (mode != "d") || (mode != "m")))
    {
      cout << "Enter a valid mode declaration. Either c, d, or m." << endl;
      getline(cin, mode);
    }
    string speed;
    cout << "Enter output style. Paused, Manual, File (p/m/f)" << endl;
    cin >> speed;
    while (!((mode != "p") || (mode != "m") || (mode != "f")))
    {
      cout << "Enter a valid output declaration. (p/m/f)" << endl;
      getline(cin, speed);
    }

    int genCount = 1;
    getline(cin,trash);
    if (speed == "p")
    {
      cout << "Generation: 0" << endl;
      life1->drawBoard();
      cout << endl;
      sleep(1);
      while (!(life1->endGame()) && (genCount < 1000))
      {
        cout << "Generation: " << genCount << endl;
        life1->calculateNextGen(mode);
        life1->drawBoard();
        cout << endl;
        genCount++;
        sleep(1);
      }
    }
    else if (speed == "m")
    {
      cout << "Generation: 0" << endl;
      life1->drawBoard();
      cout << endl;
      string holder;
      getline(cin, holder);
      while (!(life1->endGame()) && (genCount < 1000))
      {
        cout << "Generation: " << genCount << endl;
        life1->calculateNextGen(mode);
        life1->drawBoard();
        cout << endl;
        genCount++;
        getline(cin, holder);
      }
    }
    else if (speed == "f")
    {
      string outputFile;
      cout << "What is the name of the output file you want to use? Make sure the file is a .txt file. (example.txt)" << endl;
      getline(cin, outputFile);
      bool incorrect = true;
      while (incorrect)
      {
        if (outputFile.length() < 5)
        {
          cout << "Enter a valid file name." << endl;
          getline(cin, outputFile);
        }
        else if (outputFile.substr(outputFile.length() - 4) != ".txt")
        {
          cout << "Enter a valid file name." << endl;
          getline(cin, outputFile);
        }
        else
        {
          incorrect = false;
        }
      }
      cout << "Opening " << outputFile << "." << endl;
      outputStream.open(outputFile);
      if (!outputStream.is_open())
      {
        cout << "Could not open " << outputFile << "." << endl;
      }
      outputStream << "Generation: 0" << endl;
      for (int r = 0; r < row; r++)
      {
        outputStream << life1->lineOutput(r);
        outputStream << endl;
      }
      outputStream << endl;
      while (!(life1->endGame()) && (genCount < 1000))
      {
        outputStream << "Generation: " << genCount << endl;
        life1->calculateNextGen(mode);
          for (int r = 0; r < row; r++)
          {
            outputStream << life1->lineOutput(r);
            outputStream << endl;
          }
        outputStream << endl;
        genCount++;

      }
      outputStream.close();
      cout << outputFile << " was closed." << endl;
    }
  }
  //if answer is n
  else
  {
    string inputFile;
    string fileConfig;
    cout << "What is the name of the input file you want to use? Make sure the file is a .txt file. (example.txt)" << endl;
    getline(cin,inputFile);
    bool incorrect = true;
    while (incorrect)
    {
      if (inputFile.length() < 5)
      {
        cout << "Enter a valid file name." << endl;
        getline(cin, inputFile);
      }
      else if (inputFile.substr(inputFile.length() - 4) != ".txt")
      {
        cout << "Enter a valid file name." << endl;
        getline(cin, inputFile);
      }
      else
      {
        incorrect = false;
      }
    }
    cout << "Opening " << inputFile << "." << endl;
    inputStream.open(inputFile);
    if (!inputStream.is_open())
    {
      cout << "Could not open " << inputFile << "." << endl;
    }

    inputStream >> row;
    inputStream >> col;
    Life* life2 = new Life(row,col,0);
    int lineCount = 0;
    while (!inputStream.eof())
    {
      string filler = "";
      getline(inputStream,filler);
      if (lineCount > 0)
      {
        life2->addLine(lineCount - 1,filler);
      }
      lineCount++;
    }
    inputStream.close();
    cout << inputFile << " was closed." << endl;
    cout << "What kind of boundary mode do you want to run in? (c/d/m)" << endl;
    getline(cin, mode);
    while (!((mode != "c") || (mode != "d") || (mode != "m")))
    {
      cout << "Enter a valid mode declaration. Either c, d, or m." << endl;
      getline(cin, mode);
    }
    string speed;
    cout << "Enter output style. Paused, Manual, File (p/m/f)" << endl;
    getline(cin, speed);
    while (!((speed != "p") || (speed != "m") || (speed != "f")))
    {
      cout << "Enter a valid output declaration. (p/m/f)" << endl;
      getline(cin, speed);
    }

    if (speed == "p")
    {
      cout << "Generation: 0" << endl;
      life2->drawBoard();
      cout << endl;
      life2->calculateNextGen(mode);
      sleep(1);
      int genCount = 1;
      while (!(life2->endGame()) && (genCount < 1000))
      {
        cout << "Generation: " << genCount << endl;
        life2->calculateNextGen(mode);
        life2->drawBoard();
        cout << endl;
        genCount++;
        sleep(1);
      }
    }
    else if (speed == "m")
    {
      cout << "Generation: 0" << endl;
      life2->drawBoard();
      life2->calculateNextGen(mode);
      string trash;
      getline(cin,trash);
      int genCount = 1;
      string holder;
      getline(cin,holder);
      while (!(life2->endGame()) && (genCount < 1000))
      {
        cout << "Generation: " << genCount << endl;
        life2->calculateNextGen(mode);
        life2->drawBoard();
        genCount++;
        getline(cin,holder);
      }
    }
    else if (speed == "f")
    {
      string outputFile;
      cout << "What is the name of the file you want to output to? Make sure the file is a .txt file. (example.txt)" << endl;
      getline(cin, outputFile);
      bool incorrect = true;
      while (incorrect)
      {
        if (outputFile.length() < 5)
        {
          cout << "Enter a valid file name." << endl;
          getline(cin, outputFile);
        }
        else if (outputFile.substr(outputFile.length() - 4) != ".txt")
        {
          cout << "Enter a valid file name." << endl;
          getline(cin, outputFile);
        }
        else
        {
          incorrect = false;
        }
      }
      cout << "Opening " << outputFile << ". " << "Press enter to finish." << endl;
      outputStream.open(outputFile);
      if (!outputStream.is_open())
      {
        cout << "Could not open " << outputFile << "." << endl;
        exit(0);
      }
      outputStream << "Generation: 0" << endl;
      for (int r = 0; r < row; r++)
      {
        outputStream << life2->lineOutput(r);
        outputStream << endl;
      }
      outputStream << endl;
      life2->calculateNextGen(mode);
      string trash;
      getline(cin,trash);
      int genCount = 1;
      while (!(life2->endGame()) && (genCount < 1000))
      {
        outputStream << "Generation: " << genCount << endl;
        life2->calculateNextGen(mode);
        for (int r = 0; r < row; r++)
        {
          outputStream << life2->lineOutput(r);
          outputStream << endl;
        }
        outputStream << endl;
        genCount++;
      }
      outputStream.close();
      cout << outputFile << " was closed." << endl;
    }
  }
  return 0;
}
