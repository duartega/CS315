// Author       : Gabriel Duarte
// Date         : 04/24/2018
// Class        : Cs315
// Assignment   : Lab09

#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include <cstdlib>
#include <iomanip>
#include "SeparateChaining.cpp"
#include "QuadraticProbing.h"


using namespace std;

void LoadFile(string in, bool board[49]);                                                                                                                                                       // This will loaad the file and input the pegs
bool solve(bool board[49], vector<vector<int>> &moves, vector<vector<int>> &seq);                                                                                                               // Will find the winning sequence without hashing
void InsertPossibleMoves(vector<vector<int>> &moves);                                                                                                                                           // Contains the list of possible moves
bool solved(bool board[49], int count);                                                                                                                                                         // Will check if the board is solved by checking if there is only one peg left
void printOut(bool board[49], vector<vector<int>> &moves, vector<vector<int>> &seq, HashTable<long long> &H1, HashTableQ<long long> &H2, HashTableQ<long long> &H3, HashTableQ<long long> &H4); // Prints data
vector<vector<int>> nextMoves(const vector<vector<int>> &moves, const bool board[49]);                                                                                                          // Checks all the next moves
void makeNextMove(bool board[49], bool newBoard[49], const vector<int> &move);                                                                                                                  // Will make the next move
bool hsolve(bool board[49], vector<vector<int>> &moves, vector<vector<int>> &seq, HashTable<long long> &H, int count, int number);                                   // Will find the winning sequence using hashing
bool csolve(bool board[49], vector<vector<int>> &moves, vector<vector<int>> &seq, HashTableQ<long long> &Q, int count, int number);
int main()
{
  bool board[49];               // Create a new board
  vector<vector<int>> allMoves; // Create vector for possible moves
  vector<vector<int>> seq;      // Create vector for the winning sequence
  HashTable<long long> SepChain;
  HashTableQ<long long> LinHash;
  HashTableQ<long long> QuadHash;
  HashTableQ<long long> DoubleHash;

  string in; // Variable to store file name

  InsertPossibleMoves(allMoves); // Inserts all the possible moves that were given to us

  for (int peg = 0; peg < 49; ++peg)
    board[peg] = false; // Set all positions to false so there isn't garbage data
  cout << endl
       << "Welcome to Peg Solitare!" << endl;
  cout << "Please enter a file name: ";
  cin >> in;                                                               // Read in the file name
  LoadFile(in, board);                                                     // Send the input to see if it is a valid file
  printOut(board, allMoves, seq, SepChain, LinHash, QuadHash, DoubleHash); // Prints data

  return 0;
}
void printOut(bool board[49], vector<vector<int>> &moves, vector<vector<int>> &seq, HashTable<long long> &SepChain, HashTableQ<long long> &LinHash, HashTableQ<long long> &QuadHash, HashTableQ<long long> &DoubleHash)
{
  char in; // Create variable to see which option they want
  cout << "Data loaded!" << endl;

  while (in != '5') // While the user does not want to quit
  {
    cout << endl
         << "(1) To solve" << endl
         << "(2) To exit" << endl
         << "Which option would you like to select? ";
    cin >> in; // Read in their selection
    cout << endl;
    int count = 1; // Set count to only print certain things

    if (in == '1') // Non-Hashing option
    {
      //--------Seperate chaining ----------------------------------------------------------------------------
      float start_time = clock();    // Start a clock timer to see how long it takes to find a solution
      hsolve(board, moves, seq, SepChain, count, 2);                // If there is not solution, then print out no solution
      float finish_time = clock();                               // End the clock
      float timer = (finish_time - start_time) / CLOCKS_PER_SEC; // Calculate the time
      cout << endl
           << endl
           << "Time to solve with Seperate Chaining: " << setprecision(5) << fixed << timer << endl;

      //--------Linear Hashing------------------------------------------------------------------------------

      start_time = clock();                                   // Start a clock timer to see how long it takes to find a solution
      csolve(board, moves, seq, LinHash, count, 1); // If there is not solution, then print out no solution
      finish_time = clock();                                  // End the clock
      timer = (finish_time - start_time) / CLOCKS_PER_SEC;    // Calculate the time
      cout << "Time to solve with Linear Hashing: " << setprecision(5) << timer << endl;

      //--------Quadratic Hashing---------------------------------------------------------------------------------

      start_time = clock();                                    // Start a clock timer to see how long it takes to find a solution
      csolve(board, moves, seq, QuadHash, count, 3); // If there is not solution, then print out no solution
      finish_time = clock();                                   // End the clock
      timer = (finish_time - start_time) / CLOCKS_PER_SEC;     // Calculate the time
      cout << "Time to solve with Quadratic Hashing: " << setprecision(5) << timer << endl;

      //--------Double Hashing---------------------------------------------------------------------------------

      start_time = clock();                                      // Start a clock timer to see how long it takes to find a solution
      csolve(board, moves, seq, DoubleHash, count, 2); // If there is not solution, then print out no solution
      finish_time = clock();                                     // End the clock
      timer = (finish_time - start_time) / CLOCKS_PER_SEC;       // Calculate the time
      cout << "Time to solve with Double Hashing: " << setprecision(5) << timer << endl << endl;

    }
    if (in == '2') // Linear Hashing option
      exit(1);
  }
}

