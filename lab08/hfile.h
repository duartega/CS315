#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <iostream> // For NULL
#include <iomanip>  // To set the width for the line numbers for words
#include <algorithm> // To use max

using namespace std;

// BinarySearchTree class
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
class BinarySearchTree
{
public:
  BinarySearchTree() : root(NULL)
  {
  }

  BinarySearchTree(const BinarySearchTree &rhs) : root(NULL)
  {
    *this = rhs;
  }

  /**
   * Destructor for the tree
   */
  ~BinarySearchTree()
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
  bool contains(const Comparable &x) const
  {
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
  void printTree(ostream &out = cout)
  {
    if (isEmpty())
      cout << "Empty tree" << endl;
    else
      printTree(root, out);
  }

  void Inorder(vector<int> &B)
  {
    Inorder(root, B);
  }

  void printC(vector<int> &C)
  {
    printC(root, C);
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
  bool insert(const Comparable &x)
  {
    insert(x, root);
  }

  int KeyOfRank(const Comparable &x)
  {
    KeyOfRank(x, root);
  }

  int RankOfKey(const Comparable &x)
  {
    RankOfKey(x, root);
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

  /**
   * Remove x from the tree. Nothing is done if x is not found.
   */
  bool remove(const Comparable &x)
  {
    remove(x, root);
  }

  /**
   * Deep copy.
   */
  const BinarySearchTree &operator=(const BinarySearchTree &rhs)
  {
    if (this != &rhs)
    {
      makeEmpty();
      root = clone(rhs.root);
    }
    return *this;
  }

private:
  struct BinaryNode
  {
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;
    // Added this for the vector
    int size;
    int height;

    BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt, int sz, int ht)
        : element(theElement), left(lt), right(rt), size(sz), height(ht) {}
  };

  BinaryNode *root;

  /*
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
  bool insert(const Comparable &x, BinaryNode *&t)
  {
    if (t == NULL)
    {
      t = new BinaryNode(x, NULL, NULL, 1, 0);
      return true;
    }
    else if (x < t->element)
    {
      if (insert(x, t->left))
      {
        t->size++;
        //t->height = LeftHeight(t);
        //t->height = max(LeftHeight(t), RightHeight(t)) + 1;
      }
      return true;
    }
    else if (t->element < x)
    {
      if (insert(x, t->right))
        t->size++;
      return true;
    }
    else //(x == t->element)
      return false;
    // Duplicate; do nothing
  }

  int RankOfKey(const Comparable &x, BinaryNode *&t)
  {
    if (t == NULL)
      return 0;
    if (x < t->element) // or t->element
      return RankOfKey(x, t->left);
    else if (x == t->element)
      return 1 + size(t->left);
    //else if (t->left != NULL)
    //return 0;
    else
      return 1 + size(t->left) + RankOfKey(x, t->right);
  }

  int KeyOfRank(const Comparable &k, BinaryNode *&t)
  {
    if (t == NULL || k > size(t)) // Or k is out of range
      return 0;
    if (size(t->left) == k - 1)
      //cout << t->element;
      return t->element;
    else if (size(t->left) >= k)
      return KeyOfRank(k, t->left);
    else
      return KeyOfRank(k - size(t->left) - 1, t->right);
  }

  /**
       * Internal method to remove from a subtree.
       * x is the item to remove.
       * t is the node that roots the subtree.
       * Set the new root of the subtree.
       */
  bool remove(const Comparable &x, BinaryNode *&t)
  {
    if (t == NULL)
      return false;

    if (t->element > x)
    {
      if (remove(x, t->left))
      {
        t->size--;
        return true;
      }
      else
        return false;
    }

    else if (t->element < x)
    {
      if (remove(x, t->right))
      {
        t->size--;
        return true;
      }
      else
        return false;
    }

    else if (t->left == NULL && t->right == NULL)
    {
      delete t;
      t = NULL;
      return true;
    }
    else if (t->left != NULL && t->right != NULL)
    {
      Comparable y = findMin(t->right);
      t->element = y;
      remove(y, t->right);
      t->size--;
      return true;
    }
    else
    {
      deleteMin(t);
      return true;
    }
    return false;
  }

  int deleteMin(BinaryNode *&t) const
  {
    BinaryNode *y = t;
    t = t->left != NULL ? t->left : t->right;
    delete y;
  }

  /**
       * Internal method to find the smallest item in a subtree t.
       * Return node containing the smallest item.
       */
  int findMin(BinaryNode *&t) const
  {
    if (t->left == NULL)
      return t->element;
    return findMin(t->left);
  }

  /**
       * Internal method to find the largest item in a subtree t.
       * Return node containing the largest item.
       */
  BinaryNode *findMax(BinaryNode *t) const
  {
    if (t != NULL)
      while (t->right != NULL)
        t = t->right;
    return t;
  }

  int LeftHeight(BinaryNode *t)
  {
    // returns the height of the tree t
    if (t == NULL)
      return -1;
    else
    {
      int p = height(t->left);
      return 1 + p;
    }
  }

  int RightHeight(BinaryNode *t)
  {
    // returns the height of the tree t
    if (t == NULL)
      return -1;
    else
    {
      int p = height(t->right);
      return 1 + p;
    }
  }

  /**
       * Internal method to test if an item is in a subtree.
       * x is item to search for.
       * t is the node that roots the subtree.
       */
  bool contains(const Comparable &x, BinaryNode *t) const
  {
    if (t == NULL)
      return false;
    else if (x < t->element)
      return contains(x, t->left);
    else if (t->element < x)
      return contains(x, t->right);
    else
      return true; // Match
  }

  /**
       * Internal method to make subtree empty.
       */
  void makeEmpty(BinaryNode *&t)
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
  void printTree(BinaryNode *t, ostream &out = cout)
  {
    if (t != NULL)
    {
      printTree(t->left, out);
      // B.push_back(t->element);
      out << t->element << " ";
      printTree(t->right, out);

      //inOrder(B);
    }
  }

  void Inorder(BinaryNode *t, vector<int> &B)
  {
    if (t != NULL)
    {
      Inorder(t->left, B);
      B.push_back(t->element);
      Inorder(t->right, B);
    }
  }

  void printC(BinaryNode *t, vector<int> &C)
  {
    if (t != NULL)
    {
      printC(t->left, C);
      C.push_back(t->element);
      printC(t->right, C);
    }
  }

  void search(const Comparable &x, BinaryNode *t, ostream &out = cout)
  {
    if (t != NULL)
    {

      search(x, t->left, out);

      search(x, t->right, out);
    }
  }

  void findHeight(BinaryNode *t, ostream &out = cout)
  {
    out << height(t);
  }

  void findSize(BinaryNode *t, ostream &out = cout)
  {
    out << size(t);
  }

  /**
       * Internal method to clone subtree.
     */
  BinaryNode *clone(BinaryNode *t) const
  {
    if (t == NULL)
      return NULL;
    else
      return new BinaryNode(t->element, clone(t->left), clone(t->right), t->size, t->height);
  }

public:
  static int height(BinaryNode *t)
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

  static int size(BinaryNode *t)
  {
    if (t == NULL)
      return 0;
    else
      return t->size;
  }

  BinaryNode *getRoot()
  {
    return root;
  }
};

#endif
