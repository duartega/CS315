// Author      : Gabriel Duarte
// Class       : CS315 Spring 2018
// Date        : 04/01/2018
// Description : We will be building a tree that implements size and height with each node

// Include all the libraries
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <time.h>
#include <iomanip>
#include "hfile.h"

using namespace std;

// Function prototypes
void UserInput(vector<int> A, BinarySearchTree<int> &myTree);
bool check(vector<int> &B);
bool kor(vector<int> &B, int num, BinarySearchTree<int> &myTree, int count);

int main()
{

  vector<int> A;

  BinarySearchTree<int> myTree; // Create a tree

  int num;
  vector<int> B;
  vector<int> C;

  B.clear();
  C.clear();

  cout << "Please enter an integer n: ";
  cin >> num;

  for (int i = 0; i < num; i++)
    A.push_back(i);
  random_shuffle(A.begin(), A.end());

  for (auto i : A)
  {
    myTree.insert(i);
  }

  cout << "\n\nHeight of tree: ";
  myTree.findHeight();
  cout << endl;

  cout << "Size of tree: ";
  myTree.findSize(); // Print out the height of the tree
  cout << endl;

  cout << "Log base 2 of " << num << ": " << log2(num) << endl;

  // This will insert the keys into B
  myTree.Inorder(B);
  if (check(B))
    cout << "Order Check - successfull\n";
  else
    cout << "Order Check - unsuccessfull\n";

  if (kor(B, num, myTree, 2))
    cout << "Key of rank successfull\n";
  else
    cout << "Key of rank unsuccessfull\n";

  if (B[myTree.RankOfKey(A[num / 2])] == myTree.RankOfKey(A[num / 2]))
    cout << "Rank of Key Successfull\n";
  else
    cout << "Rank of key Unsuccessfull\n";

  sort(A.begin(), A.end());

  for (int i = A.size() / 2; i < A.size(); i++)
    myTree.remove(A[i]);

  cout << "\n\nHeight of tree: ";
  myTree.findHeight();
  cout << endl;

  cout << "Size of tree: ";
  myTree.findSize(); // Print out the height of the tree
  cout << endl;

  cout << "Log base 2 of " << num << ": " << log2(num) << endl;

  myTree.printC(C);
  if (check(C))
    cout << "Order Check - successfull\n";
  else
    cout << "Order Check - unsuccessfull\n";

  if (kor(C, num, myTree, 4))
    cout << "Key of rank successfull\n";
  else
    cout << "Key of rank unsuccessfull\n";

  if (C[myTree.RankOfKey(A[num / 4])] == myTree.RankOfKey(A[num / 4]))
    cout << "Rank of Key Successfull\n";
  else
    cout << "Rank of key Unsuccessfull\n";

  cout << endl;

  return 0;
}

bool check(vector<int> &B)
{
  int count = 0;
  if (B.size() == 1)
    return true;
  for (int i = 0; i < B.size(); i++)
    if (B[i] < B[i + 1])
    {
      count++;
      if (count == B.size() - 1)
        return true;
    }
}

bool kor(vector<int> &B, int num, BinarySearchTree<int> &myTree, int div)
{
  //cout << "\nB[n/2-1]: " << B[num / 2 - 1] << endl;
  //cout << "Key of Rank(n/2): " << myTree.KeyOfRank(num/2) << endl;

  if (B[num / div - 1] == myTree.KeyOfRank(num / div))
    return true;
  else
    return false;
}
