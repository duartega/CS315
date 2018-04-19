// Author : Gabriel Duarte
// Date : 02/12/2018
// Class : CS315

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
using namespace std;

int insertionSort (vector<int> A);

int main()
{
  int sum = 0;
  int q = 100;
  int count = 0;
  srand(time(0));
  

  for (int i = 0; i < 10; i++)
    {
      sum = 0;
      cout << "q: " << q << "  ";
      count++;
      
      vector<int> A;
      for (int j = 0; j < q; j++)
	{
	  A.push_back(rand());
	}
      
      if (i <= 10)
      {
	sum += insertionSort(A);
	cout << "Count " << i << ": " << sum/10 << endl;
        q += 100;
      }
      
    }

  return 0;
}


int insertionSort (vector<int> A) {

  int count = 0;
  int temp;
  int max = -1;

  

  for (int j = 1; j < A.size(); ++j) {

    temp = A[j];

    for (int k = j - 1; k >= 0 && A[k] > temp; k--) {

      count++;

      A[k+1] = A[k];

    }

    if (j >= 0)

    count++;  // need to add the last comparison when the loop is not entered
	
    A[j] = temp;    

  }
  return count;
  
}
