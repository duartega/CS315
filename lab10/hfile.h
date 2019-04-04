#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <iostream> // For NULL
#include <iomanip>  // To set the width for the line numbers for words
using namespace std;

// AVLTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AVLTree
{
public:
  AVLTree() : root(NULL)
  {
  }

  AVLTree(const AVLTree &rhs) : root(NULL)
  {
    *this = rhs;
  }

  /**
   * Destructor for the tree
   */
  ~AVLTree()
  {
    makeEmpty();
  }

  /**
   * Find the smallest item in the tree.
   * Throw UnderflowException if empty.
   */
  const Comparable &findMin() const
  {
    if (isEmpty())
      throw UnderflowException();
    return findMin(root)->element;
  }

  /**
   * Find the largest item in the tree.
   * Throw UnderflowException if empty.
   */
  const Comparable &findMax() const
  {
    if (isEmpty())
      throw UnderflowException();
    return findMax(root)->element;
  }

  /**
   * Returns true if x is found in the tree.
   */
  bool contains(const Comparable &x)
  {
    comparisonsForSearch = 0;
    return contains(x, root);
  }

  /**
   * Test if the tree is logically empty.
   * Return true if empty, false otherwise.
   */
  bool isEmpty() const
  {
    return root == NULL;
  }

  /**
   * Print the tree contents in sorted order.
   */
  void printTree(ostream &out = cout) const
  {
    if (isEmpty())
      out << "Empty tree" << endl;
    else
      printTree(root, out);
  }

  /**
   * Make the tree logically empty.
   */
  void makeEmpty()
  {
    makeEmpty(root);
  }

  /**
   * Insert x into the tree; duplicates are ignored.
   */
  void insert(const Comparable &x, int y)
  {
    insert(x, root, y);
  }

  void search(const Comparable &x, ostream &out = cout)
  {
    search(x, root, out);
  }

  void findHeight(ostream &out = cout)
  {
    findHeight(root, out);
  }

  void findSize(ostream &out = cout)
  {
    findSize(root, out);
  }

  void getComparisons(ostream &out = cout)
  {
    getComparisons(root, out);
  }

  void getComparisonsInsert(ostream &out = cout)
  {
    getComparisonsInsert(root, out);
  }

  void getComparisonsContains(ostream &out = cout)
  {
    getComparisonsContains(root, out);
  }

  /**
   * Remove x from the tree. Nothing is done if x is not found.
   */
  void remove(const Comparable &x)
  {
    remove(x, root);
  }

  /**
   * Deep copy.
   */
  const AVLTree &operator=(const AVLTree &rhs)
  {
    if (this != &rhs)
    {
      makeEmpty();
      root = clone(rhs.root);
    }
    return *this;
  }

private:
  struct AvlNode
  {
    Comparable element;
    AvlNode *left;
    AvlNode *right;
    int height;
    int insertions;
    int containsInsertions;
    // Added this for the vector
    vector<int> lineNumberList;
    AvlNode(const Comparable &theElement, AvlNode *lt, AvlNode *rt, vector<int> lnl, int h = 0, int ins = 0, int cins = 0)
        : element(theElement), left(lt), right(rt), lineNumberList(lnl), height(h), insertions(ins), containsInsertions(cins) {}
  };

  AvlNode *root;
  int comparisonsForInsertions = 0;
  int comparisonsForSearch = 0;

  /**
       * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
  void insert(const Comparable &x, AvlNode *&t, int l)
  {
//comparisonsForInsertions += 1;
    if (t == NULL)
    {
      t = new AvlNode(x, NULL, NULL, vector<int>(), 0);
      //comparisonsForInsertions += 1;
      t->lineNumberList.push_back(l);
    }
    else if (x < t->element)
    {
      comparisonsForInsertions += 1;
      insert(x, t->left, l);
    }
    else if (t->element < x)
    {
      comparisonsForInsertions += 2;
      insert(x, t->right, l);
    }
    else
    {
      comparisonsForInsertions += 2;
      t->lineNumberList.push_back(l); // Duplicate; do nothing
    }
    balance(t);
  }

  static const int ALLOWED_IMBALANCE = 1;

  void balance(AvlNode *&t)
  {
    if (t == NULL)
      return;

    if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
      if (height(t->left->left) >= height(t->left->right))
        rotateWithLeftChild(t);
      else
        doubleWithLeftChild(t);
    else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
      if (height(t->right->right) >= height(t->right->left))
        rotateWithRightChild(t);
      else
        doubleWithRightChild(t);
    t->height = max(height(t->left), height(t->right)) + 1;
  }

  void rotateWithLeftChild(AvlNode *&k2)
  {
    AvlNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
  }

  void rotateWithRightChild(AvlNode *&k2)
  {
    AvlNode *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
  }

  void doubleWithLeftChild(AvlNode *&k3)
  {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
  }

  void doubleWithRightChild(AvlNode *&k3)
  {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
  }

  /**
       * Internal method to remove from a subtree.
       * x is the item to remove.
       * t is the node that roots the subtree.
       * Set the new root of the subtree.
       */
  void remove(const Comparable &x, AvlNode *&t)
  {
    if (t == NULL)
      return; // Item not found; do nothing
    if (x < t->element)
      remove(x, t->left);
    else if (t->element < x)
      remove(x, t->right);
    else if (t->left != NULL && t->right != NULL) // Two children
    {
      t->element = findMin(t->right)->element;
      remove(t->element, t->right);
    }
    else
    {
      AvlNode *oldNode = t;
      t = (t->left != NULL) ? t->left : t->right;
      delete oldNode;
    }

    balance(t);
  }

  /**
       * Internal method to find the smallest item in a subtree t.
       * Return node containing the smallest item.
       */
  AvlNode *findMin(AvlNode *t) const
  {
    if (t == NULL)
      return NULL;
    if (t->left == NULL)
      return t;
    return findMin(t->left);
  }

  /**
       * Internal method to find the largest item in a subtree t.
       * Return node containing the largest item.
       */
  AvlNode *findMax(AvlNode *t) const
  {
    if (t != NULL)
      while (t->right != NULL)
        t = t->right;
    return t;
  }

  /**
       * Internal method to test if an item is in a subtree.
       * x is item to search for.
       * t is the node that roots the subtree.
       */
  bool contains(const Comparable &x, AvlNode *t)
  {
    if (t == NULL)
    {
      // t->containsInsertions += 1;
      return false;
    }
    else if (x < t->element)
    {
      comparisonsForSearch += 1;
      return contains(x, t->left);
    }
    else if (t->element < x)
    {
      comparisonsForSearch += 2;
      return contains(x, t->right);
    }
    else{
      comparisonsForSearch += 2;
      return true; // Match
    }
  }
  /****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != NULL )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
      *****************************************************/

  /**
       * Internal method to make subtree empty.
       */
  void makeEmpty(AvlNode *&t)
  {
    if (t != NULL)
    {
      makeEmpty(t->left);
      makeEmpty(t->right);
      delete t;
    }
    t = NULL;
  }

  /**
       * Internal method to print a subtree rooted at t in sorted order.
       */
  void printTree(AvlNode *t, ostream &out) const
  {
    if (t != NULL)
    {
      printTree(t->left, out);
      out << t->element << " ";
      //print out the vector
      out << right << setw(20 - t->element.size());
      for (auto i = t->lineNumberList.begin(); i != t->lineNumberList.end() - 1; i++)
        out << *i << ", ";
      out << t->lineNumberList.back() << endl;
      printTree(t->right, out);
    }
  }

  void search(const Comparable &x, AvlNode *t, ostream &out = cout)
  {
    if (t != NULL)
    {
      if (t->element == x)
      {
        for (auto i = t->lineNumberList.begin(); i != t->lineNumberList.end() - 1; i++)
          out << *i << ", ";
        out << t->lineNumberList.back() << endl;
      }
      search(x, t->left, out);

      search(x, t->right, out);
    }
  }

  void findHeight(AvlNode *t, ostream &out = cout)
  {
    out << height(t);
  }

  void findSize(AvlNode *t, ostream &out = cout)
  {
    out << size(t);
  }

  void getComparisonsInsert(AvlNode *t, ostream &out = cout)
  {
    out << comparisonsForInsertions;
  }

  void getComparisonsContains(AvlNode *t, ostream &out = cout)
  {
    out << comparisonsForSearch;
  }

  int heights(AvlNode *t) const
  {
    return t == NULL ? -1 : t->height;
  }

  /**
       * Internal method to clone subtree.
     */
  AvlNode *clone(AvlNode *t) const
  {
    if (t == NULL)
      return NULL;
    else
      return new AvlNode(t->element, clone(t->left), clone(t->right), t->lineNumberList);
  }

public:
  static int height(AvlNode *t)
  {
    // returns the height of the tree t
    if (t == NULL)
      return 0;
    else
    {
      int p = height(t->left);
      int q = height(t->right);
      if (p < q)
        return 1 + q;
      else
        return 1 + p;
    }
  }

  static int size(AvlNode *t)
  {
    if (t == NULL)
      return 0;
    else
      return 1 + size(t->left) + size(t->right);
  }

  AvlNode *getRoot()
  {
    return root;
  }
};

#endif
