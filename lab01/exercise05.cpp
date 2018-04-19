#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> Gray (int n);

int main()
{

  vector<string> output = Gray(6);
  for (int i = 0; i < output.size(); i++)
    cout << output[i] << endl;

  return 0;
}

vector<string> Gray (int n)
{
  if (n == 1)
    {
      vector<string> v;
      v.push_back("0");
      v.push_back("1");
      return v;
    }
  else
    if (n > 1)
    {
      vector<string> u;
      vector<string> a = Gray(n-1);
      vector<string> b = Gray(n-1);

      for (int i = 0; i < a.size(); i++)
	{
	  a[i] += "0";
	}
      u.insert(u.end(), a.begin(), a.end());
      for (int j = 0; j < b.size(); j++)
      	{
	  b[j] += "1";
      	}
      u.insert(u.end(), b.rbegin(), b.rend());
      return u;
    }
}
