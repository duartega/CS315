// Author      : Gabriel Duarte
// Class       : CS315 Spring 2018
// Date        : 03/05/2018
// Description : We will be building a binary search tree from a text file that models a book index
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
void ReadWords (int argc, char * argv []);
void buildTree (int argc, char * argv [], int & totalWords, int & uniqueWords, BinarySearchTree<string> & myTree);
void out (int totalWords, int uniqueWords, double timer, BinarySearchTree<string> & myTree);

int main(int argc, char * argv [])
{

  int uniqueWords = 0; // Variable for the number of unique words
  int totalWords = 0; // Declare the variable for the total number of words

  BinarySearchTree<string> myTree; // Create a tree

  ReadWords(argc, argv); // Read in the file and to check if the files exist and error check

  double start_time = clock(); // Start a clock timer to see how long it takes to build the list

  buildTree(argc, argv, totalWords, uniqueWords, myTree); // Then read in the words
  double finish_time = clock(); // End the clock

  double timer = (finish_time - start_time) / CLOCKS_PER_SEC; // Calculate the time

  out(totalWords, uniqueWords, timer, myTree); // This will ask the user for input as welll as write out information

  return 0;
}

void ReadWords (int argc, char * argv [])
{
  // Exit if no file name
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <file name>\n";
    exit(1);
  }

  ifstream input(argv[1]); // Declare and open an input file

  // Check to see if the file was successfully opened
  if (input.fail()) {
    cout << "File: " << argv[1] << " not found\n";
    exit(2); // Exit if no file found
  }
}

void buildTree (int argc, char * argv [], int & wordCount, int & uniqueCount, BinarySearchTree<string> & myTree)
{
  ifstream input(argv[1]); // Declare and open an input file
  string newStr; // Use this to save a word without periods, commas, and spaces
  string line; // Used to read in the line
  int lineNum = 1; // To get the line number for each word

  while (getline(input, line))
    {
      stringstream s(line); // Read in char by char
      string potentialWord; // Variable to store the chars

      while (s >> potentialWord)
	{
	  for (int i = 0; i < potentialWord.size(); i++) // Checks to see if there are non-aplha-numeric characters
	    {
	      if (potentialWord[i] == ' ' || potentialWord[i] == '.' || potentialWord[i] == ',')
		break;
	      else
		newStr += potentialWord[i]; // Adds the chars to make a word without period, commas, spaces, etc
	    }
	  wordCount ++; // Increment the total word count after each word has been constructed
	  if (!myTree.contains(newStr)) // Checks to see if the BST does not contain the word
            uniqueCount++; // Increment the unique word counter if the word is not in the tree
	  myTree.insert(newStr, lineNum); // Inert the word and the line number
	  newStr.clear(); // Clear the string so we dont add another word to the word that is already in there
	}
      lineNum++; // Increment the line number once the getline sees a new line character
    }

  input.close(); // close the input after we read it all in so that we dont have a memory leak
}

void out (int totalWords, int uniqueWords, double timer, BinarySearchTree<string> & myTree) {

  string in; // Variable to get the user input
  string searchWord; // variable to pass the word they want to search
  cout << "Total number of words:\t\t\t" << totalWords << endl;
  cout << "Total number of distinct words:\t\t" << uniqueWords << endl;
  cout << "Time taken to build index using BST is: " << timer << endl;
  cout << "Height of BST tree is:\t\t\t";
  myTree.findHeight(); // Print out the height of the tree
  cout << endl;
  cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
  cin >> in; // Read in the input 1, 2, 3, or 4

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
      if (myTree.contains(searchWord)) { // Checks to see if the word is in the tree
	cout << "Line numbers <BST>: ";
	myTree.search(searchWord); // If it is, it will print the line numbers
      }
      else
        {
	  cout <<"The word is not in the document\n"; // Else it will say the word is not in the document
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

  while (in != "4")
    {
      cout << "\nOptions: (1) display index, (2) search, (3) save index, (4) quit\n";
      cin >> in;

      if (in == "1")
	{
	  cout << "Binary Search Tree Index:\n";
	  cout << "-------------------------\n";
	  myTree.printTree();
	}
      if (in == "2")
	{
	  cout << "Search word? ";
	  cin >> searchWord;
	  if (myTree.contains(searchWord)) {
            cout << "Line numbers <BST>: ";
            myTree.search(searchWord);
	  }
	  else
	    {
	      cout <<"The word is not in the document\n";
	    }
	}
      if (in == "3")
	{
	  string outfile;
	  cout << "Please enter a output file name: ";
	  cin >> outfile;

	  // Open the output file
	  ofstream output(outfile);

	  myTree.printTree(output);

	}
      if (in == "4")
	{
	  exit(1);
	}
    }
}
