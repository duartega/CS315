// Author      : Gabriel Duarte
// Date        : 02/18/2018
// Class       : Cs315 Spring 2018
// Description : We will be entering a list that will make nodes and depending on the depth of the list,
//               make down pointers. We will be able to update the list as well. The program will also
//               allow us to print the original list as well as the updated list.


#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <stack>

using namespace std;

// Create an enumeration list for the tokens
enum TokenType { StartOfList, EndOfList, Comma, Number };

struct Token {
  TokenType type;
  int number;
};

class Stack;

class Node {

public:
  Node(int key1){
    key = key1;
    tag = 0;
    down = NULL;
    next = NULL;
  }
  
  Node(Node* dptr, Node* nptr) {
    tag = 1;
    down = dptr;
    next = nptr;
  }
  
  void setKey(int k) {
    key = k;
  }
  
  void setDown(Node* ptr) {
    down = ptr;
  }
  
  void setNext(Node* ptr) {
    next = ptr;
  }
  
  void setTag(int t) {
    tag = t;
  }

  int getKey() {
    return key;
  }

  int getTag() {
    return tag;
  }

  Node* getDown() {
    return down;
  }

  Node* getNext() {
    return next;
  }

  int size() {
    if (this == NULL)
      return 0;
    else if (this->tag == 0) return 1;
    else
      return down->size() + next->size();
  }

  void update(int j, int k){
    // Checks to see if the list is empty
    if (this->size() == 0)
      {
	cout << "The list is empty!\n";
	return;
      }

    // Reaches the point where the number is and changes it
    else if (this->tag == 0)
      {
	this->key = k;
	return;
      }

    // Recursively call update
    else
      {
	int s = this->down->size();
	if (j <= s)
	  this->down->update(j,k);
	else
	  this->next->update(j-s, k);
      }
  }

  bool isEmpty() {
    return this == NULL;
  }

  void print(int depth) {
    if (this == NULL) return;
    if (tag == 0) {
      cout << "<" << key << ":" << depth << ">  " ;
    }
    else {
      down->print(depth+1);
      next->print(depth);
    } // end else
  } // end print
  
private:
  int tag;
  int key;
  Node* down;
  Node* next;
};

class Stack {

private:
  int maxTop;// max stack size = size - 1
  int top;// current top of stack
  Node* values[1000];// element array

public:

  bool IsEmpty() { return top == -1; }
  bool IsFull() { return top == maxTop; }

  Stack() {
    top=-1;
    maxTop= 999;
  }

  void Push(Node* x) {
    if (IsFull())  // if stack is full, print error
      cout << "Error: the stack is full." << endl;
    else {
      values[++top]= x;
    }
  }

  Node*  Pop() {
    if (IsEmpty()) { //if stack is empty, print error
      cout << "Error: the stack is empty." << endl;
      return NULL;
    }
    else {
      return values[top--];
    }
  }

  Node* Top() {
    if (IsEmpty()) {
      cout << "Error: the stack is empty." << endl;
      return NULL;
    }
    else
      return values[top];
  }
};

int convert(string x) {
  // converts a string rep of decimal integer to an int
  return atoi(x.c_str());
}

Node* create (vector<string> T) {
  return NULL; // to be completed. Takes as input a vector of strings and builds a generalized list
} 

string TokenTypeToString (TokenType t) {
  switch(t) {
  case StartOfList: return "[";
  case EndOfList: return "]";
  case Number: return "Number";
  case Comma: return "Comma";
  default:
    cout << "Unknown token type\n";
    exit(1);
  }
}


