#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

int nextPrime(int n);

// SeparateChaining Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items

template <typename HashedObj>
class HashTable
{
  public:
    explicit HashTable(int size = 10007) : currentSize{0}
    {
        theLists.resize(10007);
    }

    bool contains(const HashedObj &x) const
    {
        auto &whichList = theLists[myhash(x)];
        return find(begin(whichList), end(whichList), x) != end(whichList);
    }

    int count(const HashedObj &x)
    {
        auto &whichList = theLists[myhash(x)];
        int probes = 1;

        return probes;
    }

    void makeEmpty()
    {
        for (auto &thisList : theLists)
            thisList.clear();
    }

    bool insert(const HashedObj &x, vector<vector<int>> &probes)
    {
        // Rehash; see Section 5.5
        if (++currentSize > theLists.size() / 2)
            return false;

        auto &whichList = theLists[myhash(x)];
        if (find(begin(whichList), end(whichList), x) != end(whichList))
            return false;

        whichList.push_back(x);

        return true;
    }

    bool insert(HashedObj &&x, vector<vector<int>> &probes)
    {
        // Rehash; see Section 5.5
        if (++currentSize > theLists.size() / 2)
            return false;
        //int probe = 0;
        auto &whichList = theLists[myhash(x)];
        //finds(whichList, x, probe);
        //probes.push_back(vector<int>{probe});
        if (find(begin(whichList), end(whichList), x) != end(whichList))
          return false;
           int count = 0;
        for (auto i : whichList)
            count++;
        cout << "The total number of probes: " << count << endl;
        whichList.push_back(std::move(x));

        return true;
    }

    bool finds(int list[], int x, int &probe)
    {
        for (int i = 0; i < sizeof(list); i++)
        {
            if (x == list[i])
            {
                probe += 5;
            }
            else
                return false;
        }
        return true;
    }

    bool remove(const HashedObj &x)
    {
        auto &whichList = theLists[myhash(x)];
        auto itr = find(begin(whichList), end(whichList), x);

        if (itr == end(whichList))
            return false;

        whichList.erase(itr);
        --currentSize;
        return true;
    }

  private:
    vector<list<HashedObj>> theLists; // The array of Lists
    unsigned currentSize;

    size_t myhash(const HashedObj &x) const
    {
        static hash<HashedObj> hf;
        return hf(x) % theLists.size();
    }
};

#endif
