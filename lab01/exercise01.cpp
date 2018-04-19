// Author:  Gabriel Duarte
// Class:   Cs315
// Date:    1/23-2018
// Teacher: Dr. Ravikumar

#include <iostream>

using namespace std;

int f(int n);

int main ()
{
  cout << f(4) << endl;
  return 0;
}

int f(int n)
{
  if (n == 1)
    return 1;
  else
    return f(n - 3) + n;
}
