#include <iostream>
#include "hf.h"
using namespace std;
/*bool contains(const Object & x, BinaryNode* t)
    BinaryNode* findMin( BinaryNode *t) const
    void insert( const Comparable & x,  BinaryNode * & t)
    void remove( const Comparable & x, BinaryNode* & t)
    int countKey(BinaryNode* & t): returns the number of keys in the tree rooted at t.
    int countNodes(BinaryNode* & t): returns the number of nodes in the tree rooted at t. Because deleted nodes are still in the tree, countNodes and countKey may return different values
    void printTree(BinaryNode* & t) : prints the tree using inorder traversal. The successive keys will be printed in the same line with 3 blank spaces separating them. Make sure to print only the “active” keys, not the deleted ones.
*/
    // Test program
int main( )
{
    //BinarySearchTree<int> Te;
    //cout << "finding max of an empty tree" << Te.findMax() << endl;

    BinarySearchTree<int> t1;
    int NUMS1 = 40;  const int GAP  =   3711;

    for(int i = 0; i < 40; i++) {
        t1.insert(372632*(i+1) % GAP);
    }

    t1.printTree();

    BinarySearchTree<int> t;
    int NUMS = 400000;

    int i, temp, min1, max1;
    temp = 0; min1 = 2716761; max1 = -1;

    cout << "Checking... (no more output means success)" << endl;

    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS ) {
        temp++;
        t.insert( i );
        if (i < min1)
            min1 = i;
        if (i > max1)
            max1 = i;

    }
    cout << "number of keys inserted = " << temp << endl;
    cout << "min value is = " << min1 << endl;
    cout << "max value is = " << max1 << endl;

    int c1 = t.countKey();
    cout << "The number of keys should be 399999; actually it is = " << c1 << endl;

    if (t.countKey() != temp) 
        cout << "Count error before deletions" << endl;

    for( i = 1; i < NUMS; i+= 2 )
       t.remove( i );
    
    cout << "min value found after deletions is "  << t.findMin() << endl;

    //t.printTree();

    if( t.findMin() != 2)
        cout << "findMin error!" << endl;

    if ( t.findMax( ) != max1)
        cout << "findMax error!" << endl;
    //t.printTree();
    for( i = 2; i < NUMS; i+=2 )
        if( !t.contains( i ) )
            cout << "Error in searching - type 1!" << i << endl;

    for( i = 1; i < NUMS; i+=2 )
    {
        if( t.contains( i ) )
            cout << "Error in searching - type 2! and i: " << i << endl;
    }

//t.printTree();
    cout << "The size of the tree after deletions is " << t.countKey() << endl;
    if (t.countKey() != NUMS/2-1)
        cout << "error in counting keys after deletions" << endl;

    if (t.countNodes()!= NUMS-1)
       cout << "error in counting nodes after deletions" << endl;
    //cout << Numt.countNodes();

    int test = NUMS/17;
    if (test%2 != 0 && t.contains(test))
        cout << "error in search"  << endl;

    if (test%2 == 0 && !t.contains(test))
        cout << "error in search" << endl;

    test++;

    if (test%2 != 0 && t.contains(test))
        cout << "error in search"  << endl;

    if (test%2 == 0 && !t.contains(test))
        cout << "error in search" << endl;


    cout << "Finished testing" << endl;

    return 0;
}
