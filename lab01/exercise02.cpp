// Author : Gabriel Duarte
// Class  : Cs315
// Date   : 1/23/2018
// Teacher: Dr. Ravikumar

#include <iostream>

using namespace std;

double g(double k, double l);

int main()
{

  cout << g(2, 51) << endl;
  return 0;
}

double g(double x, double n)
{
  if (n == 1)
    return 2;
  else
    return x * g(x, n-1);
}