void LoadFile(string in, bool board[49])
{

  ifstream input(in.c_str()); // Declare and open an input file

  // Check to see if the file was successfully opened
  if (input.fail())
  {
    cout << "File: " << in << " not found\n";
    exit(2); // Exit if no file found
  }

  int pegs;
  while (input >> pegs) // Read in the pegs from the specified file
    board[pegs] = true;

  input.close(); // close the input after we read it all in so that we don't have a memory leak
}

bool solve(bool board[49], vector<vector<int>> &moves, vector<vector<int>> &seq)
{
  int count = 0;

  if (solved(board, count)) // Check to see if the board is solved
    return true;

  vector<vector<int>> currMoves = nextMoves(moves, board); // Set all the possible moves

  for (int move = 0; move < currMoves.size(); move++) // Check each move in the possible moves list
  {
    bool newBoard[49]; // Create a new board so we have updates

    makeNextMove(board, newBoard, currMoves[move]); // Make the next move

    if (solve(newBoard, moves, seq)) // If we can move then push back that move
    {
      seq.push_back(currMoves[move]);
      cout << '(';
      for (int j = 0; j < 2; j++) // Print out moves that we make for the winning solution
      {
        cout << currMoves[move][j] << ' ';
      }
      cout << currMoves[move][2] << ") ";

      return true; // Return that the move was successfull
    }
  }

  return false; // The move was not successfull or not a solution
}

bool solved(bool board[49], int count) // Checks to see if the game is won by only having one peg left
{
  int pegs = 0;
  for (int i = 0; i < 49; ++i)
  {
    if (board[i] == 1)
    {
      pegs++;
    }
  }
  if (pegs == 1) // Shows the correct output based on which option was selected
  {
    if (count == 0)
      cout << "Winning Sequence without hashing: " << endl;
    if (count == 1)
    cout << endl;
      //cout << "Hashtable Winning Sequence: " << endl;
    return true; // There was only one peg
  }
  else
    return false; // There was not only one peg, there was more so return saying that the board was not solved
}

vector<vector<int>> nextMoves(const vector<vector<int>> &moves, const bool board[49]) // Will make the list of next moves
{
  vector<vector<int>> currentMoves;      // Vector for possible moves
  for (int i = 0; i < moves.size(); i++) // Check which moves are possible and pushes back
  {
    if (board[moves[i][0]] && board[moves[i][1]] && !board[moves[i][2]])
      currentMoves.push_back(moves[i]);
  }
  return currentMoves; // Return the possible moves vector
}

void makeNextMove(bool board[49], bool newBoard[49], const vector<int> &move)
{
  for (int i = 0; i < 49; ++i)
    newBoard[i] = board[i]; // Copies over the last board to the new board

  newBoard[move[0]] = false;
  newBoard[move[1]] = false;
  newBoard[move[2]] = true;
}

bool hsolve(bool board[49], vector<vector<int>> &moves, vector<vector<int>> &seq, HashTable<long long> &H, int count, int number)
{
    vector<vector<int> > probes;
    probes.clear();
    probes.push_back(vector<int> {1});

    if (solved(board, count)) // Checks to see if the board was solved
      return true;

    vector<vector<int>> currMoves = nextMoves(moves, board); // Set all possible moves

    for (int move = 0; move < currMoves.size(); move++) // Check each move in the possible moves list
    {
      bool newBoard[49];         // Create a new board so we have updates
      long long int boardId = 0; // Make into 64 bit

      makeNextMove(board, newBoard, currMoves[move]); // Make the next move

      for (int j = 0; j < 49; j++)
        if (newBoard[j])
          boardId |= 1LL << j; //boardId+pow(2,j);

      if (!H.contains(boardId))
      {
        if (hsolve(newBoard, moves, seq, H, count, number)) // If we can move then push back that move
        {
          seq.push_back(currMoves[move]);
          if (count == 1)
          {
            cout << '(';
            for (int j = 0; j < 2; j++) // Print out moves that we make for the winning solution
            {
              cout << currMoves[move][j] << ' ';
            }
            cout << currMoves[move][2] << ") ";
          }
          return true; // Return that the move was successfull
        }
        else
        {
          H.insert(boardId, probes);
        }
      }
    }
   // for (int i = 0; i != probes.size(); i++)
   //   for (int j = 0; j < probes[i].size(); j++)
   //     cout << probes[j][i] << ' ';
    return false;
}

