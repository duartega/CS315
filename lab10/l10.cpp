// Author      : Gabriel Duarte
// Class       : CS315 Spring 2018
// Date        : 04/29/2018
// Description : We will be building an AVL tree from a text file that models a book index
// Operations  : Search, Insert, Save output, List Index, etc...

// Include all the libraries
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <iomanip>
#include "hfile.h"

using namespace std;

// Function prototypes
void ReadWords(int argc, char *argv[]);
void buildTree(int argc, char *argv[], int &totalWords, AVLTree<string> &myTree);
void out(int totalWords, double timer, AVLTree<string> &myTree);

int main(int argc, char *argv[])
{

  int totalWords = 0;  // Declare the variable for the total number of words

  AVLTree<string> myTree; // Create a tree

  ReadWords(argc, argv); // Read in the file and to check if the files exist and error check

  double start_time = clock(); // Start a clock timer to see how long it takes to build the list

  buildTree(argc, argv, totalWords, myTree); // Then read in the words
  double finish_time = clock();                           // End the clock

  double timer = (finish_time - start_time) / CLOCKS_PER_SEC; // Calculate the time

  out(totalWords, timer, myTree); // This will ask the user for input as welll as write out information

  return 0;
}

void ReadWords(int argc, char *argv[])
{
  // Exit if no file name
  if (argc < 2)
  {
    cout << "Usage: " << argv[0] << " <file name>\n";
    exit(1);
  }

  ifstream input(argv[1]); // Declare and open an input file

  // Check to see if the file was successfully opened
  if (input.fail())
  {
    cout << "File: " << argv[1] << " not found\n";
    exit(2); // Exit if no file found
  }
}

void buildTree(int argc, char *argv[], int &wordCount, AVLTree<string> &myTree)
{
  ifstream input(argv[1]); // Declare and open an input file
  string newStr;           // Use this to save a word without periods, commas, and spaces
  string line;             // Used to read in the line
  int lineNum = 1;         // To get the line number for each word

  while (getline(input, line))
  {
    stringstream s(line); // Read in char by char
    string potentialWord; // Variable to store the chars

    while (s >> potentialWord)
    {
      for (int i = 0; i < potentialWord.size(); i++) // Checks to see if there are non-aplha-numeric characters
      {
        if (potentialWord[i] == ' ') break;
        else if (potentialWord[i] == '.' & !isalnum(potentialWord[i + 1])) break;
        else if (potentialWord[i] == ',') break;
        else if (potentialWord[i] == '-' & !isalpha(potentialWord[i + 1])) break;
        else if ((potentialWord[i] == ';')) break;
        else if ((potentialWord[i] == '"')) break;
        else if ((potentialWord[i] == ':')) break;
        else if ((potentialWord[i] == '\'')) break;
        else if ((potentialWord[i] == '(' || (potentialWord[i] == ')'))) break;
        else
          newStr += potentialWord[i]; // Adds the chars to make a word without period, commas, spaces, etc
      }
      wordCount++;                    // Increment the total word count after each word has been constructed

      myTree.insert(newStr, lineNum); // Inert the word and the line number
      newStr.clear();                 // Clear the string so we dont add another word to the word that is already in there
    }
    lineNum++; // Increment the line number once the getline sees a new line character
  }

  input.close(); // close the input after we read it all in so that we dont have a memory leak
}

void out(int totalWords, double timer, AVLTree<string> &myTree)
{

  string in;         // Variable to get the user input
  string searchWord; // variable to pass the word they want to search
  cout << "Total number of words:\t\t\t" << totalWords << endl;
  cout << "Total number of distinct words:\t\t";
  myTree.findSize(); // Get the number of distinct words based on the size of the tree since there cannot be any duplicates
  cout << endl;
  cout << "Time taken to build index using BST is: " << setprecision(4) << timer << endl;
  cout << "Height of BST tree is:\t\t\t";
  myTree.findHeight(); // Print out the height of the tree
  cout << "\nNumber of comparisons:\t\t\t";
  myTree.getComparisonsInsert();
  cout << endl;
  in == "5";

while (in != "4")
{    cout << "\n\nOptions: (1) display index, (2) search, (3) save index, (4) quit\n";
    cin >> in;
  if (in == "1")
  {
    cout << "Binary Search Tree Index:\n";
    cout << "-------------------------\n";
    myTree.printTree(); // Print the index
  }
  if (in == "2")
  {
    cout << "Search word? ";
    cin >> searchWord; // Read in the word
    if (myTree.contains(searchWord))
    { // Checks to see if the word is in the tree
      cout << "Line numbers <BST>: ";
      myTree.search(searchWord); // If it is, it will print the line numbers
      cout << "\nNumber of key comparisons for search algorithm:\t\t\t";
      myTree.getComparisonsContains();
    }
    else
    {
      cout << "The word is not in the document\n"; // Else it will say the word is not in the document
      cout << "\nNumber of key comparisons for search algorithm:\t\t\t";
      myTree.getComparisonsContains();
    }
  }
  if (in == "3")
  {
    string outfile; // Variable to get file name
    cout << "Please enter a output file name: ";
    cin >> outfile; // Read in the input and store it

    ofstream output(outfile); // Open the output file

    myTree.printTree(output); // Write the output to the file they specified
  }
    if (in == "4")
    {
      exit(1);
    }
}


}