// Function Prototypes
vector<Token> tokenize(string input);
Node * buildList(vector<Token> tokens);
//---------------------------------------------MAIN---------------------------------------------
int main ()
{
  // Declare a sting for input and one for the copy of the string
  string input;
  string original;
  
  // Ask the user for their list and get input 
  cout << "Please enter your generalized list: " << endl;
  getline (cin, input);

  // Copy the string so that we can recall the original entry later on
  original = input;

  // Create a vector to store our tokens
  vector<Token> sendin;

  // Call the tokenize function to tokenize our input
  sendin = tokenize(input);

  // Call build list to build our list and store the output in the list variable
  Node* list = buildList(sendin);

  // Create a variable for the while loop and input for updates, priting, and quiting
  char KeyPress;

  // Create the variable for the index and value to replace
  int num, index;
  
  cout << "\nThe input list (with depth for each key):\n";

  // Print the list out to them in <x:x> form for each node with its value and depth
  list->print(-1);
  
  
  // Ask user for input
  cout << "\nWhat would you like to do?\n";
  cout << "'u' : Update an element\n";
  cout << "'p' : Print the original list\n";
  cout << "'q' : Quit the program\n";

  // Run until the 'q' key is pressed
  while (KeyPress != 'q')
    {
      // Read in the key theyu pressed
      cin >> KeyPress;
      if (KeyPress == 'u')
	{
	  cout << "\nWhich element would you like to update? ";
	  cin >> index;

	  // Makes sure that the index is in range
	  if (index <= list->size())
	    {
	      cout << "What would you like to update it to? ";
	      cin >> num;
	      cout << "\nThe updated list is:\n";

	      // Call the update list and then update it and print
	      list->update(index, num);
	      list->print(-1);
	      
	      cout << "\n\nWhat would you like to do?\n";
	      cout << "'u' : Update an element\n";
	      cout << "'p' : Print the original list\n";
	      cout << "'q' : Quit the program\n";
	    }
	  
	  // If the index is out of range
	  else
	    {
	      cout << "\nInvalid index!\n";
	      
	      cout << "\nWhat would you like to do?\n";
	      cout << "'u' : Update an element\n";
	      cout << "'p' : Print the original list\n";
	      cout << "'q' : Quit the program\n";
	    }
	}

      // Will quit the program
      else if (KeyPress == 'q')
	{
	  cout << "\nThe program has exited with no errors!\n\n";
	  break;
	}

      // Will print the original list and ask what they want to do again
      else if (KeyPress == 'p')
	{
	  cout << "\nThe original list: " << original << endl;
	  cout << "\nWhat would you like to do?\n";
	  cout << "'u' : Update an element\n";
	  cout << "'p' : Print the original list\n";
	  cout << "'q' : Quit the program\n";
	}

      // Any other input will exit the program without segfault
      else
	{
	  cout << "\nThe input is invalid: Exiting!\n";
	  exit(1);
	}      
    }
    
  return 0;
}

// Will tokenize our string input
vector<Token> tokenize(string input)
{
  // Create the stringstream so we can read in the string
  stringstream stream;
  stream << input;

  // Create a 'c' variable so we can compare the input
  char c;
  int i;

  // Create a vector to store our tokens
  vector<Token> tokens;

  // Loop while util the end of the string
  while (stream >> c)
    {
      // Checks the types of characters being read in and set its types
      Token t;
      if (c == '[')
	{
	  t.type = StartOfList;
	}
      else if (c == ']') {
	t.type = EndOfList;
      }
      else if (c == ',') {
	t.type = Comma;
      }
      else if (c == ' ') {
	continue;
      }
      else if (c == '-' or isdigit(c))
	{
	  t.type = Number;
	  // Will put the numbers into a vector
	  stream.putback(c);
	  // Keep reading until the number is fully read in
	  stream >> i;
	  t.number = i;
	}

      // Will exit if any other input is entered without segfault
      else
	{
	  cout << "Unexpected input! " << c << " Exiting!";
	  exit(1);
	}
      tokens.push_back(t);
    }
  /*
    for (auto i : tokens)
    {
    if (i.type == Number) {
    cout << i.number << endl;
    }
    else {
    cout << TokenTypeToString(i.type) << endl;
    }
    }
  */

  // Return the vector
  return tokens;
}

Node * buildList(vector<Token> tokens)
{
  // Initialize the stack
  Stack S;

  // C++ 11 syntax to increment through the vector of tokens
  for (auto i : tokens) {

    // Checks for start of list '[' and creates a node. Pushes onto stack
    if (i.type == StartOfList){
      Node * temp = new Node(NULL, NULL);
      S.Push(temp);
    }

    // Checks for a number and then creates a new node dwnptr and new node. Pushes onto stack
    else if (i.type == Number)
      {
	Node * n = new Node(new Node(i.number), NULL);
	S.Push(n);
      }

    // Do nothing if the token is a comma
    else if (i.type == Comma) {
    }

    // Checks for end of list ']' and pops
    else if (i.type == EndOfList)
      {
    	Node * n = S.Pop();

	// Keep popping while Top()->size() != 0
      	while (S.Top()->size() != 0)
      	  {
	    Node * k1 = S.Pop();
	    k1->setNext (n);
	    n = k1;
	  }
      	Node * list = S.Pop();
	list->setDown(n);
      	S.Push(list);
      }

    // Exit if unexpected tokens appear
    else
      {
	cout << "Unexpected token type!\n";
	exit(1);
      }
  }

  // Return the pointer
  return S.Pop();
}
