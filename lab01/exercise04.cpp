#include <iostream>

using namespace std;

long long int C(int n, int m);

int main()
{

  cout << C(6,3) << endl;
  return 0;
}

long long int C(int n, int m) {
  if (m > n) return 0; else
    if (m == n || m == 0) return 1;
    else return C(n - 1, m) + C(n - 1, m - 1);
}