bool csolve(bool board[49], vector<vector<int>> &moves, vector<vector<int>> &seq, HashTableQ<long long> &Q, int count, int number)
{
    if (solved(board, count))
      return true;

    vector<vector<int>> currMoves = nextMoves(moves, board);

    for (int move = 0; move < currMoves.size(); move++)
    {
      bool newBoard[49];
      long long int boardId = 0;

      makeNextMove(board, newBoard, currMoves[move]);

      for (int j = 0; j < 49; j++)
        if (newBoard[j])
          boardId |= 1LL << j; //boardId+pow(2,j);

      if (!Q.contains(boardId, number))
      {
        if (csolve(newBoard, moves, seq, Q, count, number))
        {
          seq.push_back(currMoves[move]);
         
          return true;
        }
        else
        {
          Q.insertQ(boardId, number);
        }
      }
    }
    return false;
}

void InsertPossibleMoves(vector<vector<int>> &moves)
{
  // List of all possible moves given by Ravi and allowed to be HardCoded per Piazza Post
  moves.push_back(vector<int>{14, 21, 28});
  moves.push_back(vector<int>{15, 22, 29});
  moves.push_back(vector<int>{19, 26, 33});
  moves.push_back(vector<int>{20, 27, 34});
  moves.push_back(vector<int>{2, 9, 16});
  moves.push_back(vector<int>{9, 16, 23});
  moves.push_back(vector<int>{16, 23, 30});
  moves.push_back(vector<int>{23, 30, 37});
  moves.push_back(vector<int>{30, 37, 44});
  moves.push_back(vector<int>{3, 10, 17});
  moves.push_back(vector<int>{10, 17, 24});
  moves.push_back(vector<int>{17, 24, 31});
  moves.push_back(vector<int>{24, 31, 38});
  moves.push_back(vector<int>{31, 38, 45});
  moves.push_back(vector<int>{4, 11, 18});
  moves.push_back(vector<int>{11, 18, 25});
  moves.push_back(vector<int>{18, 25, 32});
  moves.push_back(vector<int>{25, 32, 39});
  moves.push_back(vector<int>{32, 39, 46});
  moves.push_back(vector<int>{2, 3, 4});
  moves.push_back(vector<int>{9, 10, 11});
  moves.push_back(vector<int>{37, 38, 39});
  moves.push_back(vector<int>{44, 45, 46});
  moves.push_back(vector<int>{14, 15, 16});
  moves.push_back(vector<int>{15, 16, 17});
  moves.push_back(vector<int>{16, 17, 18});
  moves.push_back(vector<int>{17, 18, 19});
  moves.push_back(vector<int>{18, 19, 20});
  moves.push_back(vector<int>{21, 22, 23});
  moves.push_back(vector<int>{22, 23, 24});
  moves.push_back(vector<int>{23, 24, 25});
  moves.push_back(vector<int>{24, 25, 26});
  moves.push_back(vector<int>{25, 26, 27});
  moves.push_back(vector<int>{28, 29, 30});
  moves.push_back(vector<int>{29, 30, 31});
  moves.push_back(vector<int>{30, 31, 32});
  moves.push_back(vector<int>{31, 32, 33});
  moves.push_back(vector<int>{32, 33, 34});
  moves.push_back(vector<int>{28, 21, 14});
  moves.push_back(vector<int>{29, 22, 15});
  moves.push_back(vector<int>{33, 26, 19});
  moves.push_back(vector<int>{34, 27, 20});
  moves.push_back(vector<int>{16, 9, 2});
  moves.push_back(vector<int>{23, 16, 9});
  moves.push_back(vector<int>{30, 23, 16});
  moves.push_back(vector<int>{37, 30, 23});
  moves.push_back(vector<int>{44, 37, 30});
  moves.push_back(vector<int>{17, 10, 3});
  moves.push_back(vector<int>{24, 17, 10});
  moves.push_back(vector<int>{31, 24, 17});
  moves.push_back(vector<int>{38, 31, 24});
  moves.push_back(vector<int>{45, 38, 31});
  moves.push_back(vector<int>{18, 11, 4});
  moves.push_back(vector<int>{25, 18, 11});
  moves.push_back(vector<int>{32, 25, 18});
  moves.push_back(vector<int>{39, 32, 25});
  moves.push_back(vector<int>{46, 39, 32});
  moves.push_back(vector<int>{4, 3, 2});
  moves.push_back(vector<int>{11, 10, 9});
  moves.push_back(vector<int>{39, 38, 37});
  moves.push_back(vector<int>{46, 45, 44});
  moves.push_back(vector<int>{16, 15, 14});
  moves.push_back(vector<int>{17, 16, 15});
  moves.push_back(vector<int>{18, 17, 16});
  moves.push_back(vector<int>{19, 18, 17});
  moves.push_back(vector<int>{20, 19, 18});
  moves.push_back(vector<int>{23, 22, 21});
  moves.push_back(vector<int>{24, 23, 22});
  moves.push_back(vector<int>{25, 24, 23});
  moves.push_back(vector<int>{26, 25, 24});
  moves.push_back(vector<int>{27, 26, 25});
  moves.push_back(vector<int>{30, 29, 28});
  moves.push_back(vector<int>{31, 30, 29});
  moves.push_back(vector<int>{32, 31, 30});
  moves.push_back(vector<int>{33, 32, 31});
  moves.push_back(vector<int>{34, 33, 32});
}
