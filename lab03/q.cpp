#include <iostream>

using namespace std;

int main ()
{

  int count = 0;
  int c1 = 0;
  
  for (int j = 1; j < 100; j++)
    {
      c1++;
      for (int k = j + 1; k < 100; ++k)
	count ++;
    }

  cout << "B[j] = 0 : " << c1 << endl << " B[j] += b[k] : " << count << endl;
  return 0;
}
